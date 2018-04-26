#ifndef ASYNCHRONOUS_LOADER_H
#define ASYNCHRONOUS_LOADER_H

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>

#include "constants.hpp"

/*
  This file is the unlucky product of premature optimization.
  The creation of Pdf_page, Highlighting and Highlighting_component instances was extremely slow, but I made too few benchmarks and I erroneuosly tought that the problem was "new" being called too many times (I later solved the real problem).
  This file defines a template class, implemented with the singleton pattern (that means that only one object of Asynchronous_loader can be created).
  The syntax Asynchronous_loader::get_isntance() is used to access the singleton object.
  The template definition is Asynchronous_loader <T, buffer_size>, where T is a type for which we need to call "new" various times, like Highlighting, and buffer_size is the size of two internal buffers that are allocated asynchronously inside the template to store T instances, ready to be returned when asked (so avoiding to call "new" when the instance is needed).
  
  Example:
  Since now T will be an Highlighting.  
  When the program starts, Asynchronous_loader<Highlighting,1000>::get_instance() must be called. 
  This starts an asynchronous thread which allocates two vectors of 1000 highlightings each.
  When the program needs a new Highlighting it will just call Asynchronous_loader<Highlighting,1000>::get_instance().get_element()
  get_element() tries to return the element at index current_element_in_buffer of the buffer number current_buffer.
  If the background thread has not finished yet to load the current_buffer, then the call to get_element() will wait until the buffer is ready.
  When the buffer is ready, get_element() will return the desired element and increment current_element_in_buffer.
  Before returning, if get_element() detects that current_element_in_buffer is equal to the size of the buffer, it flips the value of current_buffer and sets current_element_in_buffer to 0 (so at the next call of get_element(), the element at index 0 of the other buffer will be returned).
  The other buffer it is expected to be already allocated, if not the new call to get_element() will just wait (as described before).
  When get_element() returns the last element of a buffer, before returning, starts a new background thread to re-allocate the just exhausted buffer.

  Additional details:
  -If Asynchronous_loader<Highlighting,1000>::get_instance() is called and then also Asynchronous_loader<Highlighting,999>::get_instance() (same T, but different value for buffer_size), an error will be raised by the template function ensure_only_one_is_instancieated()
  -The atomic values should be avoided, and one should use conditional variables, as explained here: https://stackoverflow.com/questions/49986097/creating-a-thread-which-acquires-a-mutex-before-the-calling-thread-in-c0x/49987358#49987358
  -For more information about the singleton pattern, check out here: https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
  -Do not trust std::cerr if it does not show anything, probably it is not thread safe (I am not sure).

  Is this class useful?
  -First of all, the code seems working (even if I have not made enoght tests and if there is a known bug, highlighting below), so it can be used for ispiration when multithreading will be needed
  -Second, in my machine it is comparable to call "new" throusands of times or to use this class, but maybe if we will need to call new more times or in a different machine, this class could become useful again. Honestly I do not think this would be the case.
  ---> THIRD, A CIRCUMNSTANCE IN WHICH THIS CLASS COULD BE REALLY USEFUL, IS CACHE EXPLOITATION. In fact the objects allocated via this method are stored in contigous memory, so they accomplish the principle of data locality. This could lead to a great improvement in some machines.

  If you want to use this code:
  -you have to insert, in main.cpp,
  "Resources_manager::initialize_resources_caching();"
  -you have to replace, in resources_manager.cpp, the three lines containing "new" with the three adjacent lines containing a call to a function of Asynchronous_loader, for instance
  "Highlighting * highlighting = new Highlighting();" 
  must be replaced by
  "Highlighting * highlighting = Asynchronous_loader<Highlighting,BUFFER_SIZE_HIGHLIGHTING>::get_instance().get_element();"
*/

// this is used becase we want only one instance of Asynchronous_loader to be defined for each T, and not for each (T, buffer_size)
template <class T> void ensure_only_one_is_instanciated()
{
    std::cerr << "ensure_only_one_is_instanciated(): sizeof(T) = " << sizeof(T) << "\n";
    static std::mutex first_instance_mutex;
    std::unique_lock<std::mutex> lock(first_instance_mutex);
    static bool first_instance = true;
    if(!first_instance) {
        std::cerr << "error: first_instance = " << first_instance << ", aborting.\n";
        MY_ASSERT(false); exit(1);
    }
    first_instance = false;
}

template <class T, int buffer_size>
class Asynchronous_loader {
public:
    Asynchronous_loader(Asynchronous_loader const &) = delete;
    void operator=(Asynchronous_loader const &) = delete;

    static Asynchronous_loader & get_instance()
    {
        // this is thread-safe since C++0x
        static Asynchronous_loader instance;
        return instance;
    }
    void loader();
    T * get_element();

    std::vector<std::thread *> threads;
    std::mutex m;
    std::mutex loader_running_mutex;
    std::atomic<bool> loader_running;
    std::atomic<bool> loader_running_for_the_first_time;
    // when a buffer is full it is filled again
    T * buffers [2][buffer_size];
    bool current_buffer = 0;
    unsigned int current_element_in_buffer = 0;

private:
    Asynchronous_loader()
    {
        std::cerr << "Asynchronous_loader(): sizeof(T) = " << sizeof(T) << ", buffer_size = " << buffer_size << "\n";
        ensure_only_one_is_instanciated<T>();
        this->loader_running_for_the_first_time = true;
        this->loader_running = false;
        std::thread * t = new std::thread(&Asynchronous_loader::loader,this);
        this->threads.push_back(t);
    }
    ~Asynchronous_loader()
    {
        for(auto && t: this->threads){
            t->join();
            delete t;
        }            
    }
};

template <class T, int buffer_size>
void Asynchronous_loader<T, buffer_size>::loader()
{
    {
        // std::cerr << "info: asking loader_running_mutex (loader), sizeof(T) = " << sizeof(T) << "\n";
        std::lock_guard<std::mutex> g(this->loader_running_mutex);
        // std::cerr << "info: acquired loader_running_mutex (loader), sizeof(T) = " << sizeof(T) << "\n";
        
        // for printing the output, because if there is an error we do not want these value to change before having printed them
        bool b0 = this->loader_running;
        bool b1 = this->loader_running_for_the_first_time;
        if(!((!b0 && b1) || (b0 && !b1))) {
            std::cerr << "error: this->loader_running = " << b0 << ", this->loader_running_for_the_first_time = " << b1 << ", aborting\n";
            MY_ASSERT(false); exit(1);
        }

        //BUG: if get_element reaches the last element of a buffer (so it starts this thread), get_element() is called a lot of times before this thread finished (so even the other buffer is exhausted) and so get_element() tries to get again an element of the buffer modified in this call of loader(), then there will be a conflict in accessing the buffer. There is no need to fix this bug now since this class is unused
        
        int iterations = b1 ? 2 : 1;
        for(int i = 0; i < iterations; i++) {
            /*
              We do not bother to delete, it is someone else responsibility. 
              So we just allocate over the previously allocated buffer.
              For instance that will be done when deleting an Highlighting, a Page, removing a cached Document, etc.
            */
            T * allocated_buffer = new T [buffer_size];
            for(int i = 0; i < buffer_size; i++) {
                this->buffers[(int)(!current_buffer)][i] = allocated_buffer + i;
            }
            if(b1) {
                current_buffer = !current_buffer;
            }
        }
    
        this->loader_running = false;
        this->loader_running_for_the_first_time = false;
        // std::cerr << "info: initialized, sizeof(T) = " << sizeof(T) << "\n";
    }
}

template <class T, int buffer_size>
T * Asynchronous_loader<T, buffer_size>::get_element()
{
    {
        // std::cerr << "info: started waiting outsize 0, sizeof(T) = " << sizeof(T) << "\n";
        while(this->loader_running_for_the_first_time) {
            // std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        // std::cerr << "info: finished waiting outsize 0, sizeof(T) = " << sizeof(T) << "\n";

        // std::cerr << "info: asking m (get_element), sizeof(T) = " << sizeof(T) << "\n";
        std::lock_guard<std::mutex> lock(this->m);
        // std::cerr << "info: acquired m (get_element), sizeof(T) = " << sizeof(T) << "\n";
  
        if(current_element_in_buffer >= buffer_size) {
            // std::cerr << "info: current_element_in_buffer = " << current_element_in_buffer << ", aborting\n";
            MY_ASSERT(false); exit(1);
        }
        
        T * element_to_return = this->buffers[(int)current_buffer][current_element_in_buffer];
        
        current_element_in_buffer++;
        if(current_element_in_buffer == buffer_size) {
            {
                // std::cerr << "info: started waiting outsize 1, sizeof(T) = " << sizeof(T) << "\n";
                while(1) {
                    // std::cerr << "info: asked loader_running_mutex (loader), sizeof(T) = " << sizeof(T) << "\n";
                    std::lock_guard<std::mutex> g(this->loader_running_mutex);
                    if(!this->loader_running) {
                        break;
                    }
                    // std::cerr << "info: acquired loader_running_mutex (loader), sizeof(T) = " << sizeof(T) << "\n";
                    // std::this_thread::sleep_for(std::chrono::milliseconds(1));
                }
                // std::cerr << "info: finished waiting outsize 1, sizeof(T) = " << sizeof(T) << "\n";
            }
            this->loader_running = true;
            current_element_in_buffer = 0;
            current_buffer = !current_buffer;
            std::thread * t = new std::thread(&Asynchronous_loader::loader,this);
            this->threads.push_back(t);
        }
        return element_to_return;
    }
}

#endif //ASYNCHRONOUS_LOADER_H

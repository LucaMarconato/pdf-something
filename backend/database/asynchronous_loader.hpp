#ifndef ASYNCHRONOUS_LOADER_H
#define ASYNCHRONOUS_LOADER_H

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>

// #include <condition_variable>

//TODO: std::cerr makes everything block, support it!
//TODO: use a conditional variable: https://stackoverflow.com/questions/49986097/creating-a-thread-which-acquires-a-mutex-before-the-calling-thread-in-c0x/49987358#49987358

/*
  Singleton pattern: 
  https://stackoverflow.com/questions/1008019/c-singleton-design-pattern

  It is thread safe, as explained here:
  https://stackoverflow.com/questions/1661529/is-meyers-implementation-of-the-singleton-pattern-thread-safe
*/

// this is used becase we want only one instance of Asynchronous_loader to be defined for each T, and not for each (T, buffer_size)
template <class T> void ensure_only_one_is_instanciated()
{
    static bool first_instance = true;
    if(!first_instance) {
        // std::cerr << "error: first_instance = " << first_instance << ", aborting.\n";
        exit(1);
    }
}

template <class T, int buffer_size>
class Asynchronous_loader {
public:
    static Asynchronous_loader & get_instance()
    {
        // this mutex is set to be sure that the variable first_instance is accessed correctly
        std::unique_lock<std::mutex> lock(Asynchronous_loader::get_instance_mutex);
        ensure_only_one_is_instanciated<T>();

        // this is thread-safe since C++0x
        static Asynchronous_loader instance;
        return instance;
    }
    Asynchronous_loader(Asynchronous_loader const &) = delete;
    void operator=(Asynchronous_loader const &) = delete;
    static void loader();
    static T * get_element();

    static std::vector<std::thread *> threads;
    // for ensuring that each template instantiation is invoked only once in the code
    static std::mutex get_instance_mutex;
    static std::mutex m;
    static std::mutex loader_running_mutex;
    // TODO: do we really need an atomic here?
    static std::atomic<bool> loader_running;
    static std::atomic<bool> loader_running_for_the_first_time;
    // when a buffer is full it is filled again
    static T * buffers [2][buffer_size];
    static bool current_buffer;
    static unsigned int current_element_in_buffer;

private:
    Asynchronous_loader()
    {
        Asynchronous_loader::loader_running_for_the_first_time = true;
        std::thread * t = new std::thread(Asynchronous_loader::loader);
        Asynchronous_loader::threads.push_back(t);
    }
    ~Asynchronous_loader()
    {
        for(auto && t: Asynchronous_loader::threads){
            t->join();
            delete t;
        }            
    }
};

template <class T, int buffer_size>
std::vector<std::thread *> Asynchronous_loader<T, buffer_size>::threads;

template <class T, int buffer_size>
std::mutex Asynchronous_loader<T, buffer_size>::get_instance_mutex;

template <class T, int buffer_size>
std::mutex Asynchronous_loader<T, buffer_size>:: m;

template <class T, int buffer_size>
std::mutex Asynchronous_loader<T, buffer_size>::loader_running_mutex;

template <class T, int buffer_size>
std::atomic<bool> Asynchronous_loader<T, buffer_size>::loader_running = false;

template <class T, int buffer_size>
std::atomic<bool> Asynchronous_loader<T, buffer_size>::loader_running_for_the_first_time;

template <class T, int buffer_size>
T * Asynchronous_loader<T, buffer_size>::buffers [2][buffer_size];

template <class T, int buffer_size>
bool Asynchronous_loader<T, buffer_size>::current_buffer = 0;

template <class T, int buffer_size>
unsigned int Asynchronous_loader<T, buffer_size>::current_element_in_buffer = 0;

template <class T, int buffer_size>
void Asynchronous_loader<T, buffer_size>::loader()
{
    {
        // std::cerr << "error: asking loader_running_mutex (loader), sizeof(T) = " << sizeof(T) << "\n";
        std::lock_guard<std::mutex> g(Asynchronous_loader::loader_running_mutex);
        std::cerr << "info: acquired loader_running_mutex (loader), sizeof(T) = " << sizeof(T) << "\n";
        // for printing the output, because they can change
        bool b0 = Asynchronous_loader::loader_running;
        bool b1 = Asynchronous_loader::loader_running_for_the_first_time;
        if(!((!b0 && b1) || (b0 && !b1))) {
            // std::cerr << "error: Asynchronous_loader::loader_running = " << b0 << ", Asynchronous_loader::loader_running_for_the_first_time = " << b1 << ", aborting\n";
            exit(1);
        }
    
        {
            int iterations = b1 ? 2 : 1;
            for(int i = 0; i < iterations; i++) {
                // we do not delete, Mediator will do when, for instance, deleting an Highlighting, a Page, removing a cached Document, etc.
                T * allocated_buffer = new T [buffer_size];
                for(int i = 0; i < buffer_size; i++) {
                    Asynchronous_loader::buffers[(int)(!current_buffer)][i] = allocated_buffer + i;
                }
                if(b1) {
                    current_buffer = !current_buffer;
                }
            }
        }
    
        Asynchronous_loader::loader_running = false;
        Asynchronous_loader::loader_running_for_the_first_time = false;
        // std::cerr << "error: initialized, sizeof(T) = " << sizeof(T) << "\n";
    }
}

template <class T, int buffer_size>
T * Asynchronous_loader<T, buffer_size>::get_element()
{
    {
        // std::cerr << "error: started waiting outsize 0, sizeof(T) = " << sizeof(T) << "\n";
        // check that the mutex is actually not required here
        while(Asynchronous_loader::loader_running_for_the_first_time) {
            // std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        // std::cerr << "error: finished waiting outsize 0, sizeof(T) = " << sizeof(T) << "\n";

        // std::cerr << "error: asking m (get_element), sizeof(T) = " << sizeof(T) << "\n";
        std::lock_guard<std::mutex> lock(Asynchronous_loader::m);
        // std::cerr << "error: acquired m (get_element), sizeof(T) = " << sizeof(T) << "\n";
  
        if(current_element_in_buffer >= buffer_size) {
            // std::cerr << "error: current_element_in_buffer = " << current_element_in_buffer << ", aborting\n";
            exit(1);
        }
        
        unsigned int to_return_element_in_buffer = current_element_in_buffer;
        bool to_return_current_buffer = current_buffer;
        
        current_element_in_buffer++;
        if(current_element_in_buffer == buffer_size) {
            {
                // std::cerr << "error: started waiting outsize 1, sizeof(T) = " << sizeof(T) << "\n";
                while(1) {
                    // std::cerr << "error: asked loader_running_mutex (loader), sizeof(T) = " << sizeof(T) << "\n";
                    std::lock_guard<std::mutex> g(Asynchronous_loader::loader_running_mutex);
                    if(!Asynchronous_loader::loader_running) {
                        // TODO: check if break is thread-safe, it should be
                        break;
                    }
                    // std::cerr << "error: acquired loader_running_mutex (loader), sizeof(T) = " << sizeof(T) << "\n";
                    // std::this_thread::sleep_for(std::chrono::milliseconds(10));
                }
                // std::cerr << "error: finished waiting outsize 1, sizeof(T) = " << sizeof(T) << "\n";
            }
            Asynchronous_loader::loader_running = true;
            current_element_in_buffer = 0;
            current_buffer = !current_buffer;
            std::thread * t = new std::thread(Asynchronous_loader::loader);
            Asynchronous_loader::threads.push_back(t);
        }
        return Asynchronous_loader::buffers[(int)to_return_current_buffer][to_return_element_in_buffer];
    }
}


#endif //ASYNCHRONOUS_LOADER_H

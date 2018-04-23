#ifndef ASYNCHRONOUS_LOADER_H
#define ASYNCHRONOUS_LOADER_H

#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>

// #include <condition_variable>

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
        std::cerr << "error: first_instance = " << first_instance << ", aborting.\n";
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

        // according to the link above about thread-safety, the following line would be thread-safe since C++0x even without using mutexes
        static Asynchronous_loader instance;
        instance.loader_running = true;
        std::thread t(instance.loader);
        return instance;
    }
    Asynchronous_loader(Asynchronous_loader const &) = delete;
    void operator=(Asynchronous_loader const &) = delete;
    void loader();
    T * get_element();

    // for ensuring that each template instantiation is invoked only once in the code
    static std::mutex get_instance_mutex;
    std::mutex m;
    std::mutex loader_running_mutex;
    std::atomic<bool> loader_running;
    // when a buffer is full it is filled again
    T * buffers [2][buffer_size];
    bool current_buffer = 0;
    unsigned int current_element_in_buffer = 0;

private:
    Asynchronous_loader() {}
};

template <class T, int buffer_size>
void Asynchronous_loader<T, buffer_size>::loader()
{
    {
        std::lock_guard<std::mutex> g(this->loader_running_mutex);
        if(!this->loader_running) {
            std::cerr << "error: this->loader_running = 0, aborting\n";
            exit(1);
        }
    }
    
    {
        std::lock_guard<std::mutex> g(this->m);
        // we do not delete, Mediator will do when, for instance, deleting an Highlighting, a Page, removing a cached Document, etc.
        T * allocated_buffer = new T [buffer_size];
        for(int i = 0; i < buffer_size; i++) {
            this->buffers[(int)(!current_buffer)][i] = allocated_buffer + i;
        }
        this->current_buffer = !(this->current_buffer);
    }
    
    {
        std::lock_guard<std::mutex> g(this->loader_running_mutex);
        this->loader_running = false;      
    }
}

template <class T, int buffer_size>
T * Asynchronous_loader<T, buffer_size>::get_element()
{
    {
        {
            std::lock_guard<std::mutex> g(this->loader_running_mutex);
            while(!this->loader_running) {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }          
        }
        std::lock_guard<std::mutex> lock(this->m);
        if(current_element_in_buffer < buffer_size) {
            unsigned int to_return_index = current_element_in_buffer;
            current_element_in_buffer++;
            if(current_element_in_buffer == buffer_size) {
                current_element_in_buffer %= buffer_size;
                this->loader_running = true;
                std::thread t(this->loader);
            }
            return this->buffers[(int)current_buffer][to_return_index];
        }
    }
}

#endif //ASYNCHRONOUS_LOADER_H

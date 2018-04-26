#include "monitor.hpp"

Monitor::Monitor() {}

Monitor::Monitor(const Monitor & obj)
{
    this->initialized = obj.initialized;
    this->id = obj.id;
    this->name = obj.name;
}

void swap(Monitor & obj1, Monitor & obj2)
{
    std::swap(obj1.initialized,obj2.initialized);
    std::swap(obj1.id,obj2.id);
    std::swap(obj1.name,obj2.name);
}

Monitor & Monitor::operator=(Monitor obj)
{
    swap(*this,obj);
    return *this;
}

bool Monitor::is_valid() const
{
    bool is_valid = true;
    is_valid = is_valid && this->initialized;

    if(!is_valid) {
        std::cerr << "error: Monitor, is_valid = " << is_valid << "\n";
    }
    return is_valid;
}

std::ostream & operator<<(std::ostream & stream, const Monitor & obj)
{
    if(obj.initialized) {
        stream << "obj.id = " << obj.id << "<BR>";
        stream << "obj.name = " << obj.name;
        stream << "\n";        
    } else {
        stream << "[uninitialized monitor]";
    }
    return stream;    
}


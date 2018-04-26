#include "virtual_screen.hpp"

Virtual_screen::Virtual_screen() {}

Virtual_screen::Virtual_screen(const Virtual_screen & obj)
{
    this->initialized = obj.initialized;
    this->id = obj.id;        
}

bool Virtual_screen::is_valid() const
{
    bool is_valid = true;
    is_valid = is_valid && this->initialized;

    if(!is_valid) {
        std::cerr << "error: Virtual_screen, is_valid = " << is_valid << "\n";
        exit(1);
    }
    return is_valid;
}

void swap(Virtual_screen & obj1, Virtual_screen & obj2)
{
    std::swap(obj1.initialized,obj2.initialized);
    std::swap(obj1.id,obj2.id);
}

Virtual_screen & Virtual_screen::operator=(Virtual_screen obj)
{
    swap(*this,obj);
    return *this;
}

std::ostream & operator<<(std::ostream & stream, const Virtual_screen & obj)
{
    if(obj.initialized) {
        stream << "obj.id = " << obj.id;
        return stream;
    } else {
        stream << "[uninitialized virtual screen]";
    }
    return stream;
}

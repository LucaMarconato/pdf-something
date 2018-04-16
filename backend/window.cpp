#include "window.hpp"

#include <iostream>

//virtual screen

Virtual_screen::Virtual_screen()
{
    
}

std::ostream & operator<<(std::ostream & stream, const Virtual_screen & obj)
{
    if(obj.initialized) {
        stream << "obj.id = " << obj.id << "\n";
        stream << "\n";
        return stream;
    } else {
        stream << "<uninitialized virtual screen>";
    }
    return stream;
}

//monitor

Monitor::Monitor()
{
    
}

std::ostream & operator<<(std::ostream & stream, const Monitor & obj)
{
    if(obj.initialized) {
        stream << "obj.id = " << obj.id << "\n";
        stream << "obj.name = " << obj.name << "\n";
        stream << "\n";        
    } else {
        stream << "<uninitialized monitor>";
    }
    return stream;    
}

//window

Window::Window(double x0, double y0, double x1, double y1)
{
    this->x0 = x0;
    this->y0 = y0;
    this->x1 = x1;
    this->y1 = y1;
}

std::ostream & operator<<(std::ostream & stream, const Window & obj)
{    
    stream << "obj.x0 = " << obj.x0 << ", obj.y0 = " << obj.y0 << ", obj.x1 = " << obj.x1 << ", obj.y1 = " << obj.y1 << "\n";
    stream << "obj.virtual_screen:\n";
    stream << obj.virtual_screen;
    stream << "obj.monitor:\n";
    stream << obj.monitor;
    return stream;
}


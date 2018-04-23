#include "window.hpp"

#include <iostream>
#include <cassert>

//--------virtual screen--------

Virtual_screen::Virtual_screen()
{
    
}

Virtual_screen::Virtual_screen(Virtual_screen & obj)
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
    }
    return is_valid;
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

//--------monitor--------

Monitor::Monitor()
{
    
}

Monitor::Monitor(Monitor & obj)
{
    this->initialized = obj.initialized;
    this->id = obj.id;
    this->name = obj.name;
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

//--------window--------

Window::Window()
{
    
}

Window::Window(const Window & obj)
{
    this->virtual_screen = obj.virtual_screen;
    this->monitor = obj.monitor;
    this->window_split_screen = obj.window_split_screen;
    this->x0 = obj.x0;
    this->y0 = obj.y0;
    this->x1 = obj.x1;
    this->y1 = obj.y1;
    this->fullscreen = obj.fullscreen;
}

void Window::set_dimentions(double x0, double y0, double x1, double y1)
{
    this->x0 = x0;
    this->y0 = y0;
    this->x1 = x1;
    this->y1 = y1;
}

void Window::set_dimentions(bool fullscreen)
{
    if(!fullscreen) {
        std::cerr << "error: fullscreen must be true\n";
        exit(1);
    }
    this->fullscreen = fullscreen;
}

bool Window::is_valid() const
{    
    bool is_valid = true;
    if(!this->fullscreen) {
        is_valid = is_valid && VALID_WINDOW_SIZE(this->x0,this->y0,this->x1,this->y1);
        MY_ASSERT(is_valid);
    }
    is_valid = is_valid && this->monitor.is_valid(); MY_ASSERT(is_valid);
    is_valid = is_valid && this->virtual_screen.is_valid(); MY_ASSERT(is_valid);
    is_valid = is_valid && this->window_split_screen.is_valid(); MY_ASSERT(is_valid);

    if(!is_valid) {
        std::cerr << "error: Window, is_valid = " << is_valid << "\n";
    }
    return is_valid;
}

std::ostream & operator<<(std::ostream & stream, const Window & obj)
{
    if(obj.is_valid()) {
        if(obj.fullscreen) {
            stream << "obj.fullscreen = true<BR>";
        } else {
            stream << "obj.fullscreen = false<BR>";
            stream << "obj.x0 = " << obj.x0 << ", obj.y0 = " << obj.y0 << ", obj.x1 = " << obj.x1 << ", obj.y1 = " << obj.y1 << "<BR>";
        }
        stream << "obj.virtual_screen:<blockquote>";
        stream << obj.virtual_screen;
        stream << "</blockquote>";
        stream << "obj.monitor:<blockquote>";
        stream << obj.monitor;
        stream << "</blockquote>";
        stream << "obj.window_layout<blockquote>";
        stream << obj.window_split_screen;
        stream << "</blockquote>";
    } else {
        stream << "[uninitialized window]";
    }

    return stream;
}


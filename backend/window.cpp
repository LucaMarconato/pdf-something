#include "window.hpp"

#include <iostream>

Window::Window() {}

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

void swap(Window & obj1, Window & obj2)
{
    std::swap(obj1.virtual_screen,obj2.virtual_screen);
    std::swap(obj1.monitor,obj2.monitor);
    std::swap(obj1.window_split_screen,obj2.window_split_screen);
    std::swap(obj1.x0,obj2.x0);
    std::swap(obj1.y0,obj2.y0);
    std::swap(obj1.x1,obj2.x1);
    std::swap(obj1.y1,obj2.y1);
    std::swap(obj1.fullscreen,obj2.fullscreen);
}

Window & Window::operator=(Window obj)
{
    swap(*this,obj);
    return *this;
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
        MY_ASSERT(false); exit(1);
    }
    this->fullscreen = fullscreen;
}

bool Window::is_valid() const
{    
    bool is_valid = true;
    if(!this->fullscreen) {
        is_valid = is_valid && VALID_WINDOW_SIZE(this->x0,this->y0,this->x1,this->y1);
    }
    is_valid = is_valid && this->monitor.is_valid();
    is_valid = is_valid && this->virtual_screen.is_valid();
    is_valid = is_valid && this->window_split_screen.is_valid();

    if(!is_valid) {
        std::cerr << "error: Window, is_valid = " << is_valid << "\n";
        MY_ASSERT(false); exit(1);
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


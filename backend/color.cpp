#include "color.hpp"

#include <iostream>

Color::Color()
{
    this->rgb(0,0,0);
}

Color::Color(double r, double g, double b)
{
    this->rgb(r,g,b);
    this->initialized = true;
}

void Color::rgb(double r, double g, double b)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->initialized = true;
}

std::ostream & operator<<(std::ostream & stream, const Color & obj)
{
    if(obj.initialized) {
        stream << "obj.r = " << obj.r << ", obj.g = " << obj.g << ", obj.b = " << obj.b;
    } else {
        stream << "<uninitalized color>";
    }    
    return stream;
}

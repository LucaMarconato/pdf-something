#include "color.hpp"

#include <iostream>

Color::Color()
{
    this->rgb(0,0,0);
}

Color::Color(double r, double g, double b)
{
    this->rgb(r,g,b);
}

void Color::rgb(double r, double g, double b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}

inline bool Color::is_valid() const
{    
    if(this->r >= 0 && this->r <= 1 &&
       this->g >= 0 && this->g <= 1 &&
       this->b >= 0 && this->b <= 1) {
        return true;
    } else {
        std::cerr << "warning: r = " << r << ", g = " << g << ", b = " << b << "\n";
        return false;
    }
}

std::ostream & operator<<(std::ostream & stream, const Color & obj)
{
    if(obj.is_valid()) {
        stream << "obj.r = " << obj.r << ", obj.g = " << obj.g << ", obj.b = " << obj.b;
    } else {
        stream << "<uninitalized color>";
    }    
    return stream;
}

#include "highlighting.hpp"

#include <iostream>

//highlighting

Highlighting::Highlighting(Document & parent) : parent_document(parent) 
{

}

std::ostream & operator <<(std::ostream & stream, const Highlighting & obj)
{
    if(obj.initialized) {
        stream << "obj.uuid.uuid_string = " << obj.uuid.uuid_string << "\n";
        stream << "obj.color:\n";
        stream << obj.color << "\n";
        stream << "obj.parent_document:\n";
        stream << obj.parent_document << "\n";
        stream << "obj.components:\n";
        for(auto && component : obj.components) {
            stream << component << "\n";
        }        
    } else {
        stream << "<uninitialized highighting>";
    }
    return stream;
}

//highlighting component

Highlighting_component::Highlighting_component(Highlighting & parent, Pdf_page & in_page, double x0, double y0, double x1, double y1)
    : parent_highlighting(parent), in_page(in_page)
{
    if(x0 < x1 && y0 < y1 &&
       MIN_X <= x0 && x1 <= MAX_X &&
       MIN_Y <= y0 && y1 <= MAX_Y) {        
        this->x0 = x0;
        this->x1 = x1;
        this->y0 = y0;
        this->y1 = y1;
        
        this->initialized = true;
    } else {
        std::cerr << "error: x0 = " << x0 << ", y0 = " << y0 << ", x1 = " << x1 << ", y1 = " << y1 << "\n";
    }
}

std::ostream & operator <<(std::ostream & stream, const Highlighting_component & obj)
{
    if(obj.initialized) {
        stream << "obj.uuid.uuid_string = " << obj.uuid.uuid_string << "\n";
        stream << "&obj.parent_highlighting = " << &obj.parent_highlighting << "\n";
        stream << "&obj.in_page = " << &obj.in_page << "\n";
        stream << "obj.x0 = " << obj.x0 << ", obj.y0 = " << obj.y0 << ", obj.x1 = " << obj.x1 << ", obj.y1 = " << obj.y1;
    } else {
        stream << "<uninitialized highlighting component>";
    }
    return stream;
}

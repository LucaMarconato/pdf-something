#include "highlighting.hpp"

#include <iostream>

//highlighting

Highlighting::Highlighting(Document * in_document) : in_document(in_document) 
{

}

inline bool Highlighting::is_valid() const
{
    bool is_valid = true;

    is_valid = is_valid && this->uuid.is_valid();
    is_valid = is_valid && this->in_document != nullptr;
    is_valid = is_valid && this->color.is_valid();
    is_valid = is_valid && this->highlighting_components.size() > 0;

    if(!is_valid) {
        std::cerr << "error: highlighting is not valid\n";
    }
    return is_valid;
}

std::ostream & operator <<(std::ostream & stream, const Highlighting & obj)
{
    if(obj.is_valid()) {
        stream << "obj.uuid = " << obj.uuid << "<BR>";
        stream << "obj.color = " << obj.color << "<BR>";
        stream << "obj.in_document = " << obj.in_document << "<BR>";
        stream << "obj.highlighting_components:";
        for(auto && highlighting_component : obj.highlighting_components) {
            stream << "<blockquote>";
            stream << "-highlighting_component<BR>";
            stream << highlighting_component;
            stream << "</blockquote>";
        }
    } else {
        stream << "[uninitialized highighting]";
    }
    return stream;
}

//highlighting component

bool Highlighting_component::is_valid() const
{
    bool is_valid = true;

    is_valid = is_valid && VALID_PAGE_COORDINATES(x0,y0,x1,y1);
    is_valid = is_valid && this->uuid.is_valid();
    is_valid = is_valid && this->parent_highlighting != nullptr;
    is_valid = is_valid && this->in_page != nullptr;

    if(!is_valid) {
        std::cerr << "error: highlighting component is not valid\n";
    }
    return is_valid;
}


std::ostream & operator <<(std::ostream & stream, const Highlighting_component & obj)
{
    if(obj.is_valid()) {
        stream << "obj.uuid = " << obj.uuid << "<BR>";
        stream << "obj.in_page = " << obj.in_page << "<BR>";
        stream << "obj.x0 = " << obj.x0 << ", obj.y0 = " << obj.y0 << ", obj.x1 = " << obj.x1 << ", obj.y1 = " << obj.y1 << "<BR>";
        stream << "obj.parent_highlighting = " << obj.parent_highlighting << "<BR>";
        stream << "*obj.parent_highlighting:";
        stream << "<blockquote>";
        stream << *obj.parent_highlighting;
        stream << "</blockquote>";
    } else {
        stream << "[uninitialized highlighting component]";
    }
    return stream;
}

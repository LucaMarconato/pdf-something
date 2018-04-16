#include "pdf_document.hpp"

#include <iostream>

//pdf page
Pdf_page::Pdf_page(Pdf_document & in_document) : in_document(in_document)
{
    this->compute_size();
    this->initialized = true;
}

void Pdf_page::compute_size()
{
    std::cout << "TODO: Pdf_page::compute_size() to be implemented, using a fixed choice.\n";
    this->width = 100;
    this->height = 200;
}

std::ostream & operator<<(std::ostream & stream, const Pdf_page & obj)
{
    //obj.initialized is located in the Document superclass
    if(obj.initialized) {
        stream << "obj.in_docuent:\n";
        stream << obj.in_document << "\n";
        stream << "obj.width = " << obj.width << "\n";
        stream << "obj.height = " << obj.height;
    } else {
        stream << "<uninitialized pdf page>";
    }
    return stream;
}

//pdf document
std::ostream & operator<<(std::ostream & stream, const Pdf_document & obj)
{
    //call the stream operator in the superclass to see also its content    
    const Document & parent(obj);
    stream << parent << "\n";
    
    if(obj.initialized) {
        stream << "obj.pages.size() = " << obj.pages.size() << "\n";
        stream << "obj.pages:\n";
        for(auto && page : obj.pages) {
            stream << page << "\n";
        }
    } else {
        stream << "<uninitialized pdf document>";
    }
    return stream;
}

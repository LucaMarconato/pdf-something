#include "pdf_page.hpp"

#include <iostream>
#include <set>
#include <list>

#include "uuid.hpp"
#include "datetime.hpp"
#include "database/resources_manager.hpp"
#include "database/mediator.hpp"

#define VALID_WIDTH(width) (width > 0 && width < this->MAX_WIDTH)
#define VALID_HEIGHT(height) (height > 0 && height < this->MAX_HEIGHT)
#define VALID_INDEXES(index,index_in_pdf) (index < this->MAX_INDEX && index_in_pdf < this->MAX_INDEX)

/*
  This constructor is needed by std::map beucase it must be able to create new empty objects.
  If we do not like this constructor to be public we can make this class a friend of std::map
*/

Pdf_page::Pdf_page()
{
    
}

Pdf_page::Pdf_page(Pdf_document * in_document) : in_document(in_document)
{
    this->compute_size();
}

Pdf_page::Pdf_page(const Pdf_page & obj)
{
    this->in_document = obj.in_document;
    this->width = obj.width;
    this->height = obj.height;
    this->index = obj.index;
    this->index_in_pdf = obj.index_in_pdf;
}

Pdf_page & Pdf_page::operator=(Pdf_page & obj)
{
    Pdf_page to_swap = Pdf_page(obj);
    swap(*this,to_swap);
    return *this;
}

void swap(Pdf_page & obj1, Pdf_page & obj2)
{
    std::swap(obj1.in_document,obj2.in_document);
    std::swap(obj1.width,obj2.width);
    std::swap(obj1.height,obj2.height);
    std::swap(obj1.index,obj2.index);
    std::swap(obj1.index_in_pdf,obj2.index_in_pdf);
}

void Pdf_page::compute_size()
{
    // TODO: Pdf_page::compute_size() to be implemented, using a fixed choice
    this->width = 100;
    this->height = 200;
}

inline bool Pdf_page::is_valid() const
{
    bool is_valid = true;
    is_valid = is_valid && this->uuid.is_valid();

    if(!VALID_WIDTH(this->width) || !VALID_HEIGHT(this->height) || !VALID_INDEXES(this->index,this->index_in_pdf)) {
        is_valid = false;
        std::cerr << "warning: this->width = " << this->width << ", this->height = " << this->height << ", this->index = " << this->index << ", this->index_in_pdf = " << this->index_in_pdf << "\n";
    }
    if(this->in_document == nullptr) {
        is_valid = false;
        std::cerr << "warning: this->in_doument is not initialized\n";        
    }
    if(!is_valid) {
        std::cerr << "error: Pdf_page, is_valid = " << is_valid << "\n";
    }
    return is_valid;
}

std::ostream & operator<<(std::ostream & stream, const Pdf_page & obj)
{
    //obj.initialized is located in the Document superclass
    if(obj.is_valid()) {
        stream << "obj.uuid = " << obj.uuid << "<BR>";
        stream << "obj.in_document:<BR>";
        stream << "<blockquote>";
        stream << obj.in_document << "<BR>";
        stream << "</blockquote>";
        stream << "obj.width = " << obj.width << "<BR>";
        stream << "obj.height = " << obj.height << "<BR>";
        stream << "obj.index = " << obj.index << "<BR>";
        stream << "obj.index_in_pdf = " << obj.index_in_pdf << "<BR>";
        stream << "obj.highlighting_components:<BR>";
        for(auto && h: obj.highlighting_components) {
            stream << "-higlighting_component:";
            stream << "<blockquote>";
            stream << h << "<BR>";
            stream << "*h:<BR>";
            stream << *h;
            stream << "</blockquote>";
        }
    } else {
        stream << "<uninitialized pdf page>";
    }
    return stream;
}


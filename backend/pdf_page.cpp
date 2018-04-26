#include "pdf_page.hpp"

#include <iostream>
#include <set>
#include <list>

#include "uuid.hpp"
#include "datetime.hpp"
#include "database/resources_manager.hpp"
#include "database/mediator.hpp"

Pdf_page::Pdf_page() {}

// Pdf_page::Pdf_page(const Pdf_page & obj)
// {
//     this->in_document = obj.in_document;
//     this->width = obj.width;
//     this->height = obj.height;
//     this->index = obj.index;
//     this->index_in_pdf = obj.index_in_pdf;
//     this->x0_crop = obj.x0_crop;
//     this->y0_crop = obj.y0_crop;
//     this->x1_crop = obj.x1_crop;
//     this->y1_crop = obj.y1_crop;
//     this->highlighting_components = obj.highlighting_components;
// }

// Pdf_page & Pdf_page::operator=(Pdf_page & obj)
// {
//     swap(*this,obj);
//     return *this;
// }

// void swap(Pdf_page & obj1, Pdf_page & obj2)
// {
//     std::swap(obj1.in_document,obj2.in_document);
//     std::swap(obj1.width,obj2.width);
//     std::swap(obj1.height,obj2.height);
//     std::swap(obj1.index,obj2.index);
//     std::swap(obj1.index_in_pdf,obj2.index_in_pdf);
//     std::swap(obj1.x0_crop,obj2.x0_crop);
//     std::swap(obj1.y0_crop,obj2.y0_crop);
//     std::swap(obj1.x1_crop,obj2.x1_crop);
//     std::swap(obj1.y1_crop,obj2.y1_crop);
//     std::swap(obj1.highlighting_components,obj2.highlighting_components);
// }

void Pdf_page::compute_size()
{
    // TODO: Pdf_page::compute_size() to be implemented in the frontend, filling with dummy values
    this->width = 100;
    this->height = 200;
}

inline bool Pdf_page::is_valid() const
{
    bool is_valid = true;
    is_valid = is_valid && this->in_document != nullptr;
    is_valid = is_valid && this->uuid.is_valid();
    is_valid = is_valid && VALID_PAGE_INDEX(this->index);
    is_valid = is_valid && VALID_PAGE_INDEX(this->index_in_pdf);
    is_valid = is_valid && VALID_PAGE_COORDINATES(this->x0_crop, this->y0_crop, this->x1_crop, this->y1_crop);
    is_valid = is_valid && VALID_PAGE_WIDTH(this->width);
    is_valid = is_valid && VALID_PAGE_HEIGHT(this->height);

    if(!is_valid) {
        std::cerr << "error: Pdf_page, is_valid = " << is_valid << "\n";
    }
    return is_valid;
}

bool Pdf_page::operator==(const Pdf_page & obj) const
{
    bool is_equal = true;
    is_equal = is_equal && this->in_document == obj.in_document;
    is_equal = is_equal && this->uuid == obj.uuid;
    is_equal = is_equal && this->index == obj.index;
    is_equal = is_equal && this->index_in_pdf == obj.index_in_pdf;
    is_equal = is_equal && this->highlighting_components == obj.highlighting_components;
    is_equal = is_equal && this->x0_crop == obj.x0_crop;
    is_equal = is_equal && this->y0_crop == obj.y0_crop;
    is_equal = is_equal && this->x1_crop == obj.x1_crop;
    is_equal = is_equal && this->y1_crop == obj.y1_crop;
    is_equal = is_equal && this->width == obj.width;
    is_equal = is_equal && this->height == obj.height;
    return is_equal;
}

std::ostream & operator<<(std::ostream & stream, const Pdf_page & obj)
{
    //obj.initialized is located in the Document superclass
    if(obj.is_valid()) {
        stream << "obj.in_document = " << obj.in_document << "<BR>";
        stream << "obj.uuid = " << obj.uuid << "<BR>";
        stream << "obj.index = " << obj.index << "<BR>";
        stream << "obj.index_in_pdf = " << obj.index_in_pdf << "<BR>";
        stream << "obj.x0_crop = " << obj.x0_crop << ", obj.y0_crop = " << obj.y0_crop << ", obj.x1_crop = " << obj.x1_crop << ", obj.y1_crop = " << obj.y1_crop << "<BR>";
        stream << "obj.width = " << obj.width << "<BR>";
        stream << "obj.height = " << obj.height << "<BR>";
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
        stream << "[uninitialized pdf page]";
    }
    return stream;
}


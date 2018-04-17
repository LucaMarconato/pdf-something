#include "pdf_document.hpp"

#include <iostream>

#include "uuid.hpp"
#include "datetime.hpp"

//----------------pdf page----------------
Pdf_page::Pdf_page(Pdf_document & in_document, unsigned int index) : in_document(in_document)
{
    this->compute_size();
    this->index = index;
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
        stream << "obj.height = " << obj.height << "\n";
        stream << "obj.index = " << obj.index;
    } else {
        stream << "<uninitialized pdf page>";
    }
    return stream;
}

//----------------pdf document----------------
Pdf_document::Pdf_document(json const & j)
{
    std::cout << "j[\"format\"] = " << j["format"] << "\n";
    this->uuid = Uuid(j["uuid"].get<std::string>());
    this->in_program_directory = j["in_program_directory"].get<std::string>();
    this->name = j["name"].get<std::string>();
    this->latest_opening = Datetime(j["latest_opening"].get<std::string>());
    this->initialized = true;
}

void Pdf_document::load_all_pages(json const & j)
{
    if(this->pages.size() > 0 || this->numbering.size() > 0) {
        std::cerr << "error: this->pages.size() = " << this->pages.size() << ", this->numbering.size() = " << this->numbering.size() << "\n";
        return;
    }
    for(auto && j_page : j["pages"]) {
        Uuid uuid(j_page["uuid"].get<std::string>());

        auto & j_highlightings = j_page.front();
        std::cout << "j_highlightings.size() = " << j_highlightings.size() << "\n";
    }
}

std::ostream & operator<<(std::ostream & stream, const Pdf_document & obj)
{
    //call the stream operator in the superclass to see also its content    
    const Document & parent(obj);
    stream << parent << "\n";
    
    if(obj.initialized) {
        stream << "obj.pages.size() = " << obj.pages.size() << "\n";
        stream << "obj.pages:\n";
        for(auto && page : obj.pages) {
            stream << page.second << "\n";
        }
    } else {
        stream << "<uninitialized pdf document>";
    }
    return stream;
}

Pdf_document::~Pdf_document()
{
    
}

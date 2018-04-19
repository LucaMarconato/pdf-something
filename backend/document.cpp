#include "document.hpp"

#include <iostream>

#include <nlohmann/json.hpp>

#include "pdf_document.hpp"

using json = nlohmann::json;

Document * Document::parse_document(char * file_content)
{
    // std::cout << "file_content = " << file_content << "\n";
    auto j = json::parse(file_content);
    if(j["format"] == "pdf") {        
        Pdf_document * document = new Pdf_document(j);
        document->load_all_pages(j);
        return document;
    } else {
        std::cout << "\"" << j["format"] << "\" format is not supported\n";
        return nullptr;
    }
}

std::string Document::serialize_to_json()
{
    return "{\n\t\"TODO:\" : \"serialize_to_json()\"\n}";
}

bool Document::is_valid() const
{    
    return this->is_valid_base();
}

bool Document::is_valid_base() const
{
    bool is_valid = true;
    is_valid = is_valid && this->uuid.is_valid();
    is_valid = is_valid && this->latest_opening.is_valid();
    if(this->in_program_directory == "") {
        std::cerr << "warning: this->in_program_directory = " << this->in_program_directory << "\n";
        is_valid = false;
    }
    if(this->name == "") {
        std::cerr << "warning: this->name = " << this->name << "\n";
    }
    
    if(!is_valid) {
        std::cerr << "error: is_valid = " << is_valid << "\n";
    }
    return is_valid;
}

std::ostream & operator<<(std::ostream & stream, const Document & obj)
{
    obj.print(stream);
    return stream;
}

void Document::load_all_pages(json const &j)
{
    std::cerr << "warning: who called me (Document::load_all_pages())?\n";
}

void Document::print(std::ostream & stream) const
{
if (this->is_valid())
    {
        stream << "this->uuid = " << this->uuid << "<BR>";
        stream << "this->in_program_directory = " << this->in_program_directory << "<BR>";
        stream << "this->name = " << this->name << "<BR>";
        stream << "this->latest_opening = " << this->latest_opening;
    } else {
        stream << "<uninitialized document>";
    }

}

Document::~Document()
{
    
}

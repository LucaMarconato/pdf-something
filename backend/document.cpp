#include "document.hpp"

#include <iostream>
#include <memory>

#include <nlohmann/json.hpp>

#include "pdf_document.hpp"

using json = nlohmann::json;

std::shared_ptr<Document> Document::parse_document(char * file_content)
{
    // std::cout << "file_content = " << file_content << "\n";
    auto j = json::parse(file_content);
    if(j["format"] == "pdf") {        
        std::shared_ptr<Document> document = std::make_shared<Pdf_document>(Pdf_document(j));
        std::shared_ptr<Pdf_document> pdf_document = std::dynamic_pointer_cast<Pdf_document>(document);
        pdf_document->load_all_pages(j);
        return document;
    } else {
        std::cout << "\"" << j["format"] << "\" format is supported\n";
        return std::make_shared<Document>();
    }
}

std::string Document::serialize_to_json()
{
    return "{\n\t\"TODO:\" : \"serialize_to_json()\"\n}";
}

std::ostream & operator<<(std::ostream & stream, const Document & obj)
{
    if(obj.initialized) {
        stream << "obj.uuid = " << obj.uuid << "\n";
        stream << "obj.in_program_directory = " << obj.in_program_directory << "\n";
        stream << "obj.name = " << obj.name << "\n";
        stream << "obj.latest_opening = " << obj.latest_opening;
    } else {
        stream << "<uninitialized document>";
    }
    return stream;
}

Document::~Document()
{
    
}

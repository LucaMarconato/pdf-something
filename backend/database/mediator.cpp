#include "mediator.hpp"

#include "../io/file.hpp"
#include "../windows_configuration.hpp"

#include <iostream>

Uuid Mediator::get_latest_opened_pdf()
{
    return Uuid(Database::latest_opened_pdf);
}
Document * Mediator::document_for_uuid(Uuid const & uuid)
{
    //to make the code more readable
    std::map<Uuid, Document *> loaded = Resources_manager::loaded_documents;
    
    auto e = loaded.find(uuid);
    if(e == loaded.end()) {
        char * buffer = Database::read_document(uuid);
        auto document = Document::parse(buffer);
        delete [] buffer;
        Resources_manager::loaded_documents[uuid] = document;
        return document;
    } else {
        return e->second;
    }    
}

Pdf_page * Mediator::pdf_page_for_uuid(Uuid const & uuid, Pdf_document * in_document)
{
    //to make the code more readable
    std::map<Uuid, Pdf_page *> loaded = Resources_manager::loaded_pdf_pages;
    
    auto e = loaded.find(uuid);
    if(e == loaded.end()) {        
        Pdf_page * pdf_page = new Pdf_page(in_document);
        pdf_page->uuid = uuid;
        Resources_manager::loaded_pdf_pages.insert(std::make_pair(uuid,pdf_page));
        return pdf_page;
    } else {
        //integrity check
        if(e->second->in_document != in_document) {
            std::cerr << "error: e->second->in_document = " << e->second->in_document << ", in_document = " << in_document << "\n";
            exit(1);
        }
        return e->second;
    }
}

Highlighting * Mediator::highlighting_for_uuid(Uuid const & uuid, Document * in_document)
{
    //to make the code more readable
    std::map<Uuid, Highlighting *> loaded = Resources_manager::loaded_highlightings;
    
    auto e = loaded.find(uuid);
    if(e == loaded.end()) {
        Highlighting * highlighting = new Highlighting(in_document);
        highlighting->uuid = uuid;
        Resources_manager::loaded_highlightings.insert(std::make_pair(uuid,highlighting));
        return highlighting;
    } else {
        //integrity check
        if(e->second->in_document != in_document) {
            std::cerr << "error: e->second->in_document = " << e->second->in_document << ", in_document = " << in_document << "\n";
            exit(1);
        }
        return e->second;
    }    
}

Highlighting_component * Mediator::highlighting_component_for_uuid(Uuid const & uuid)
{
    //to make the code more readable
    std::map<Uuid, Highlighting_component *> loaded = Resources_manager::loaded_highlighting_components;
    
    auto e = loaded.find(uuid);
    if(e == loaded.end()) {
        Highlighting_component * highlighting_component = new Highlighting_component();
        highlighting_component->uuid = uuid;
        Resources_manager::loaded_highlighting_components.insert(std::make_pair(uuid,highlighting_component));
        return highlighting_component;
    } else {
        return e->second;
    }
}

void Mediator::load_latest_windows_configuration()
{
    char * buffer = Database::read_latest_windows_configuration();
    Windows_configuration::parse(buffer);
    
    delete [] buffer;
}

bool Mediator::document_is_loaded(Uuid uuid)
{
    auto e = Resources_manager::loaded_documents.find(uuid);
    if(e == Resources_manager::loaded_documents.end()) {
        return false;
    } else {
        return true;
    }
}
bool Mediator::pdf_page_is_loaded(Uuid uuid)
{
    auto e = Resources_manager::loaded_pdf_pages.find(uuid);
    if(e == Resources_manager::loaded_pdf_pages.end()) {
        return false;
    } else {
        return true;
    }
}
bool Mediator::highlighting_is_loaded(Uuid uuid)
{
    auto e = Resources_manager::loaded_highlightings.find(uuid);
    if(e == Resources_manager::loaded_highlightings.end()) {
        return false;
    } else {
        return true;
    }
}
bool Mediator::highlighting_component_is_loaded(Uuid uuid)
{
    auto e = Resources_manager::loaded_highlighting_components.find(uuid);
    if(e == Resources_manager::loaded_highlighting_components.end()) {
        return false;
    } else {
        return true;
    }
}

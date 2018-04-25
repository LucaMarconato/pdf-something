#include "mediator.hpp"

#include "../io/file.hpp"
#include "../windows_configuration.hpp"
#include "../timer.hpp"

#include <iostream>

Uuid Mediator::get_latest_opened_pdf()
{
    return Uuid(Database::latest_opened_pdf);
}

Document * Mediator::document_for_uuid(Uuid const & uuid)
{
    // to make the code more readable
    std::unordered_map<Compact_uuid, Document *> & loaded = Resources_manager::loaded_documents;
    
    auto e = loaded.find(uuid.compact_uuid);
    if(e == loaded.end()) {
        char * buffer = Database::read_document(uuid);
        Document * document = Document::parse(buffer);
        delete [] buffer;
        loaded[uuid.compact_uuid] = document;
        return document;
    } else {
        return e->second;
    }    
}

Pdf_page * Mediator::pdf_page_for_uuid(Uuid const & uuid)
{
    std::unordered_map<Compact_uuid, Pdf_page *> & loaded = Resources_manager::loaded_pdf_pages;

    auto e = loaded.find(uuid.compact_uuid);
    if(e == loaded.end()) {
        Pdf_page * pdf_page = Resources_manager::get_new_pdf_page();
        pdf_page->uuid = uuid;
        loaded[uuid.compact_uuid] = pdf_page;
        return pdf_page;
    } else {
        return e->second;
    }
}

Highlighting * Mediator::highlighting_for_uuid(Uuid const & uuid)
{
    std::unordered_map<Compact_uuid, Highlighting *> & loaded = Resources_manager::loaded_highlightings;

    auto e = loaded.find(uuid.compact_uuid); 
    if(e == loaded.end()) {
        Highlighting * highlighting = Resources_manager::get_new_highlighting(); 
        highlighting->uuid = uuid;
        loaded[uuid.compact_uuid] = highlighting;
        return highlighting;
    } else {
        return e->second;
    }    
}

Highlighting_component * Mediator::highlighting_component_for_uuid(Uuid const & uuid)
{
    std::unordered_map<Compact_uuid, Highlighting_component *> & loaded = Resources_manager::loaded_highlighting_components;

    auto e = loaded.find(uuid.compact_uuid);
    if(e == loaded.end()) {
        Highlighting_component * highlighting_component = Resources_manager::get_new_highlighting_component();
        highlighting_component->uuid = uuid;
        loaded[uuid.compact_uuid] = highlighting_component;
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

bool Mediator::document_is_loaded(Uuid & uuid)
{
    auto e = Resources_manager::loaded_documents.find(uuid.compact_uuid);
    if(e == Resources_manager::loaded_documents.end()) {
        return false;
    } else {
        return true;
    }
}
bool Mediator::pdf_page_is_loaded(Uuid & uuid)
{
    auto e = Resources_manager::loaded_pdf_pages.find(uuid.compact_uuid);
    if(e == Resources_manager::loaded_pdf_pages.end()) {
        return false;
    } else {
        return true;
    }
}
bool Mediator::highlighting_is_loaded(Uuid & uuid)
{
    auto e = Resources_manager::loaded_highlightings.find(uuid.compact_uuid);
    if(e == Resources_manager::loaded_highlightings.end()) {
        return false;
    } else {
        return true;
    }
}
bool Mediator::highlighting_component_is_loaded(Uuid & uuid)
{
    auto e = Resources_manager::loaded_highlighting_components.find(uuid.compact_uuid);
    if(e == Resources_manager::loaded_highlighting_components.end()) {
        return false;
    } else {
        return true;
    }
}

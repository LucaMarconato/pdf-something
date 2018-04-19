#include "resources_manager.hpp"

bool Resources_manager::document_is_loaded(Uuid uuid)
{
    auto e = Resources_manager::loaded_documents.find(uuid);
    if(e == Resources_manager::loaded_documents.end()) {
        return false;
    } else {
        return true;
    }
}
bool Resources_manager::pdf_page_is_loaded(Uuid uuid)
{
    auto e = Resources_manager::loaded_pdf_pages.find(uuid);
    if(e == Resources_manager::loaded_pdf_pages.end()) {
        return false;
    } else {
        return true;
    }
}
bool Resources_manager::highlighting_is_loaded(Uuid uuid)
{
    auto e = Resources_manager::loaded_highlightings.find(uuid);
    if(e == Resources_manager::loaded_highlightings.end()) {
        return false;
    } else {
        return true;
    }
}
bool Resources_manager::highlighting_component_is_loaded(Uuid uuid)
{
    auto e = Resources_manager::loaded_highlighting_components.find(uuid);
    if(e == Resources_manager::loaded_highlighting_components.end()) {
        return false;
    } else {
        return true;
    }
}

std::map<Uuid, std::shared_ptr<Document>> Resources_manager::loaded_documents;
std::map<Uuid, std::shared_ptr<Pdf_page>> Resources_manager::loaded_pdf_pages;
std::map<Uuid, std::shared_ptr<Highlighting>> Resources_manager::loaded_highlightings;
std::map<Uuid, std::shared_ptr<Highlighting_component>> Resources_manager::loaded_highlighting_components;

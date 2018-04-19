#ifndef RESOURCES_MANAGER_H
#define RESOURCES_MANAGER_H

#include <map>
#include <memory>

#include "../uuid.hpp"
#include "../document.hpp"
#include "../pdf_document.hpp"
#include "../highlighting.hpp"

class Resources_manager {
public:
    static bool document_is_loaded(Uuid uuid);
    static bool pdf_page_is_loaded(Uuid uuid);
    static bool highlighting_is_loaded(Uuid uuid);
    static bool highlighting_component_is_loaded(Uuid uuid);
protected:
    static std::map<Uuid, std::shared_ptr<Document>> loaded_documents;
    static std::map<Uuid, std::shared_ptr<Pdf_page>> loaded_pdf_pages;
    static std::map < Uuid, std::shared_ptr<Highlighting>> loaded_highlightings;
    static std::map<Uuid, std::shared_ptr<Highlighting_component>> loaded_highlighting_components;
};

#endif //RESOURCES_MANAGER_H

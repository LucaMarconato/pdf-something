#ifndef RESOURCES_MANAGER_H
#define RESOURCES_MANAGER_H

#include <map>

#include "../uuid.hpp"
#include "../document.hpp"
#include "../pdf_page.hpp"
#include "../highlighting.hpp"

class Resources_manager {
protected:
    static std::map<Uuid, Document *> loaded_documents;
    static std::map<Uuid, Pdf_page *> loaded_pdf_pages;
    static std::map<Uuid, Highlighting *> loaded_highlightings;
    static std::map<Uuid, Highlighting_component *> loaded_highlighting_components;
};

#endif //RESOURCES_MANAGER_H

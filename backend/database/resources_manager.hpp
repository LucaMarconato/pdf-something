#ifndef RESOURCES_MANAGER_H
#define RESOURCES_MANAGER_H

#include <boost/unordered_map.hpp>

#include "../uuid.hpp"
#include "../document.hpp"
#include "../pdf_page.hpp"
#include "../highlighting.hpp"
#include "asynchronous_loader.hpp"

class Resources_manager {
public:
    // this method must be called as soon as possible when the application opens
    static void initialize_resources_caching();
protected:
    static boost::unordered_map<Uuid, Document *> loaded_documents;
    static boost::unordered_map<Uuid, Pdf_page *> loaded_pdf_pages;
    static boost::unordered_map<Uuid, Highlighting *> loaded_highlightings;
    static boost::unordered_map<Uuid, Highlighting_component *> loaded_highlighting_components;
    
    static Pdf_page * get_new_pdf_page();
    static Highlighting * get_new_highlighting();
    static Highlighting_component * get_new_highlighting_component();
};

#endif //RESOURCES_MANAGER_H

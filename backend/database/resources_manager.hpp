#ifndef RESOURCES_MANAGER_H
#define RESOURCES_MANAGER_H

#include <map>

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
    static std::map<Uuid, Document *> loaded_documents;
    static std::map<Uuid, Pdf_page *> loaded_pdf_pages;
    static Pdf_page * get_new_pdf_page();
    static std::map<Uuid, Highlighting *> loaded_highlightings;
    static Highlighting * get_new_highlighting();
    static std::map<Uuid, Highlighting_component *> loaded_highlighting_components;
    static Highlighting_component * get_new_highlighting_component();
};

#endif //RESOURCES_MANAGER_H


return Asynchronous_loader<Pdf_page,500>.get_instance().get_element();
return Asynchronous_loader<Highlighting,1000>.get_instance().get_element();
Highlighting_component * Resources_manager::get_new_highlighting_component()
{
    return Asynchronous_loader<Highlighting_component,1500>.get_instance().get_element();   
}

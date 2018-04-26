#ifndef RESOURCES_MANAGER_H
#define RESOURCES_MANAGER_H

#include <unordered_map>

#include "../uuid.hpp"
#include "../document.hpp"
#include "../pdf_page.hpp"
#include "../highlighting.hpp"
#include "asynchronous_loader.hpp"

class Resources_manager {
public:
    Resources_manager() = delete;
    /*
      If using the class Asynchronous_loader, then this method must be called as soon as possible, when the application opens.
      This function initialize some singleton template classes making them running a threads in background which loads some resources in memory.
    */
    static void initialize_resources_caching();
    
protected:
    /*
      Here are stored the relevant resources, the key of the maps is a 128bit representation of an UUID (a struct), since using the class Uuid in the key makes the code slower. The compact uuid of an Uuid object is built when the UUID is created and it is accessible via Uuid.compact_uuid.
      See also: https://github.com/LucaMarconato/pdf-something/issues/7
    */
    static std::unordered_map<Uuid, Document *> loaded_documents;
    /*
      Note the we should have a polymorphic class, say Page, instead of Pdf_page, like we do for Document instead of Pdf_document.
      We shall modify this in the future, but not now, since for the moment we are mainly focusing on .pdf files
    */
    static std::unordered_map<Uuid, Pdf_page *> loaded_pdf_pages;
    static std::unordered_map<Uuid, Highlighting *> loaded_highlightings;
    static std::unordered_map<Uuid, Highlighting_component *> loaded_highlighting_components;

    /*
      These function allocate the desired object. 
      new is called here, it is someone else responsibility to delete the memory: we will create a class which handle memory so not to exceed a certain limit and so to keep the most recently used objects in memory.
    */
    static Pdf_page * get_new_pdf_page();
    static Highlighting * get_new_highlighting();
    static Highlighting_component * get_new_highlighting_component();
};

#endif // RESOURCES_MANAGER_H

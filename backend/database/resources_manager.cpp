#include "resources_manager.hpp"

#define BUFFER_SIZE_PDF_PAGE 500
#define BUFFER_SIZE_HIGHLIGHTING 2000
#define BUFFER_SIZE_HIGHLIGHTING_COMPONENT 3000

void Resources_manager::initialize_resources_caching()
{
    Asynchronous_loader<Pdf_page,BUFFER_SIZE_PDF_PAGE>::get_instance();
    Asynchronous_loader<Highlighting,BUFFER_SIZE_HIGHLIGHTING>::get_instance();
    Asynchronous_loader<Highlighting_component,BUFFER_SIZE_HIGHLIGHTING_COMPONENT>::get_instance();
}

std::unordered_map<Uuid, Document *> Resources_manager::loaded_documents;
std::unordered_map<Uuid, Pdf_page *> Resources_manager::loaded_pdf_pages;
std::unordered_map<Uuid, Highlighting *> Resources_manager::loaded_highlightings;
std::unordered_map<Uuid, Highlighting_component *> Resources_manager::loaded_highlighting_components;

Pdf_page * Resources_manager::get_new_pdf_page()
{
    Pdf_page * pdf_page = new Pdf_page();
    // this option uses the asynchronous loading: new was already called in the background and it is just returned a pointer to the desired memory
    // Pdf_page * pdf_page = Asynchronous_loader<Pdf_page,BUFFER_SIZE_PDF_PAGE>::get_instance().get_element();
    return pdf_page;
}

Highlighting * Resources_manager::get_new_highlighting()
{
    Highlighting * highlighting = new Highlighting();
    // Highlighting * highlighting = Asynchronous_loader<Highlighting,BUFFER_SIZE_HIGHLIGHTING>::get_instance().get_element();
    return highlighting;
}

Highlighting_component * Resources_manager::get_new_highlighting_component()
{
    Highlighting_component * highlighting_component = new Highlighting_component();
    // Highlighting_component * highlighting_component = Asynchronous_loader<Highlighting_component,BUFFER_SIZE_HIGHLIGHTING_COMPONENT>::get_instance().get_element();
    return highlighting_component;
}

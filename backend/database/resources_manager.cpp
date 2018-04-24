#include "resources_manager.hpp"

void Resources_manager::initialize_resources_caching()
{
    Asynchronous_loader<Pdf_page,500>::get_instance();
    Asynchronous_loader<Highlighting,1000>::get_instance();
    Asynchronous_loader<Highlighting_component,1500>::get_instance();
}

boost::unordered_map<Uuid, Document *> Resources_manager::loaded_documents;
boost::unordered_map<Uuid, Pdf_page *> Resources_manager::loaded_pdf_pages;
boost::unordered_map<Uuid, Highlighting *> Resources_manager::loaded_highlightings;
boost::unordered_map<Uuid, Highlighting_component *> Resources_manager::loaded_highlighting_components;

Pdf_page * Resources_manager::get_new_pdf_page()
{
    return Asynchronous_loader<Pdf_page,500>::get_instance().get_element();
}

Highlighting * Resources_manager::get_new_highlighting()
{
    return Asynchronous_loader<Highlighting,2000>::get_instance().get_element();
}

Highlighting_component * Resources_manager::get_new_highlighting_component()
{
    return Asynchronous_loader<Highlighting_component,3000>::get_instance().get_element();
}

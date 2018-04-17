#include "resources_manager.hpp"

std::map<Uuid, Document> Resources_manager::loaded_documents;
std::map<Uuid, Pdf_Page> Resources_manager::loaded_pdf_pages;
std::map<Uuid, Highlighting> Resources_manager::loaded_highlightings;
std::map<Uuid, Highlighting_component> Resources_manager::loaded_highlighting_components;

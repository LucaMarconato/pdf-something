#include "mediator.hpp"

#include <iostream>
#include <memory>

Uuid Mediator::get_latest_opened_pdf()
{
    return Uuid(Database::latest_opened_pdf);
}
Document & Mediator::document_for_uuid(Uuid const & uuid)
{
    //to make the code more readable
    std::map<Uuid, Document> & loaded = Resources_manager::loaded_documents;
    
    auto e = loaded.find(uuid);
    if(e == loaded.end()) {
        File file;
        std::string file_path = "data/" + uuid.uuid_string + "/info.json";
        file.open(file_path, File::READ_BINARY);
        if(!file.is_open) {
            std::cerr << "error: unable to locate the document uuid = " << uuid << "\n";
            exit(1);
        } else {
            file.read_all_content(true);
            std::cout << "read " << file.size()/1024 << " KBs\n";
            auto document = Document::parse_document(file.content);
            Resources_manager::loaded_documents[uuid] = *(document.get());
            return Resources_manager::loaded_documents[uuid];
            file.close();
        }
    } else {
        return e->second;
    }    
}

Pdf_page & Mediator::pdf_page_for_uuid(Uuid const & uuid, Pdf_document & in_document, unsigned int index)
{
    //to make the code more readable
    std::map<Uuid, Pdf_page> & loaded = Resources_manager::loaded_pdf_pages;
    
    auto e = loaded.find(uuid);
    if(e == loaded.end()) {
        std::shared_ptr<Pdf_page> pdf_page = std::make_shared<Pdf_page>(Pdf_page(in_document, index));
        Resources_manager::loaded_pdf_pages[uuid] = *(pdf_page.get());
        return Resources_manager::loaded_pdf_pages[uuid];
    } else {
        Pdf_page & page = e->second;
        //integrity check
        if(e->in_document != in_document || e->index != index) {
            std::cerr << "error: e->in_document = " << e->in_document << ", in_document = " << in_document << ", e->index = " << e->index << ", index = " << index << "\n";
            exit(1);
        }
        return page;
    }
}

Highlighting & Mediator::highlighting_for_uuid(Uuid const & uuid)
{
    //to make the code more readable
    std::map<Uuid, Highlighting> & loaded = Resources_manager::loaded_highlightings;
    
    auto e = loaded.find(uuid);
    if(e == loaded.end()) {
        std::cerr << "WARNING: The highlighting is not loaded in memory, look in the big database\n";
        exit(1);
    } else {
        return e->second;
    }    
}

Highlighting_component & Mediator::highlighting_component_for_uuid(Uuid const & uuid)
{
    //to make the code more readable
    std::map<Uuid, Highlighting_component> & loaded = Resources_manager::loaded_highlighting_components;
    
    auto e = loaded.find(uuid);
    if(e == loaded.end()) {
        std::cerr << "WARNING: The highlighting component is not loaded in memory, look in the big database\n";
        exit(1);
    } else {
        return e->second;
    }
}

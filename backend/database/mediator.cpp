#include "mediator.hpp"

#include <iostream>

Uuid Mediator::get_latest_opened_pdf()
{
    return Uuid(Database::latest_opened_pdf);
}
std::shared_ptr<Document> Mediator::document_for_uuid(Uuid const & uuid)
{
    //to make the code more readable
    std::map<Uuid, std::shared_ptr<Document>> loaded = Resources_manager::loaded_documents;
    
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
            // std::cout << "read " << file.size()/1024 << " KBs\n";
            auto document = Document::parse_document(file.content);
            Resources_manager::loaded_documents[uuid] = document; 
            file.close();
            return document;
        }
    } else {
        return e->second;
    }    
}

std::shared_ptr<Pdf_page> Mediator::pdf_page_for_uuid(Uuid const & uuid, std::shared_ptr<Pdf_document> in_document)
{
    //to make the code more readable
    std::map<Uuid, std::shared_ptr<Pdf_page>> loaded = Resources_manager::loaded_pdf_pages;
    
    auto e = loaded.find(uuid);
    if(e == loaded.end()) {
        std::shared_ptr<Pdf_page> pdf_page = std::make_shared<Pdf_page>(Pdf_page(in_document));
        pdf_page->uuid = uuid;
        Resources_manager::loaded_pdf_pages.insert(std::make_pair(uuid,pdf_page));
        // Resources_manager::loaded_pdf_pages.insert(std::make_pair(uuid,*(pdf_page.get())));
        // Resources_manager::loaded_pdf_pages[uuid] = *(pdf_page.get());
        return Resources_manager::loaded_pdf_pages[uuid];
    } else {
        //integrity check
        if(e->second.get()->in_document != in_document) {
            std::cerr << "error: *(e->second.get())->in_document = " << *(e->second.get())->in_document << ", in_document = " << in_document << "\n";
            exit(1);
        }
        return e->second;
    }
}

std::shared_ptr<Highlighting> Mediator::highlighting_for_uuid(Uuid const & uuid)
{
    //to make the code more readable
    std::map<Uuid, std::shared_ptr<Highlighting>> loaded = Resources_manager::loaded_highlightings;
    
    auto e = loaded.find(uuid);
    if(e == loaded.end()) {
        std::cerr << "WARNING: The highlighting is not loaded in memory, look in the big database\n";
        exit(1);
    } else {
        return e->second;
    }    
}

std::shared_ptr<Highlighting_component> Mediator::highlighting_component_for_uuid(Uuid const & uuid)
{
    //to make the code more readable
    std::map<Uuid, std::shared_ptr<Highlighting_component>> loaded = Resources_manager::loaded_highlighting_components;
    
    auto e = loaded.find(uuid);
    if(e == loaded.end()) {
        std::cerr << "WARNING: The highlighting component is not loaded in memory, look in the big database\n";
        exit(1);
    } else {
        return e->second;
    }
}

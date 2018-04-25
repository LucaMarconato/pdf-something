#include "database.hpp"

#include <iostream>

#include "../io/file.hpp"

std::string Database::latest_opened_pdf = "84f3415d-4f59-4333-9f8b-b4f9f1e9a5fb";

char * Database::read_document(Uuid const & uuid)
{
    File file;
    std::string file_path = "data/" + uuid.to_string() + "/info.json";
    file.open(file_path, File::READ_BINARY);
    if(!file.is_open) {
        std::cerr << "error: unable to locate the document uuid = " << uuid << "\n";
        exit(1);
    } else {
        char * buffer = nullptr;
        file.read_all_content(true, &buffer);
        // std::cout << "read " << file.size()/1024 << " KBs\n";
        file.close();
        return buffer;
    }
}

char * Database::read_latest_windows_configuration()
{
    File file;
    std::string file_path = "data/latest_bigger.json";
    file.open(file_path, File::READ_BINARY);
    if(!file.is_open) {
        std::cerr << "error: unable to locate the latest windows configuration file\n";
        exit(1);
    } else {
        char * buffer = nullptr;
        file.read_all_content(true, &buffer);
        // std::cout << "read " << file.size()/1024 << " KBs\n";
        file.close();
        return buffer;
    }    
}

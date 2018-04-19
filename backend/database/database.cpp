#include "database.hpp"

#include "../io/file.hpp"

std::string Database::latest_opened_pdf = "84f3415d-4f59-4333-9f8b-b4f9f1e9a5fb";

// json Database::load_document(Uuid const & uuid)
// {
//     json to_return;
//     File file;
//     std::string file_path = "data/" + uuid.uuid_string + "/info.json";
//     file.open(file_path, File::READ_BINARY);
//     if(!file.is_open) {
//         std::cerr << "error: unable to locate the document uuid = " << uuid << "\n";
//         exit(1);
//     } else {
//         file.read_all_content(true);
// }

// json Database::latest_grid_layout()
// {

// }

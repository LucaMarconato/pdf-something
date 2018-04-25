#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <memory>

#include "../uuid.hpp"
#include "../document.hpp"
#include "../pdf_document.hpp"
#include "../highlighting.hpp"

class Database {
protected:
    /*
      The documents (.pdf, slides, etc.) are associated with an Uuid.
      Currently, they are stored as raw files accompanied by a .json file.
      This function reads the .json and return the null-terminated raw content of the .json file
      In the future we will drop the use of .json here because these .json files are unnecessarily big and we need a format to be indexed for random accesses, insertions and deletions.

      Important:
      -the caller function is responsible to delete the returned memory
    */    
    static char * read_document(Uuid const & uuid);
    /*
      Again, this is stored in a .json file.
      The .json file is always very small but we would need to update it everytime the user change pages, changes document, ...
      So we need to drop .json even here.

      Important:
      -the caller function is responsible to delete the returned memory
    */
    static char * read_latest_windows_configuration();
    static std::string latest_opened_pdf;
};

#endif //DATABASE_H

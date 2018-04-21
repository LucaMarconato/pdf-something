#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <map>
#include <memory>

#include "../uuid.hpp"
#include "../document.hpp"
#include "../pdf_document.hpp"
#include "../highlighting.hpp"

class Database {
protected:
    static char * read_document(Uuid const & uuid);
    static char * read_latest_windows_configuration();
    static std::string latest_opened_pdf;
};

#endif //DATABASE_H

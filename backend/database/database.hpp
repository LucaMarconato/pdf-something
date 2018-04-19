#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <map>

#include "../uuid.hpp"
#include "../document.hpp"
#include "../pdf_document.hpp"
#include "../highlighting.hpp"

class Database {
    // static json load_document(Uuid const & uuid);
    // static json latest_grid_layout();
protected:
    static std::string latest_opened_pdf;
};

#endif //DATABASE_H

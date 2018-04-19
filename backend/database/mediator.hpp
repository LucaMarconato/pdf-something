#ifndef MEDIATOR_H
#define MEDIATOR_H

#include <memory>

#include "database.hpp"
#include "resources_manager.hpp"
#include "../uuid.hpp"
#include "../io/file.hpp"

//this class is responsible to mediate from the database in order to return the results of predefined queries
class Mediator: Database, Resources_manager {
public:
    static std::shared_ptr<Document> document_for_uuid(Uuid const & uuid);
    static std::shared_ptr<Pdf_page> pdf_page_for_uuid(Uuid const & uuid, std::shared_ptr<Pdf_document> in_document);
    static std::shared_ptr<Highlighting> highlighting_for_uuid(Uuid const & uuid);
    static std::shared_ptr<Highlighting_component> highlighting_component_for_uuid(Uuid const & uuid);

    //this returns, it if exits
    static Uuid get_latest_opened_pdf();
};

#endif //MEDIATOR_H

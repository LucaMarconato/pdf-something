#ifndef MEDIATOR_H
#define MEDIATOR_H

#include "database.hpp"
#include "resources_manager.hpp"
#include "../uuid.hpp"
#include "../io/file.hpp"

//this class is responsible to mediate from the database in order to return the results of predefined queries
class Mediator: Database, Resources_manager {
public:
    static Document & document_for_uuid(Uuid const & uuid);
    static Pdf_page & pdf_page_for_uuid(Uuid const & uuid, Pdf_document & in_document, unsigned int index);
    static Highlighting & highlighting_for_uuid(Uuid const & uuid);
    static Highlighting_component & highlighting_component_for_uuid(Uuid const & uuid);

    //this returns, it if exits
    static Uuid get_latest_opened_pdf();
};

#endif //MEDIATOR_H

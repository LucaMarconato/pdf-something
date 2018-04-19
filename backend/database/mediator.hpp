#ifndef MEDIATOR_H
#define MEDIATOR_H

#include "database.hpp"
#include "resources_manager.hpp"
#include "../uuid.hpp"

//this class is responsible to mediate from the database in order to return the results of predefined queries
class Mediator: Database, Resources_manager {
public:
    static Document * document_for_uuid(Uuid const & uuid);
    static Pdf_page * pdf_page_for_uuid(Uuid const & uuid, Pdf_document * in_document);
    static Highlighting * highlighting_for_uuid(Uuid const & uuid, Document * in_document);
    static Highlighting_component * highlighting_component_for_uuid(Uuid const & uuid);

    static bool document_is_loaded(Uuid uuid);
    static bool pdf_page_is_loaded(Uuid uuid);
    static bool highlighting_is_loaded(Uuid uuid);
    static bool highlighting_component_is_loaded(Uuid uuid);

    //this returns, it if exits
    static Uuid get_latest_opened_pdf();
};

#endif //MEDIATOR_H

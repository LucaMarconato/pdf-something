#ifndef MEDIATOR_H
#define MEDIATOR_H

#include "database.hpp"
#include "resources_manager.hpp"
#include "../windows_configuration.hpp"
#include "../uuid.hpp"

// this class is responsible for mediating with the database (class Database) and with the collection of loaded resources (class Resources_manager) in order to return the results of predefined queries
class Mediator: Database, Resources_manager {
public:
    /*
      These methods check if the resource associated to the uuid is already in memory.
      If it is, they return it, if not, they load it in memory from the Database and then they return it.
    */
    static Document * document_for_uuid(Uuid const & uuid);
    static Pdf_page * pdf_page_for_uuid(Uuid const & uuid);
    static Highlighting * highlighting_for_uuid(Uuid const & uuid);
    static Highlighting_component * highlighting_component_for_uuid(Uuid const & uuid);

    static void load_latest_windows_configuration();

    static bool document_is_loaded(Uuid & uuid);
    static bool pdf_page_is_loaded(Uuid & uuid);
    static bool highlighting_is_loaded(Uuid & uuid);
    static bool highlighting_component_is_loaded(Uuid & uuid);

    static Uuid get_latest_opened_pdf();

    Mediator() = delete;
};

#endif // MEDIATOR_H

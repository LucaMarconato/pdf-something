#ifndef PDF_DOCUMENT_H
#define PDF_DOCUMENT_H

#include <string>
#include <list>
#include <boost/unordered_map.hpp>
#include <unordered_map>
#include <boost/bimap.hpp>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

#include "document.hpp"
#include "uuid.hpp"
// for the unordered_map hashes
#include "database/resources_manager.hpp"

class Pdf_page;

class Pdf_document : public Document {
public:
    /*
      This function receives as argument a parsed .json which describes the document, and initializes partially the document, i.e. without loading the pages and the highlightings.
      The loading of the pages is done by load_all_pages().
      In this way, it is easier for us to decide to load only some pages of a document, resuling in a faster execution
    */
    Pdf_document(json const & j);
    // method called by mediator.cpp
    void load_all_pages(json const & j);
    std::string serialize_to_json();
    bool is_valid() const;
    void print(std::ostream & stream) const;
private:
    std::unordered_map<Uuid, Pdf_page *> pages;
    /*
      Here I use a bimap to access the number of the page from the uuid and vice-versa.
      The ordering represent here is the one displayed to the user, the ordering in the original .pdf is never touched
    */
    boost::bimap<Uuid, int> numbering;
    
};
std::ostream & operator<<(std::ostream & stream, const Pdf_document & obj);

#endif // PDF_DOCUMENT_H

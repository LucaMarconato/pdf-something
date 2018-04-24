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
    //this function receives as argument the parsed .json corresponding to the information of a document
    Pdf_document(json const & j);
    void load_all_pages(json const & j);
    bool is_valid() const;
    void print(std::ostream & stream) const;
    ~Pdf_document();
private:
    std::unordered_map<Uuid, Pdf_page *> pages;
    boost::bimap<Uuid, int> numbering;
    
};
std::ostream & operator<<(std::ostream & stream, const Pdf_document & obj);

#endif //PDF_DOCUMENT_H

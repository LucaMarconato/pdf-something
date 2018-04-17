#ifndef PDF_DOCUMENT_H
#define PDF_DOCUMENT_H

#include <string>
#include <list>
#include <map>
#include <boost/bimap.hpp>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

#include "document.hpp"

class Pdf_document;

class Pdf_page {
public:
    Pdf_page(Pdf_document & in_document, unsigned int index);
    friend std::ostream & operator<<(std::ostream & stream, const Pdf_page & obj);    
private:
    void compute_size();
    Pdf_document & in_document;
    bool initialized = false;
    double width;  //real width, in inches
    double height; //real height, in inches
    unsigned int index;
};
std::ostream & operator<<(std::ostream & stream, const Pdf_page & obj);

class Pdf_document : public Document  {
public:
    //this function receives as argument the parsed .json corresponding to the information of a document
    Pdf_document(json const & j);
    void load_all_pages(json const & j);
    friend std::ostream & operator<<(std::ostream & stream, const Pdf_document & obj);
    ~Pdf_document();
private:
    std::map<Uuid, Pdf_page> pages;
    boost::bimap<Uuid, int> numbering;
};
std::ostream & operator<<(std::ostream & stream, const Pdf_document & obj);

#endif //PDF_DOCUMENT_H

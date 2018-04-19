#ifndef PDF_DOCUMENT_H
#define PDF_DOCUMENT_H

#include <string>
#include <list>
#include <map>
#include <memory>
#include <boost/bimap.hpp>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

#include "document.hpp"
#include "uuid.hpp"

class Pdf_document;

class Pdf_page {
public:
    Pdf_page();
    Pdf_page(std::shared_ptr<Pdf_document> in_document);
    Pdf_page(const Pdf_page & obj);
    friend void swap(Pdf_page & obj1, Pdf_page & obj2);
    Pdf_page & operator=(Pdf_page & obj);
    bool is_valid() const;
    friend std::ostream & operator<<(std::ostream & stream, const Pdf_page & obj);
    
    std::shared_ptr<Pdf_document> in_document;
    Uuid uuid;
    unsigned int index = -1;
private:
    void compute_size();
    void print(std::ostream & stream);

    double width = -1;  //real width, in inches
    double height = -1; //real height, in inches
};
std::ostream & operator<<(std::ostream & stream, const Pdf_page & obj);

class Pdf_document : public Document {
public:
    //this function receives as argument the parsed .json corresponding to the information of a document
    Pdf_document(json const & j);
    void load_all_pages(json const & j);
    bool is_valid() const;
    void print(std::ostream & stream) const;
    ~Pdf_document();
private:
    std::map<Uuid, std::shared_ptr<Pdf_page>> pages;
    boost::bimap<Uuid, int> numbering;
};
std::ostream & operator<<(std::ostream & stream, const Pdf_document & obj);

#endif //PDF_DOCUMENT_H

#ifndef PDF_DOCUMENT_H
#define PDF_DOCUMENT_H

#include <string>
#include <list>

#include "document.hpp"

class Pdf_document;

class Pdf_page {
public:
    Pdf_page(Pdf_document & in_document);
    friend std::ostream & operator<<(std::ostream & stream, const Pdf_page & obj);
private:
    void compute_size();
    Pdf_document & in_document;
    bool initialized = false;
    double width;  //real width, in inches
    double height; //real height, in inches
};
std::ostream & operator<<(std::ostream & stream, const Pdf_page & obj);

class Pdf_document : Document  {
public:
    friend std::ostream & operator<<(std::ostream & stream, const Pdf_document & obj);
private:
    std::list<Pdf_page> pages;
};
std::ostream & operator<<(std::ostream & stream, const Pdf_document & obj);


#endif //PDF_DOCUMENT_H

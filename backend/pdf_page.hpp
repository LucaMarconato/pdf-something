#ifndef PDF_PAGE_H
#define PDF_PAGE_H

#include <string>
#include <list>
#include <map>
#include <boost/bimap.hpp>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "document.hpp"
#include "uuid.hpp"
#include "constants.hpp"

class Pdf_document;
class Highlighting_component;

class Pdf_page {
public:
    Pdf_page();
    Pdf_page(Pdf_document * in_document);
    Pdf_page(const Pdf_page & obj);
    friend void swap(Pdf_page & obj1, Pdf_page & obj2);
    Pdf_page & operator=(Pdf_page & obj);
    bool is_valid() const;
    friend std::ostream & operator<<(std::ostream & stream, const Pdf_page & obj);
    
    Pdf_document * in_document = nullptr;
    Uuid uuid;
    unsigned int index = -1;
    unsigned int index_in_pdf = -1;
    std::list<Highlighting_component *> highlighting_components;
    double x0_crop = PAGE_MAX_X + 1;
    double y0_crop = PAGE_MAX_Y + 1;
    double x1_crop = PAGE_MAX_X + 1;
    double y1_crop = PAGE_MAX_Y + 1;
private:
    void compute_size();
    void print(std::ostream & stream);

    double width = -1;  //real width, in pixels
    double height = -1; //real height, in pixels
};
std::ostream & operator<<(std::ostream & stream, const Pdf_page & obj);

#endif //PDF_PAGE_H

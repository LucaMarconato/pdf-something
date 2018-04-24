#ifndef HIGHLIGHTING_H
#define HIGHLIGHTING_H

#include <string>
#include <list>

#include "uuid.hpp"
#include "color.hpp"
#include "constants.hpp"

class Document;
class Pdf_page;

//for the moment I am only implementing rectangular highlightings

class Highlighting_component;

class Highlighting
{
public:
    Highlighting();
    bool is_valid() const;
    friend std::ostream & operator<<(std::ostream & stream, const Highlighting & obj);

    Uuid uuid;
    Document * in_document = nullptr;
    //this is the text that the user can assign to an highlighting
    std::string text = "";
    Color color;
    std::list<Highlighting_component *> highlighting_components;
};
std::ostream & operator<<(std::ostream & stream, const Highlighting & obj);

class Highlighting_component
{
public:
    friend std::ostream & operator<<(std::ostream & stream, const Highlighting_component & obj);
    bool is_valid() const;

    Uuid uuid;
    Highlighting * parent_highlighting = nullptr;
    Pdf_page * in_page = nullptr;

    /*
      The following values respect x0 < x1, y0 < y1, and the axes are like in the Cartesian plane.
      These values are usually in [0,1], where 0 and 1 refer to the border of the page of a document.
      If the user crops the page, then the value of a newly inserted highlighting will belong to a subrange of [0,1].
      The user, with a crop, can also enlarge a page beyond its original size. Values outside the range [0,1] describe highlighting inserted in such positions.
    */
    double x0 = PAGE_MAX_X + 1;
    double y0 = PAGE_MAX_Y + 1;
    double x1 = PAGE_MAX_X + 1;
    double y1 = PAGE_MAX_Y + 1;
    
};
std::ostream & operator<<(std::ostream & stream, const Highlighting_component & obj);

#endif //HIGHLIGHTING_H

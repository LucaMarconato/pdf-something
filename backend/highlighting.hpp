#ifndef HIGHLIGHTING_H
#define HIGHLIGHTING_H

#include <string>
#include <list>

#include "uuid.hpp"
#include "document.hpp"
#include "pdf_document.hpp"
#include "color.hpp"

//for the moment I am only implementing rectangular highlightings

class Highlighting_component;

class Highlighting
{
public:
    Highlighting(Document & parent);
    friend std::ostream & operator<<(std::ostream & stream, const Highlighting & obj);
private:
    bool initialized = false;
    Uuid uuid;
    //this is the text that the user can assign to an highlighting
    std::string text = "";
    Color color;
    Document & parent_document;
    std::list<Highlighting_component> components;    
};
std::ostream & operator<<(std::ostream & stream, const Highlighting & obj);

class Highlighting_component
{
public:
    Highlighting_component(Highlighting & parent, Pdf_page & in_page, double x0, double y0, double x1, double y1);
    friend std::ostream & operator<<(std::ostream & stream, const Highlighting_component & obj);
private:
    bool initialized = false;
    Uuid uuid;
    Highlighting & parent_highlighting;
    Pdf_page & in_page;
    /*
      The following values respect x0 < x1, y0 < y1, and the axes are like in the Cartesian plane.
      These values are usually in [0,1], where 0 and 1 refer to the border of the page of a document.
      If the user crops the page, then the value of a newly inserted highlighting will belong to a subrange of [0,1].
      The user, with a crop, can also enlarge a page beyond its original size. Values outside the range [0,1] describe highlighting inserted in such positions.
    */
    double x0, y0, x1, y1;
    //these constants are used to be sure that the above values cannot be excessively large
    const double BORDER = 2.0;
    const double MIN_X = 0.0 - BORDER;
    const double MIN_Y = 0.0 - BORDER;
    const double MAX_X = 1.0 + BORDER;
    const double MAX_Y = 1.0 + BORDER;
    
};
std::ostream & operator<<(std::ostream & stream, const Highlighting_component & obj);

#endif //HIGHLIGHTING_H

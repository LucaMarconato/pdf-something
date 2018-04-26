#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

#include "datetime.hpp"
#include "uuid.hpp"
#include "grid_layout.hpp"

/*
  Document is a polymorphic base class that defines common methods and attributes for various types of documents.
  This will allow us to support differnt formats, first of all pdfs, but even presentation formats or images.
  The polymorphism is not fully implemented. Some methods of Pdf_document should be inside Document and we should introduce the class Page, a polymorphic base class for Pdf_page. 
  Anyway let us postpone this to more mature times, when we will support also formats different from .pdf
*/
class Document {
public:
    /*
      Method called by mediator.cpp, we may decide to make this method private and make Mediator a friend class
      This is a pure virtual function since it makes no sense to load the pages of a Document, but only a specific format of document, like a Pdf_document
    */
    virtual void load_all_pages(json const & j) = 0;
    /*
      Method that we can momentarily use to save a document inside a .json file. This is ultra-inefficient since we have to rewrite all the file at every save operation   
    */    
    virtual std::string serialize_to_json() = 0;
    /*
      The polymorphism with operator<< and Document::print works in this way (I will use Pdf_document as an example, but the things I will explain would work with a generic subclass):
      -if << is called on a Document, then it calls Document::print()
      --If the document object is a real document object, then only Document::print is called. Note that this will not happen to us (unless with weird casting), because we cannot write "Document document;" or "Document * document = new Document();" since Document is an abstract class (a class with pure virtual functions, so that pure Document objects do not make sense to exist)
      --If the document object was created as "Document * document = new Pdf_document();", then Pdf_document::print() is called instead of Document::print(). The function Pdf_document::print() will then manually call Document::print()
      -if << is called on a Pdf_document, then it calls Pdf_documnet::print(), as above, Pdf_document::print() then manually calls Document::print()      
    */
    friend std::ostream & operator<<(std::ostream & stream, const Document & obj);
    virtual ~Document();
protected:    
    // a child class (say Pdf_document) of Document should check if it is valid but also if this base class is valid
    bool is_valid_base() const;
    virtual bool is_valid() const;
    // described above, when talking about operator<<
    virtual void print(std::ostream & stream) const;
    
    Uuid uuid;
    // this path is used to create a directory tree inside the program, for organizing the various documents
    std::string in_program_directory;
    std::string name;
    Datetime latest_opening;
    // page at which the .pdf was open, pay attention with this value if the user swaps some pages
    unsigned int index = -1;
    // the grid which displays a document, the grid shows contiguos pages and (e.g.) if the user presses the right arrow all the pages in the grid will change
    Grid_layout grid_layout;
};
std::ostream & operator<<(std::ostream & stream, const Document & obj);

#endif //DOCUMENT_H

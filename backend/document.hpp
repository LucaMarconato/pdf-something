#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>

#include "datetime.hpp"
#include "uuid.hpp"

/*
  Document is a super class that defines common methods and attributes for various types of documents.
  This will allow us to support differnt formats, first of all pdfs, but even presentation formats or images
*/
class Document
{
public:    
    friend std::ostream & operator<<(std::ostream & stream, const Document & obj);
private:
    //this path is used to create a directory tree inside the program, for organizing the various documents
    std::string in_program_path;
    Datetime latest_opening;
    Uuid uuid;
protected:
    bool initialized = false;
};

std::ostream & operator<<(std::ostream & stream, const Document & obj);

#endif //DOCUMENT_H

#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
#include <memory>

#include <nlohmann/json.hpp>

using json = nlohmann::json;


#include "datetime.hpp"
#include "uuid.hpp"

/*
  Document is a super class that defines common methods and attributes for various types of documents.
  This will allow us to support differnt formats, first of all pdfs, but even presentation formats or images
*/
class Document {
public:
    static std::shared_ptr<Document> parse_document(char * file_content);
    virtual std::string serialize_to_json();    
    friend std::ostream & operator<<(std::ostream & stream, const Document & obj);
    //polymorphic method called by the operator<<
    virtual ~Document();
protected:
    bool is_valid_base() const;
    virtual bool is_valid() const;
    virtual void print(std::ostream & stream) const;
    virtual void load_all_pages(json const & j);
    
    Uuid uuid;
    //this path is used to create a directory tree inside the program, for organizing the various documents
    std::string in_program_directory;
    std::string name;
    Datetime latest_opening;
};

std::ostream & operator<<(std::ostream & stream, const Document & obj);

#endif //DOCUMENT_H

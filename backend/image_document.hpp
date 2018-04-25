#ifndef IMAGE_DOCUMENT_H
#define IMAGE_DOCUMENT_H

/*
  This file is unused and it will be unused for a long time, it is just a sketch for showing the polymorphism of Document.
*/

#include <iostream>

#include "document.hpp"

class Image_document : public Document {
    public:
    void load_all_pages(json const & j);
};

class Png_document : public Image_document {
public:
    bool is_valid() const {
        return false;
    }
    void print(std::ostream &stream) const
    {
        stream << "this class is only sketched\n";
        // exit(1);
    }
};

#endif //IMAGE_DOCUMENT_H

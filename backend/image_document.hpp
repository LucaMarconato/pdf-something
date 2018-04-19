#ifndef IMAGE_DOCUMENT_H
#define IMAGE_DOCUMENT_H

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
        std::cout << "this class is only sketched\n";
        exit(1);
    }
};

#endif //IMAGE_DOCUMENT_H

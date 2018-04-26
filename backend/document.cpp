#include "document.hpp"

#include <iostream>

#include "pdf_document.hpp"

bool Document::is_valid() const
{    
    return this->is_valid_base();
}

bool Document::is_valid_base() const
{
    bool is_valid = true;
    is_valid = is_valid && this->uuid.is_valid();
    is_valid = is_valid && this->latest_opening.is_valid();
    is_valid = is_valid && this->in_program_directory != "";
    is_valid = is_valid && this->name != "";
    is_valid = is_valid && VALID_PAGE_INDEX(this->index);
    is_valid = is_valid && this->grid_layout.is_valid();
    
    if(!is_valid) {
        std::cerr << "error: Document, is_valid = 0\n";
        MY_ASSERT(false); exit(1);
    }
    return is_valid;
}

std::ostream & operator<<(std::ostream & stream, const Document & obj)
{    
    obj.print(stream);
    return stream;
}

void Document::print(std::ostream & stream) const
{
if (this->is_valid())
    {
        stream << "this->uuid = " << this->uuid << "<BR>";
        stream << "this->in_program_directory = " << this->in_program_directory << "<BR>";
        stream << "this->name = " << this->name << "<BR>";
        stream << "this->latest_opening = " << this->latest_opening << "<BR>";
        stream << "this->index = " << this->index;
        stream << "<blockquote>";
        stream << "this->grid_layout = " << this->grid_layout;
        stream << "</blockquote>";
    } else {
        stream << "[uninitialized document]";
    }

}

Document::~Document()
{
    
}

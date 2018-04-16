#include "document.hpp"

#include <iostream>

std::ostream & operator<<(std::ostream & stream, const Document & obj)
{
    if(obj.initialized) {
        stream << "obj.in_program_path = " << obj.in_program_path << "\n";
        stream << "obj.latest_opening.string_representation = " << obj.latest_opening.string_representation << "\n";
    } else {
        stream << "<uninitialized document>";
    }
    return stream;
}

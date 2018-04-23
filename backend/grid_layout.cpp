#include "grid_layout.hpp"

#include "constants.hpp"

Grid_layout::Grid_layout()
{
    
}

Grid_layout::Grid_layout(unsigned int number_of_rows, unsigned int number_of_columns)
{
    this->number_of_rows = number_of_rows;
    this->number_of_columns = number_of_columns;
}

Grid_layout::Grid_layout(const Grid_layout & obj)
{
    this->number_of_columns = obj.number_of_columns;
    this->number_of_rows = obj.number_of_rows;
}

bool Grid_layout::is_valid() const
{
    bool is_valid = true;
    is_valid = is_valid && VALID_GRID_LAYOUT(this->number_of_rows,this->number_of_columns); MY_ASSERT(is_valid);
        
    if(!is_valid) {
        std::cerr << "error: Grid_layout, is_valid = 0\n";
    }
    return is_valid;
}

unsigned int Grid_layout::first_page_in_view_for_index(unsigned int index)
{
    return (index-index%(this->number_of_rows*this->number_of_columns));
}

std::tuple <unsigned int, unsigned int> Grid_layout::size()
{
    return std::make_tuple(this->number_of_rows,this->number_of_columns);
}

std::ostream & operator<<(std::ostream & stream, const Grid_layout & obj)
{
    if(obj.is_valid()) {
        stream << "obj.number_of_rows = " << obj.number_of_rows << "\n";
        stream << "obj.number_of_columns = " << obj.number_of_columns << "\n";
    } else {
        stream << "[uninitialized grid_layout]";
    }

    return stream;
}


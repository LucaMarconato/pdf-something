#include "grid_layout.hpp"

#include "constants.hpp"

Grid_layout::Grid_layout() {}

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

void swap(Grid_layout & obj1, Grid_layout & obj2)
{
    std::swap(obj1.number_of_rows,obj2.number_of_rows);
    std::swap(obj1.number_of_columns,obj2.number_of_columns);
}

Grid_layout & Grid_layout::operator=(Grid_layout obj)
{
    swap(*this,obj);
    return *this;
}

bool Grid_layout::is_valid() const
{
    bool is_valid = true;
    is_valid = is_valid && VALID_GRID_LAYOUT(this->number_of_rows,this->number_of_columns);
        
    if(!is_valid) {
        std::cerr << "error: Grid_layout, is_valid = 0\n";
        MY_ASSERT(is_valid);
        exit(1);
    }
    return is_valid;
}

unsigned int Grid_layout::first_page_in_view_for_index(unsigned int index)
{
    if(!this->is_valid()) {
        std::cerr << "error: first_page_in_view_for_index, this->is_valid() = 0\n";
        MY_ASSERT(false);
        exit(1);
    }
    return (index-index%(this->number_of_rows*this->number_of_columns));
}

std::tuple <unsigned int, unsigned int> Grid_layout::size()
{
    return std::make_tuple(this->number_of_rows,this->number_of_columns);
}

std::ostream & operator<<(std::ostream & stream, const Grid_layout & obj)
{
    if(obj.is_valid()) {
        stream << "obj.number_of_rows = " << obj.number_of_rows << "<BR>";
        stream << "obj.number_of_columns = " << obj.number_of_columns;
    } else {
        stream << "[uninitialized grid_layout]";
    }

    return stream;
}


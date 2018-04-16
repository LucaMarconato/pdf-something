#include "window_layout.hpp"

#include <iostream>

//window layout element

Window_layout_element::Window_layout_element()
{
    
}

Window_layout_element::Window_layout_element(Document * document)
{
    this->document = document;
}

Window_layout_element::Window_layout_element(const Window_layout_element & element)
{
    this->document = element.document;
}

Window_layout_element & Window_layout_element::operator=(Window_layout_element & obj)
{
    std::swap(this->document, obj.document);
    return *this;
}

std::ostream & operator<<(std::ostream & stream, const Window_layout_element & obj)
{
    stream << "obj.document:\n";
    stream << obj.document << "\n";
    return stream;
}

//window layout

void Window_layout::set_layout(unsigned int number_of_rows, unsigned int number_of_columns)
{
    if(number_of_rows > this->max_rows()) {
        std::cerr << "error: number_of_rows = " << number_of_rows << ", this->max_rows() = " << this->max_rows() << "\n";
        return;
    }
    if(number_of_columns > this->max_columns()) {
        std::cerr << "error: number_of_columns = " << number_of_columns << ", this->max_columns() = " << this->max_columns() << "\n";
        return;        
    }
    this->number_of_rows = number_of_rows;
    this->number_of_columns = number_of_columns;
    this->window_layout_elements.clear();
    //fun fact: in Swift, the following line of code would assign the same new object to each element of the vector
    this->window_layout_elements.resize(this->number_of_rows,std::vector<Window_layout_element>(this->number_of_columns));
    integrity_check_passed();
}

void Window_layout::set_layout_element(Window_layout_element & element, unsigned int row, unsigned int column)
{
    if(!this->integrity_check_passed()) {
        return;
    }
    if(row >= this->number_of_rows) {
        std::cerr << "error: row = " << row << ", this->number_of_rows = " << this->number_of_rows << "\n";
        return;
    }
    if(column >= this->number_of_columns) {
        std::cerr << "error: column = " << column << ", this->number_of_columns = " << this->number_of_columns << "\n";
        return;
    }
    this->window_layout_elements[row][column] = element;
}

std::tuple<unsigned int, unsigned int> Window_layout::size()
{
    return std::make_tuple(this->number_of_rows, this->number_of_columns);
}

/*
  This function checks that number_of_rows <= max_rows() and the same for columns.
  It also checks if the size of the 2D vector window_layout_elements is conform to the number described in the previous lines.
*/
bool Window_layout::integrity_check_passed() const
{    
    bool is_all_right = true;
    if(this->number_of_rows > this->max_rows()) {
        std::cerr << "error: this->number_of_rows = " << this->number_of_rows << ", this->max_rows() = " << this->max_rows() << "\n";
        is_all_right = false;
    }
    
    if(this->number_of_columns > this->max_columns()) {
        std::cerr << "error: this->number_of_columns = " << this->number_of_columns << ", this->max_columns() = " << this->max_columns() << "\n";
        is_all_right = false;
    }

    if(this->window_layout_elements.size() > this->number_of_rows) {
        std::cerr << "error: this->window_layout_elements.size() = " << this->window_layout_elements.size() << ", this->number_of_rows = " << this->number_of_rows << "\n";
        is_all_right = false;
    } else {
        bool each_column_has_the_same_length = true;
        unsigned int common_length;
        for(unsigned int i = 0; i < this->window_layout_elements.size(); i++) {
            if(i == 0) {
                common_length = this->window_layout_elements[0].size();
            } else {
                if(common_length != this->window_layout_elements[i].size()) {
                    each_column_has_the_same_length = false;
                    std::cerr << "error: common_length = " << common_length << ", this->window_layout_elements[" << i << "].size() = " << this->window_layout_elements[i].size() << "\n";
                }
            }
            if(this->window_layout_elements[i].size() > this->number_of_columns) {
                std::cerr << "error: this->window_layout_elements[i].size() = " << this->window_layout_elements[i].size() << ", this->number_of_columns = " << this->number_of_columns << "\n";
                is_all_right = false;
            }
        }
        is_all_right = is_all_right && each_column_has_the_same_length;
    }

    return is_all_right;
}

std::ostream & operator<<(std::ostream & stream, const Window_layout & obj)
{
    stream << "obj.number_of_rows = " << obj.number_of_rows << ", obj.number_of_columns = " << obj.number_of_columns << "\n";
    stream << "obj.max_rows() = " << obj.max_rows() << ", obj.max_columns() = " << obj.max_columns() << "\n";
    if(obj.integrity_check_passed()) {
        for(unsigned int i = 0; i < obj.number_of_rows; i++) {
            for(unsigned int j = 0; j < obj.number_of_columns; j++) {
                stream << "obj.window_layout_element (" << i << ", " << j << "):\n";
                stream << obj.window_layout_elements[i][j];
            }
        }   
    }
    return stream;
}

#include "window_layout.hpp"

#include <iostream>

#include "constants.hpp"

//window layout element

Window_layout_element::Window_layout_element()
{
    
}

Window_layout_element::Window_layout_element(Document * document, unsigned int index)
{
    this->document = document;
    this->index = index;
}

Window_layout_element::Window_layout_element(const Window_layout_element & element)
{
    this->document = element.document;
}

Window_layout_element & Window_layout_element::operator=(Window_layout_element & obj)
{
    Window_layout_element to_swap = Window_layout_element(obj);
    swap(*this,to_swap);
    return *this;
}

void swap(Window_layout_element & obj1, Window_layout_element & obj2)
{
    std::swap(obj1.document,obj2.document);
}

bool Window_layout_element::is_valid() const
{
    bool is_valid = true;
    is_valid = is_valid && this->document != nullptr;
    is_valid = is_valid && VALID_PAGE_INDEX(this->index);

    if(!is_valid) {
        std::cerr << "error: Window_layout_element, is_valid = " << is_valid << "\n";
    }
    return is_valid;
}

std::ostream & operator<<(std::ostream & stream, const Window_layout_element & obj)
{
    stream << "obj.document:<BR>";
    stream << obj.document;
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
    is_valid();
}

void Window_layout::set_layout_element(Window_layout_element & element, unsigned int row, unsigned int column)
{
    if(!this->is_valid()) {
        std::cerr << "error: set_layout_element, is_valid() = 0\n";
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
bool Window_layout::is_valid() const
{    
    bool is_valid = true;
    is_valid = is_valid && (0 < this->number_of_rows) && (this->number_of_rows <= this->max_rows());
    is_valid = is_valid && (0 < this->number_of_columns) && (this->number_of_columns <= this->max_columns());

    if(this->window_layout_elements.size() > this->number_of_rows) {
        is_valid = false;
    } else {
        bool each_column_has_the_same_length = true;
        unsigned int common_length;
        for(unsigned int i = 0; i < this->window_layout_elements.size(); i++) {
            if(i == 0) {
                common_length = this->window_layout_elements[0].size();
            } else {
                if(common_length != this->window_layout_elements[i].size()) {
                    each_column_has_the_same_length = false;
                }
            }
            if(this->window_layout_elements[i].size() > this->number_of_columns) {
                is_valid = false;
            }
        }
        is_valid = is_valid && each_column_has_the_same_length;
    }
    if(!is_valid) {
        std::cerr << "error: Window_layout, is_valid = " << is_valid << "\n";
    }
    
    return is_valid;
}

std::ostream & operator<<(std::ostream & stream, const Window_layout & obj)
{
    if(obj.is_valid()) {
        stream << "obj.number_of_rows = " << obj.number_of_rows << ", obj.number_of_columns = " << obj.number_of_columns << "<BR>";
        stream << "obj.max_rows() = " << obj.max_rows() << ", obj.max_columns() = " << obj.max_columns() << "<BR>";
        for(unsigned int i = 0; i < obj.number_of_rows; i++) {
            for(unsigned int j = 0; j < obj.number_of_columns; j++) {
                stream << "<blockquote>";
                stream << "obj.window_layout_element (" << i << ", " << j << "):<BR>";
                stream << obj.window_layout_elements[i][j];
                stream << "</blockquote>"; 
            }
        }   
    } else {
        stream << "<unitialized window_layout>";
    }
    return stream;
}

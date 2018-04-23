#include "window_split_screen.hpp"

#include <iostream>
#include <cassert>

#include "constants.hpp"

//window split screen element

Window_split_screen_element::Window_split_screen_element()
{
    
}

Window_split_screen_element::Window_split_screen_element(Document * document, unsigned int index, Grid_layout grid_layout)
{
    this->document = document;
    this->index = index;
    this->grid_layout = grid_layout;
}

Window_split_screen_element::Window_split_screen_element(const Window_split_screen_element & obj)
{
    this->document = obj.document;
    this->index = obj.index;
    this->grid_layout = obj.grid_layout;
}

Window_split_screen_element & Window_split_screen_element::operator=(Window_split_screen_element & obj)
{
    Window_split_screen_element to_swap = Window_split_screen_element(obj);
    swap(*this,to_swap);
    return *this;
}

void swap(Window_split_screen_element & obj1, Window_split_screen_element & obj2)
{
    std::swap(obj1.document,obj2.document);
    std::swap(obj1.index,obj2.index);
    std::swap(obj1.grid_layout,obj2.grid_layout);
}

bool Window_split_screen_element::is_valid() const
{
    bool is_valid = true;
    is_valid = is_valid && this->document != nullptr; MY_ASSERT(is_valid);
                                                          is_valid = is_valid && VALID_PAGE_INDEX(this->index); MY_ASSERT(is_valid);

    if(!is_valid) {
        std::cerr << "error: Window_split_screen_element, is_valid = " << is_valid << "\n";
    }
    return is_valid;
}

std::ostream & operator<<(std::ostream & stream, const Window_split_screen_element & obj)
{
    if(obj.is_valid()) {
        stream << "*obj.document:<BR>";
        stream << *obj.document;
        stream << "obj.index = " << obj.index;
        stream << "<blockquote>";
        stream << "obj.grid_layout = " << obj.grid_layout << "\n";
        stream << "</blockquote>";
    } else {
        stream << "[uninitialized_split_screen_element]";
    }
    return stream;
}

//window split screen

void Window_split_screen::set_split_screen_layout(unsigned int number_of_rows, unsigned int number_of_columns)
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
    this->window_split_screen_elements.clear();
    //fun fact: in Swift, the following line of code would assign the same new object to each element of the vector
    this->window_split_screen_elements.resize(this->number_of_rows,std::vector<Window_split_screen_element>(this->number_of_columns));
    is_valid();
}

void Window_split_screen::set_split_screen_element(Window_split_screen_element & element, unsigned int row, unsigned int column)
{
    if(!this->is_valid()) {
        std::cerr << "error: set_split_screen_element, is_valid() = 0\n";
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
    this->window_split_screen_elements[row][column] = element;
}

std::tuple<unsigned int, unsigned int> Window_split_screen::size()
{
    return std::make_tuple(this->number_of_rows, this->number_of_columns);
}

/*
  This function checks that number_of_rows <= max_rows() and the same for columns.
  It also checks if the size of the 2D vector window_split_screen_elements is conform to the number described in the previous lines.
*/
bool Window_split_screen::is_valid() const
{    
    bool is_valid = true;
    is_valid = is_valid && (0 < this->number_of_rows) && (this->number_of_rows <= this->max_rows()); MY_ASSERT(is_valid);
                                                                                                         is_valid = is_valid && (0 < this->number_of_columns) && (this->number_of_columns <= this->max_columns()); MY_ASSERT(is_valid);

    if(this->window_split_screen_elements.size() > this->number_of_rows) {
        is_valid = false; MY_ASSERT(is_valid);
    } else {
        bool each_column_has_the_same_length = true;
        unsigned int common_length;
        for(unsigned int i = 0; i < this->window_split_screen_elements.size(); i++) {
            if(i == 0) {
                common_length = this->window_split_screen_elements[0].size();
            } else {
                if(common_length != this->window_split_screen_elements[i].size()) {
                    each_column_has_the_same_length = false;
                    MY_ASSERT(is_valid);
                }
            }
            if(this->window_split_screen_elements[i].size() > this->number_of_columns) {
                is_valid = false;
                MY_ASSERT(is_valid);
            }
        }
        is_valid = is_valid && each_column_has_the_same_length;
        MY_ASSERT(is_valid);
    }
    if(!is_valid) {
        std::cerr << "error: Window_split_screen, is_valid = " << is_valid << "\n";
    }
    
    return is_valid;
}

std::ostream & operator<<(std::ostream & stream, const Window_split_screen & obj)
{
    if(obj.is_valid()) {
        stream << "obj.number_of_rows = " << obj.number_of_rows << ", obj.number_of_columns = " << obj.number_of_columns << "<BR>";
        stream << "obj.max_rows() = " << obj.max_rows() << ", obj.max_columns() = " << obj.max_columns() << "<BR>";
        for(unsigned int i = 0; i < obj.number_of_rows; i++) {
            for(unsigned int j = 0; j < obj.number_of_columns; j++) {
                stream << "-obj.window_split_screen_element (" << i << ", " << j << "):<BR>";
                stream << "<blockquote>";
                stream << obj.window_split_screen_elements[i][j];
                stream << "</blockquote>"; 
            }
        }   
    } else {
        stream << "<unitialized window_split_screen>";
    }
    return stream;
}

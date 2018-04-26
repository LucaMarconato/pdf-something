#include "window_split_screen.hpp"

#include <iostream>

#include "constants.hpp"

//--------window split screen element--------

Window_split_screen_element::Window_split_screen_element() {}

Window_split_screen_element::Window_split_screen_element(Document * document)
{
    this->document = document;
}

Window_split_screen_element::Window_split_screen_element(const Window_split_screen_element & obj)
{
    this->document = obj.document;
}

Window_split_screen_element & Window_split_screen_element::operator=(Window_split_screen_element obj)
{
    swap(*this,obj);
    return *this;
}

void swap(Window_split_screen_element & obj1, Window_split_screen_element & obj2)
{
    std::swap(obj1.document,obj2.document);
}

bool Window_split_screen_element::is_valid() const
{
    bool is_valid = true;
    is_valid = is_valid && this->document != nullptr;

    if(!is_valid) {
        std::cerr << "error: Window_split_screen_element, is_valid = " << is_valid << "\n";
    }
    return is_valid;
}

std::ostream & operator<<(std::ostream & stream, const Window_split_screen_element & obj)
{
    if(obj.is_valid()) {
        stream << "*obj.document:<blockquote>";
        stream << *obj.document;
        stream << "</blockquote>";
    } else {
        stream << "[uninitialized_split_screen_element]";
    }
    return stream;
}

//--------window split screen--------

Window_split_screen::Window_split_screen() {}

Window_split_screen::Window_split_screen(const Window_split_screen & obj)
{
    this->window_split_screen_elements = obj.window_split_screen_elements;
    this->number_of_rows = obj.number_of_rows;
    this->number_of_columns = obj.number_of_columns;
}

void swap(Window_split_screen & obj1, Window_split_screen & obj2)
{
    std::swap(obj1.window_split_screen_elements,obj2.window_split_screen_elements);
    std::swap(obj1.number_of_rows,obj2.number_of_rows);
    std::swap(obj1.number_of_columns,obj2.number_of_columns);
}

Window_split_screen & Window_split_screen::operator=(Window_split_screen obj)
{
    swap(*this,obj);
    return *this;
}

void Window_split_screen::set_split_screen_layout(unsigned int number_of_rows, unsigned int number_of_columns)
{
    if(number_of_rows > this->max_rows()) {
        std::cerr << "error: number_of_rows = " << number_of_rows << ", this->max_rows() = " << this->max_rows() << "\n";
        MY_ASSERT(false); exit(1);
    }
    if(number_of_columns > this->max_columns()) {
        std::cerr << "error: number_of_columns = " << number_of_columns << ", this->max_columns() = " << this->max_columns() << "\n";
        MY_ASSERT(false); exit(1);
    }
    this->number_of_rows = number_of_rows;
    this->number_of_columns = number_of_columns;
    this->window_split_screen_elements.clear();
    /*
      In Swift, the following line of code would assign the same new object to each element of the vector
      In C++, an instance of Window_split_screen_element is instanciated for each elemnt of the vector
    */
    this->window_split_screen_elements.resize(this->number_of_rows,std::vector<Window_split_screen_element>(this->number_of_columns));
}

void Window_split_screen::set_split_screen_element(Window_split_screen_element & element, unsigned int row, unsigned int column)
{
    if(!this->is_valid()) {
        std::cerr << "error: set_split_screen_element, is_valid() = 0\n";
        MY_ASSERT(false); exit(1);
    }
    if(row >= this->number_of_rows) {
        std::cerr << "error: row = " << row << ", this->number_of_rows = " << this->number_of_rows << "\n";
        MY_ASSERT(false); exit(1);
    }
    if(column >= this->number_of_columns) {
        std::cerr << "error: column = " << column << ", this->number_of_columns = " << this->number_of_columns << "\n";
        MY_ASSERT(false); exit(1);
    }
    this->window_split_screen_elements[row][column] = element;
}

std::tuple<unsigned int, unsigned int> Window_split_screen::size()
{
    return std::make_tuple(this->number_of_rows, this->number_of_columns);
}

/*
  This function checks that number_of_rows <= max_rows() and the same for columns.
  It also checks if the size of the 2D vector window_split_screen_elements is conforming to the numbers described in the previous lines.
*/
bool Window_split_screen::is_valid() const
{    
    bool is_valid = true;
    is_valid = is_valid && (0 < this->number_of_rows) && (this->number_of_rows <= this->max_rows());
    is_valid = is_valid && (0 < this->number_of_columns) && (this->number_of_columns <= this->max_columns());
    is_valid = is_valid && this->window_split_screen_elements.size() == this->number_of_rows;
    for(auto && e : this->window_split_screen_elements) {
        is_valid = is_valid && (e.size() == this->number_of_columns);
    }

    if(!is_valid) {
        std::cerr << "error: Window_split_screen, is_valid = " << is_valid << "\n";
        MY_ASSERT(false); exit(1);
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
                stream << "-obj.window_split_screen_elements[" << i << "][" << j << "]:<BR>";
                stream << "<blockquote>";
                stream << obj.window_split_screen_elements[i][j];
                stream << "</blockquote>"; 
            }
        }   
    } else {
        stream << "[unitialized window_split_screen]";
    }
    return stream;
}

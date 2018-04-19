#ifndef WINDOW_LAYOUT_H
#define WINDOW_LAYOUT_H

#include <string>
#include <vector>
#include <tuple>
#include <memory>

#include "document.hpp"

/*
  Each window is splitted in a grid, each portion of the grid is called a layout element.
  Different layout elements can display different documents
*/
class Window_layout_element
{
public:
    Window_layout_element();
    Window_layout_element(const Window_layout_element & element);
    Window_layout_element(std::shared_ptr<Document> document);
    friend void swap(Window_layout_element & obj1, Window_layout_element & obj2);
    Window_layout_element & operator=(Window_layout_element & obj);
    friend std::ostream & operator<<(std::ostream & stream, const Window_layout_element & obj);    
private:
    std::shared_ptr<Document> document;
};
std::ostream & operator<<(std::ostream & stream, const Window_layout_element & obj);

class Window_layout
{
public:
    void set_layout(unsigned int number_of_rows, unsigned int number_of_columns);
    void set_layout_element(Window_layout_element & element, unsigned int row, unsigned int column);
    std::tuple<unsigned int, unsigned int> size();
    friend std::ostream & operator<<(std::ostream & stream, const Window_layout & obj);
private:
    //perform some integrity check between the relation of some attribute of the class, returns true iff all is ok
    bool integrity_check_passed() const;
    //in an iPhone max_rows = max_columns = 1
    std::vector<std::vector<Window_layout_element>> window_layout_elements;
    unsigned int number_of_rows = 0;
    unsigned int number_of_columns = 0;
    unsigned int max_rows() const;
    unsigned int max_columns() const;
};
std::ostream & operator<<(std::ostream & stream, const Window_layout & obj);

#endif //WINDOW_LAYOUT_H

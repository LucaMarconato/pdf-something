#ifndef WINDOW_SPLIT_SCREEN_H
#define WINDOW_SPLIT_SCREEN_H

#include <string>
#include <vector>
#include <tuple>

#include "document.hpp"
#include "grid_layout.hpp"

/*
  Each window is splitted in a grid, each portion of the grid is called a split screen element.
  Different split screen elements can display different documents
*/
class Window_split_screen_element
{
public:
    Window_split_screen_element();
    Window_split_screen_element(const Window_split_screen_element & obj);
    Window_split_screen_element(Document * document, unsigned int index, Grid_layout grid_layout);
    friend void swap(Window_split_screen_element & obj1, Window_split_screen_element & obj2);
    Window_split_screen_element & operator=(Window_split_screen_element & obj);
    bool is_valid() const;
    friend std::ostream & operator<<(std::ostream & stream, const Window_split_screen_element & obj);
private:
    Document * document = nullptr;
    unsigned int index = -1;
    Grid_layout grid_layout;
};
std::ostream & operator<<(std::ostream & stream, const Window_split_screen_element & obj);

class Window_split_screen
{
public:
    void set_split_screen_layout(unsigned int number_of_rows, unsigned int number_of_columns);
    void set_split_screen_element(Window_split_screen_element & element, unsigned int row, unsigned int column);
    std::tuple<unsigned int, unsigned int> size();
    unsigned int max_rows() const;
    unsigned int max_columns() const;
    bool is_valid() const;
    friend std::ostream & operator<<(std::ostream & stream, const Window_split_screen & obj);
private:
    //perform some integrity check between the relation of some attribute of the class, returns true iff all is ok
    std::vector<std::vector<Window_split_screen_element>> window_split_screen_elements;
    unsigned int number_of_rows = 0;
    unsigned int number_of_columns = 0;
};
std::ostream & operator<<(std::ostream & stream, const Window_split_screen & obj);

#endif //WINDOW_SPLIT_SCREEN_H

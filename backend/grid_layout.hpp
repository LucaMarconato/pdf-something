#ifndef GRID_LAYOUT_H
#define GRID_LAYOUT_H

#include <iostream>
#include <tuple>

/*
  This class must not be confused with Window_split_screen.
  This class represents a grid view of a single document, for instance if the grid is 1x2 this is a the classical two-pages view of a .pdf. 
  The grid can be even as big as 6x6.
  For some slides and big screens the user may benefit from a 3x4 or a 4x5 grid.
  The grid layout is associated to a document and it is shared among all the devices. The user should avoid changing it because it is meant to enhance its visual memory.
  In fact, all the pages which are \equiv k \pmod (number_of_rows * number_of_columns) will be displayed in the same grid position when the user navigates throught the document.

  For instance, with a 2x3 grid, this is valid
     page6  page7  page8
     page9  page10 page11
   while this is not
     page5  page6  page7
     page8  page9  page10

  Note that in the case of a grid 1x2 of a book, the user may benefit to add a black page in the beginning, so to respect the usual layout of a book (otherwise the pages which in the book are to the right side will be displayed to the left side of the screen and vice-versa)
*/
class Grid_layout {
public:
    Grid_layout();
    Grid_layout(unsigned int number_of_rows, unsigned int number_of_columns);
    Grid_layout(const Grid_layout & obj);
    friend void swap(Grid_layout & obj1, Grid_layout & obj2);
    Grid_layout & operator=(Grid_layout obj);
    bool is_valid() const;
    /*
      Returns the first page to be displayed in the view which shows index as one element of the grid layout.
      Example: let say that the user has a 2x4 grid layout and wants to go to page 9, then this function will return 8.
               8 is returned for any of these arguments: 8, 9, 10, 11, 12, 13, 14, 15
    */
    unsigned int first_page_in_view_for_index(unsigned int index);
    std::tuple<unsigned int, unsigned int> size();
    friend std::ostream & operator<<(std::ostream & stream, const Grid_layout & obj);
    
private:
    unsigned int number_of_rows = -1;
    unsigned int number_of_columns = -1;
};

std::ostream & operator<<(std::ostream & stream, const Grid_layout & obj);

#endif // GRID_LAYOUT_H

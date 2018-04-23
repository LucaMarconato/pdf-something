#ifndef GRID_LAYOUT_H
#define GRID_LAYOUT_H

#include <iostream>
#include <tuple>

class Grid_layout {
public:
    Grid_layout();
    Grid_layout(unsigned int number_of_rows, unsigned int number_of_columns);
    Grid_layout(const Grid_layout & obj);
    bool is_valid() const;
    unsigned int first_page_in_view_for_index(unsigned int index);
    std::tuple<unsigned int, unsigned int> size();
    friend std::ostream & operator<<(std::ostream & stream, const Grid_layout & obj);
    
private:
    unsigned int number_of_rows = -1;
    unsigned int number_of_columns = -1;
};

std::ostream & operator<<(std::ostream & stream, const Grid_layout & obj);

#endif //GRID_LAYOUT_H

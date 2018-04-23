#include <window_split_screen.hpp>

unsigned int Window_split_screen::max_rows() const {
    //this is only when testing, we need to return a smaller number 
    return 1;
}

unsigned int Window_split_screen::max_columns() const {
    //this is only when testing, we need to return a smaller number 
    return 2;
}

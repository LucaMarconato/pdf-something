#include <window_split_screen.hpp>

/*
  Here we supports only 1 row and 2 columns.
  In an iPad we may choose to support a 1x2 or 2x1 split screen layout depending on the orientation of the screen, i.e. vertical or landscape.
*/

unsigned int Window_split_screen::max_rows() const {
    return 1;
}

unsigned int Window_split_screen::max_columns() const {
    return 2;
}

#ifndef WINDOW_H
#define WINDOW_H

#include <string>

#include "window_split_screen.hpp"
#include "virtual_screen.hpp"
#include "monitor.hpp"
#include "constants.hpp"

/*
  The class Window contains information about one window of the program, the program can have multiple windows opened (if the OS supports it, for instance this is not the case of iPad). 
  This application can have only one instance (i.e. main process) opened at time.

  If the application has multiple windows opened and it is closed, at the reopening the windows will be reopened, in the same Monitor, Virtual_screen and position they where opened.
  The classes Virtual_screen and Monitor are just sketched: for instance the OS can distinguish the various Monitor using an UUID or other forms of id
*/
class Virtual_screen;
class Monitor;

class Window
{
public:
    Window();
    Window(const Window & obj);
    friend void swap(Window & obj1, Window & obj2);
    Window & operator=(Window obj);
    void set_dimentions(double x0, double y0, double x1, double y1);
    void set_dimentions(bool fullscreen);
    friend std::ostream & operator<<(std::ostream & stream, const Window & obj);

    /*
      Here I am not using pointers because and copying these two objects everytime because they are lightweight and there will be only a small number of Window objects.
      We can opt to use pointers if we see that these objects are not so light, but let us postpone this when implementing Virtual_screen and Monitor in the frontend
    */
    Virtual_screen virtual_screen;
    Monitor monitor;
    Window_split_screen window_split_screen;
private:
    bool is_valid() const;
    //the following values can be negative (window partially outside the screen), are expressed in pixel, the axes are like in the Cartesian plane and to be valid must verify the macro VALID_WINDOW_SIZE(x0,y0,x1,y1) in constants.hpp
    double x0 = WINDOW_MIN_X - 1, y0 = WINDOW_MIN_Y - 1, x1 = WINDOW_MAX_X + 1, y1 = WINDOW_MAX_Y + 1;
    bool fullscreen = false;
};
std::ostream & operator<<(std::ostream & stream, const Window & obj);

#endif //WINDOW_H

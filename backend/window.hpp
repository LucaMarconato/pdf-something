#ifndef WINDOW_H
#define WINDOW_H

#include <string>

#include "window_layout.hpp"

/*
  The class Window contains information about one window of the program, the program can have multiple windows opened (if the OS supports it, for instance this is not the case of iPad). 
  This application can have only one instance (i.e. main process) opened at time.

  If the application has multiple windows opened and it is closed, at the reopening the windows will be reopened.
  The class Virtual_screen is used for storing the information about the virtual screen the window was living in, so to open each windows in the correct virtual screen
  The class Monitor is used for the same purpose.
  The classes Virtual_screen and Monitor are just sketched: for instance the OS can distinguish the various Monitor using an UUID or other forms of id
*/
class Virtual_screen
{
public:
    Virtual_screen();
    friend std::ostream & operator<<(std::ostream & stream, const Virtual_screen & obj);
private:
    bool initialized = false;
    int id;    
};
std::ostream & operator<<(std::ostream & stream, const Virtual_screen & obj);

class Monitor
{
public:
    Monitor();
    friend std::ostream & operator<<(std::ostream & stream, const Monitor & obj);
private:
    bool initialized = false;
    int id;
    std::string name;
};
std::ostream & operator<<(std::ostream & stream, const Monitor & obj);

class Window
{
public:
    Window(double x0, double y0, double x1, double y1);
    friend std::ostream & operator<<(std::ostream & stream, const Window & obj);

    //here I am using pointers because a reference cannot change its pointed value, a pointer of course can
    Virtual_screen * virtual_screen = nullptr;
    Monitor * monitor = nullptr;
private:
    //the following values are non-negative, respect x0 < x1 and y0 < y1, are expressed in pixel and the axes are like in the Cartesian plane
    double x0, y0, x1, y1;
};
std::ostream & operator<<(std::ostream & stream, const Window & obj);

#endif //WINDOW_H

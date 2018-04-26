#ifndef VIRTUAL_SCREEN_H
#define VIRTUAL_SCREEN_H

#include <iostream>

/*
  This class contains information about the virtual screen in which a to display a Window.
  The class is just sketched.
*/
class Virtual_screen
{
public:
    Virtual_screen();
    Virtual_screen(const Virtual_screen & obj);
    friend void swap(Virtual_screen & obj1, Virtual_screen & obj2);
    Virtual_screen & operator=(Virtual_screen obj);
    bool is_valid() const;
    friend std::ostream & operator<<(std::ostream & stream, const Virtual_screen & obj);
private:
    bool initialized = true;
    int id;    
};
std::ostream & operator<<(std::ostream & stream, const Virtual_screen & obj);

#endif // VIRTUAL_SCREEN_H

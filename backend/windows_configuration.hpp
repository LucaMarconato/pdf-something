#ifndef WINDOWS_CONFIGURATION_H
#define WINDOWS_CONFIGURATION_H

#include "window.hpp"

#include <iostream>
#include <list>

class Windows_configuration {
public:
    static void parse(char * file_content);
    static void print(std::ostream & stream);
    static std::list<Window> windows;
private:
    static bool is_valid();
    
    static bool already_initialized;
};

#endif //WINDOWS_CONFIGURATION_H

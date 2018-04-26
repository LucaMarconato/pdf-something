#ifndef WINDOWS_CONFIGURATION_H
#define WINDOWS_CONFIGURATION_H

#include "window.hpp"

#include <iostream>
#include <list>

class Windows_configuration {
public:
    Windows_configuration() = delete;
    static void parse(char * file_content);
    /* 
       The output uses HTML tags for displaying indentations correctly. 
       To display it just use "make run", which calls (as you can see in CMakeLists.txt), the following:
       "run ./canonical-frontend > output.html && bash put_into_html_body.sh output.html"

       There is no way to overload << for a "static" class, this is the reason why I declared the function print
    */
    static void print(std::ostream & stream);
    static std::list<Window> windows;
private:
    static bool is_valid();    
    static bool already_initialized;
};

#endif //WINDOWS_CONFIGURATION_H

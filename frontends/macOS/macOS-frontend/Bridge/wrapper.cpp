//
//  wrapper.cpp
//  macOS-frontend
//
//  Created by macbook on 12/04/2018.
//  Copyright © 2018 macbook. All rights reserved.
//

#include <string>
#include <cstring>
#include "backend.hpp"
// extern "C" will cause the C++ compiler
// (remember, this is still C++ code!) to
// compile the function in such a way that
// it can be called from C
// (and Swift).

char * std_string_to_c_string(std::string s0) {
    size_t length = s0.length() + 1;
    char * s1 = new char [length];
    std::strcpy(s1, s0.c_str());
    return s1;
}

extern "C" void freeString(char * string) {    
    delete [] string;
}

extern "C" char * getLastOpenedFile()
{
//    return std_string_to_c_string(get_last_opened_file().c_str());
    std::string s = "test";
    return std_string_to_c_string(s);
}

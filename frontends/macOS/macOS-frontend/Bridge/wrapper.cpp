//
//  wrapper.cpp
//  macOS-frontend
//
//  Created by macbook on 12/04/2018.
//  Copyright © 2018 macbook. All rights reserved.
//

#include <string>
#include <cstring>
#include <fstream>
#include <backend.hpp>
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

extern "C" char * getLastOpenedFile(const char * file)
{
//    return std_string_to_c_string(get_last_opened_file().c_str());
    std::string s = "test";
    const char * f = file+7;
    std::ofstream out(f);
    std::string to_write = "I am writing to a file with an iPad\n";
//    if(out.is_open()) {
//        out << to_write;
//        out.close();
//    }
    std::ifstream in(f);
    if(in.is_open()) {
        getline(in,s);
        in.close();
    }
    return std_string_to_c_string(s);
}

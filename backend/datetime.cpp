#include "datetime.hpp"

#include <sstream>
#include <iomanip> //for put_time()
#include <iostream>

Datetime::Datetime(std::string datetime)
{
    //the format is "yyyy-mm-dd hh:mm:ss"
    std::cout << "TODO: parse datetime from string \"" << datetime << "\" to std::time_t\n";
}

Datetime::Datetime()
{
    
}

Datetime Datetime::now()
{
    Datetime datetime;
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    datetime.time = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&datetime.time),"%F %T");
    datetime.string_representation = ss.str();
    datetime.initialized = true;
    return datetime;
}

std::ostream & operator<<(std::ostream & stream, const Datetime & obj)
{
    if(!obj.initialized) {
        stream << "<uninitalized datetime>";
    } else {
        stream << obj.string_representation;   
    }
    return stream;
}

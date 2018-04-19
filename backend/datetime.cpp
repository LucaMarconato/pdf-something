#include "datetime.hpp"

#include <sstream>
#include <iomanip> //for put_time()
#include <iostream>

Datetime::Datetime(std::string datetime)
{
    //the format is "yyyy-mm-dd hh:mm:ss"
    struct std::tm tm;
    std::istringstream ss(datetime);
    ss >> std::get_time(&tm, "%F %T");
    this->time = mktime(&tm);
    //TODO: check if the conversion was successful before claiming that this object is initalized
    this->initialized = true;
}

Datetime::Datetime()
{
    
}

Datetime Datetime::now()
{
    Datetime datetime;
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    datetime.time = std::chrono::system_clock::to_time_t(now);
    datetime.initialized = true;
    return datetime;
}

bool Datetime::is_valid() const
{
    if(!this->initialized) {
        std::cerr << "warning: uninitialized Datetime, this->initialized = " << this->initialized << "\n";
    }
    return this->initialized;
}

std::string Datetime::to_string() const
{
    std::stringstream ss;
    ss << std::put_time(std::localtime(&(this->time)),"%F %T");
    return ss.str(); 
}

std::ostream & operator<<(std::ostream & stream, const Datetime & obj)
{
    if(!obj.initialized) {
        stream << "<uninitalized datetime>";
    } else {
        stream << obj.to_string();
    }
    return stream;
}

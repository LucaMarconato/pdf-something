#include "datetime.hpp"

#include <sstream>
#include <iomanip> //for put_time()
#include <iostream>

#include "constants.hpp"

Datetime::Datetime() {}

Datetime::Datetime(std::string datetime)
{
    //the format is "yyyy-mm-dd hh:mm:ss"
    struct std::tm tm;
    std::istringstream ss(datetime);
    ss >> std::get_time(&tm, "%F %T");
    this->time = mktime(&tm);
    if(this->time == -1) {
        std::cerr << "error: mktime() failed the conversion\n";
    }
}

Datetime Datetime::now()
{
    Datetime datetime;
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    datetime.time = std::chrono::system_clock::to_time_t(now);
    return datetime;
}

bool Datetime::is_valid() const
{
    bool is_valid = true;
    is_valid = is_valid && this->time != -1;

    if(!is_valid) {
        std::cerr << "error: is_valid = -1\n";
        MY_ASSERT(false); exit(1);
    }
    return is_valid;
}

std::string Datetime::to_string() const
{
    std::stringstream ss;
    ss << std::put_time(std::localtime(&(this->time)),"%F %T");
    return ss.str(); 
}

std::ostream & operator<<(std::ostream & stream, const Datetime & obj)
{
    if(!obj.is_valid()) {
        stream << "[uninitalized datetime]";
    } else {
        stream << obj.to_string();
    }
    return stream;
}

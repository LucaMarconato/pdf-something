#ifndef DATETIME_H
#define DATETIME_H

#include <string>
#include <ctime>
#include <chrono>

/*
  This class provides an astraction layer in order to allow us to choose the preferred method for dealing with datetime.
  We will use this class for ordering the documents by latest opening
*/
class Datetime
{
public:
    Datetime();
    Datetime(std::string datetime);
    static Datetime now();
    bool is_valid() const;
    std::string to_string() const;

    friend std::ostream & operator<<(std::ostream & stream, const Datetime & obj);
private:
    // -1 is also the return value of mktime() when it encounters an error, mktime() is used in Datetime(std::string)
    std::time_t time = -1;
};

std::ostream & operator<<(std::ostream & stream, const Datetime & obj);

#endif //DATETIME_H

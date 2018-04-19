#ifndef DATETIME_H
#define DATETIME_H

#include <string>
#include <ctime>
#include <chrono>

/*
  This class provides an astraction layer in order to allow us to choose the preferred method for dealing with datetime.
  We will use this class for finding the latest visited/edited documents
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
    std::time_t time;
    bool initialized = false;
};

std::ostream & operator<<(std::ostream & stream, const Datetime & obj);

#endif //DATETIME_H

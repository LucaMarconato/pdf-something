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

    friend std::ostream & operator<<(std::ostream & stream, const Datetime & obj);

    std::string string_representation;
private:
    bool initialized = false;
    std::time_t time;
    
};

std::ostream & operator<<(std::ostream & stream, const Datetime & obj);

#endif //DATETIME_H

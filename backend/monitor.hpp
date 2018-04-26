#ifndef MONITOR_H
#define MONITOR_H

#include <iostream>
#include <string>

/*
  This class contains information about the monitor in which a to display a Window.
  The class is just sketched.
*/
class Monitor
{
public:
    Monitor();
    Monitor(const Monitor & obj);
    friend void swap(Monitor & obj1, Monitor & obj2);
    Monitor & operator=(Monitor obj);
    bool is_valid() const;
    friend std::ostream & operator<<(std::ostream & stream, const Monitor & obj);
private: 
    bool initialized = true;
    int id;
    std::string name;
};
std::ostream & operator<<(std::ostream & stream, const Monitor & obj);


#endif // MONITOR_H

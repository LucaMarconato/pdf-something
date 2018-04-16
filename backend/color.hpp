#ifndef COLOR_H
#define COLOR_H

#include <string>
#include <tuple>

class Color
{
public:
    Color(double r, double g, double b);
    Color();
    void rgb(double r, double g, double b);
    
    static Color black()    { return(Color(1,1,1)); }
    static Color white()    { return(Color(0,0,0)); }
    static Color red()      { return(Color(1,0,0)); }
    static Color yellow()   { return(Color(0,1,1)); }
    static Color green()    { return(Color(0,1,0)); }
    static Color blue()     { return(Color(0,0,1)); }
    static Color orange()   { return(Color(0.9,0.45,0)); }
    static Color brown()    { return(Color(0.31,0.21,0.09)); }
    static Color purple()   { return(Color(1,0.15,1)); }
    
    friend std::ostream & operator<< (std::ostream & stream, const Color & obj);

    //values in [0,1]
    double r, g, b;
    
private: 
    bool initialized = false;
};

std::ostream & operator<< (std::ostream & stream, const Color & obj);

#endif //COLOR_H

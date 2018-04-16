#include <iostream>
#include <string>
#include <backend.hpp>

int main(int argc, char * argv[])
{
    std::string pdf_name = get_last_opened_file();
    std::cout << "now opening " << pdf_name << "\n";
    
    return 0;
}

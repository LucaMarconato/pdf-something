#ifndef FILE_H
#define FILE_H

#include <string>

#include "../uuid.hpp"

/*
  Each operating system as his own way of dealing with files, expecially mobile systems. 
  This class is used as a protocol to handle basic operations with files (we do not need something as complex as std::fstream), and it will be implemented by each frontend.
*/

class File {
public:
  //for how the code is structured we need only binary read/write, because we always write as char *
    enum Opening_mode {
        // READ, WRITE, APPEND, READ_BINARY, WRITE_BINARY, APPEND_BINARY;
        READ_BINARY, WRITE_BINARY, APPEND_BINARY
    };
    
    File();
    File(std::string path, Opening_mode opening_mode);
    bool open(std::string path, Opening_mode opening_mode);
    ~File();
    void close();
    static bool exists(std::string path);
    unsigned long long size();
    //we are not returing the content but we are storing it in this class so we are sure that its memory is freed correctly when the destructor is called
    //this prevents memory leak but we have to be careful to not have the destructor of File called to early
    void read_all_content(bool append_null);
    void write(char * to_write, int bytes);
    void write(std::string to_write);

    char * content = nullptr;
    bool is_open = false;
private:
    Opening_mode opening_mode;
    std::string file_path;
    /*
      When the constructor is called, the frontend must create an instance of a file handler (e.g. std::fstream, FILE *, ...). This object cannot be stored inside the class because it can be something exotic (like what happen in iOS). 
      A way to make the frontend able to store it is to create a dictionary, indexed by an UUID, that stores the file handler.
      The resource will then be freed by the frontend when the destructor of this class is called.
    */    
    Uuid uuid_of_frontend_resource;
};

#endif //FILE_H

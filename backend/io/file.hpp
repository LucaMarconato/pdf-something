#ifndef FILE_H
#define FILE_H

#include <string>

#include "../uuid.hpp"

/*
  std::fstream works with iOS, according that the frontend provides the path the application is allowed to write into.
  In fact, in iOS you cannot write in the application bundle but only to a specific path.
  I wrote this class as an interface to be implemented in each frontend because I did not belived that you could use std::fstream in iOS, but since I discovered that it works, this class, as it is, is useless.
  One thing that this class should do is to tell the backend the path it is allowed to write.
  
  Anyway, this class is really simple, and if we will have some problems in dealing with files with some OS we can rely on this.
*/

class File {
public:
    // for how the code is structured we need only binary read/write, because we always write as char *
    enum Opening_mode {
        READ_BINARY, WRITE_BINARY, APPEND_BINARY
    };
    
    File();
    File(std::string path, Opening_mode opening_mode);
    bool open(std::string path, Opening_mode opening_mode);
    ~File();
    void close();
    static bool exists(std::string path);
    unsigned long long size();
    /*
      The memory is allocated in the frontend implementation of this file and will be freed by the caller of the function read_all_content()
      append_null is used if one wants to use the read chars as a C string and not as a raw array of bytes
    */
    void read_all_content(bool append_null, char ** buffer);
    void write(char * to_write, int bytes);
    void write(std::string to_write);

    bool is_open = false;
private:
    Opening_mode opening_mode;
    std::string file_path;
    /*
      When the constructor is called, the frontend must create an instance of a file handler (e.g. std::fstream, FILE *, ...). This object cannot be stored inside the class because it can be something exotic (like what happen in iOS). 
      A way to make the frontend able to store it is to create a dictionary, indexed by an UUID, that stores the file handler.
      The resource must then be freed by the frontend when the destructor of this class is called.
    */    
    Uuid uuid_of_frontend_resource;
};

#endif //FILE_H

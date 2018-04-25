#include <io/file.hpp>

#include <iostream>
#include <map>
#include <string>
#include <fstream>

std::map <Uuid, std::fstream*> fstreams;

File::File()
{
    
}

File::File(std::string path, Opening_mode opening_mode)
{
    this->open(path, opening_mode);
}

bool File::open(std::string path, Opening_mode opening_mode)
{
    Uuid uuid;
    std::fstream * file = new std::fstream();
    this->file_path = path;
    this->uuid_of_frontend_resource = uuid;
    this->opening_mode = opening_mode;
    switch(this->opening_mode) {
    case File::READ_BINARY:
        file->open(path, std::ios::in | std::ios::binary);
        break;
    case File::WRITE_BINARY:
        file->open(path, std::ios::out | std::ios::binary);
        break;
    case File::APPEND_BINARY:
        file->open(path, std::ios::app | std::ios::binary);
        break;        
    default:
        std::cerr << "error: opening_mode = " << this->opening_mode << "\n";
        delete file;
        exit(1);
    }
    if(!file->is_open()) {
        std::cerr << "error: cannot open file, path = " << path << ", opening_mode = " << this->opening_mode << "\n";
        delete file;
        return false;
    }
    ::fstreams[uuid] = file;
    this->is_open = true;
    return true;
}

File::~File()
{
    this->close();
}

void File::close()
{
    
    if(!this->is_open) {
        // this means that the destructor was already called, so we can ignore this call
        return;
    }

    auto e = ::fstreams.find(this->uuid_of_frontend_resource);
    if(e == ::fstreams.end()) {
        std::cerr << "error: cannot find frontend resource, this->uuid_of_frontend_resource = " << this->uuid_of_frontend_resource << "\n";
        exit(1);
    }
    delete ::fstreams[this->uuid_of_frontend_resource];
    ::fstreams.erase(this->uuid_of_frontend_resource);
    this->is_open = false;
}

bool File::exists(std::string path)
{
    // here we are not really checking if a file exists but if it can be opened, anyway for our case it will work
    std::ifstream file(path);
    return(file.is_open());
}

unsigned long long File::size()
{
    std::fstream * file = ::fstreams[this->uuid_of_frontend_resource];
    unsigned long long original_position = file->tellg();
    file->seekg(0, std::ios::end);
    unsigned long long file_size = file->tellg();
    file->clear();
    file->seekg(original_position, std::ios::beg);
    return file_size;
}

void File::read_all_content(bool append_null, char ** buffer)
{
    if(this->opening_mode != File::READ_BINARY) {
        std::cerr << "error: this->opening_mode = " << this->opening_mode << "\n";
        exit(1);
    }
    std::fstream * file = ::fstreams[this->uuid_of_frontend_resource];
    if(*buffer != nullptr) {
        std::cerr << "error: *buffer != nullptr\n";
        exit(1);
    }
    unsigned long long file_size = this->size();
    *buffer = new char [file_size + (append_null ? 1 : 0)];
    
    file->read(*buffer, file_size);
    if(append_null) {
        (*buffer)[file_size] = '\0';
    }
}

void File::write(char * to_write, int bytes)
{
    if(this->opening_mode != File::WRITE_BINARY && this->opening_mode != File::APPEND_BINARY) {
        std::cerr << "error: this->opening_mode = " << this->opening_mode << "\n";
        exit(1);
    }    
    std::fstream * file = ::fstreams[this->uuid_of_frontend_resource];
    file->write(to_write, bytes);
}

void File::write(std::string to_write)
{
    if(this->opening_mode != File::WRITE_BINARY && this->opening_mode != File::APPEND_BINARY) {
        std::cerr << "error: this->opening_mode = " << this->opening_mode << "\n";
        exit(1);
    }        
    this->write(const_cast<char *>(to_write.c_str()), to_write.length()+1);
}


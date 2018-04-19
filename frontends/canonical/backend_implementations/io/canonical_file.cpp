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
    //I do not remember the correct syntax in C++
    switch(this->opening_mode) {
    // case File::READ:
    //     file.open(path, std::ios::in);
    //     break;
    // case File::WRITE:
    //     file.open(path, std::ios::out);
    //     break;
    // case File::APPEND:
    //     file.open(path, std::ios::app);
    //     break;
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
        delete file;
        std::cerr << "error: cannot open file, path = " << path << ", opening_mode = " << this->opening_mode << "\n";
        return false;
    }
    ::fstreams[uuid] = file;
    // ::fstreams.insert(std::make_pair(uuid,file));    
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
        //if all is correct the destructor was already called so we can ignore this call
        return;
    }
    if(this->content != nullptr) {
        delete [] this->content;
    }    
    delete ::fstreams[this->uuid_of_frontend_resource];
    auto e = ::fstreams.find(this->uuid_of_frontend_resource);
    if(e == ::fstreams.end()) {
        std::cerr << "error: cannot find frontend resource, this->uuid_of_frontend_resource = " << this->uuid_of_frontend_resource << "\n";
        exit(1);
    }
    ::fstreams.erase(this->uuid_of_frontend_resource);
    this->is_open = false;
}

bool File::exists(std::string path)
{
    //it is not the same thing, but for our case it will work in the canonical backend
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

void File::read_all_content(bool append_null)
{
    std::fstream * file = ::fstreams[this->uuid_of_frontend_resource];
    if(this->content != nullptr) {
        std::cerr << "error: this->content != nullptr, probably read_all_content() has already been called\n";
        return;
    }
    unsigned long long file_size = this->size();
    this->content = new char [file_size + (append_null ? 1 : 0)];
    
    file->read(this->content, file_size);
    if(append_null) {
        this->content[file_size] = '\0';
    }
}

void File::write(char * to_write, int bytes)
{
    std::fstream * file = ::fstreams[this->uuid_of_frontend_resource];
    file->write(to_write, bytes);
}

void File::write(std::string to_write)
{
    this->write(const_cast<char *>(to_write.c_str()), to_write.length()+1);
}


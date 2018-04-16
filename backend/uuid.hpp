#ifndef UUID_H
#define UUID_H

#include <string>
#include <vector>

/*
  this class provide an astraction layer in order to allow us to choose the preferred method for dealing with uuids. Here I am using boost for doing that
*/
class Uuid
{
public:
    Uuid();
    bool operator==(const Uuid & u) const;
    //here I am using a string for representing an uuid, but we will need to use the byte representation
    std::string uuid_string;

private:    
    //if one needs to create more than one uuid, it is faster to use only one boost::uuids::random_generator, so I am passing the count argument and return a vector of uuids, represented as strings.
    static std::vector<std::string> generate_uuids(int count); 
};

std::ostream & operator<<(std::ostream & stream, const Uuid & obj);

#endif //UUID_H

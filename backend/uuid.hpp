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
    Uuid(std::string uuid_string);
    bool is_valid() const;
    bool operator==(const Uuid & u) const;
    bool operator!=(const Uuid & u) const;

    //for using an Uuid as a key in an std::map
    friend bool operator<(Uuid const & lhs, Uuid const & rhs);
    friend std::ostream & operator<<(std::ostream & stream, const Uuid & obj);
    
    //here I am using a string for representing an uuid, but we will need to use the byte representation   
    std::string uuid_string = "";
    /*
      Sometime we will need to ask the uuid of an object (for instance when asking the backend which was the latest opened pdf). This flag will let us determine if such object is not available (in the example above, when the applicaiton opens for the first time and so there is no pdf to be reopened, this flag will be true)
    */
    bool empty_uuid = true;

private:    
    //if one needs to create more than one uuid, it is faster to use only one boost::uuids::random_generator, so I am passing the count argument and return a vector of uuids, represented as strings.
    static std::vector<std::string> generate_uuids(int count); 
};

std::ostream & operator<<(std::ostream & stream, const Uuid & obj);

#endif //UUID_H

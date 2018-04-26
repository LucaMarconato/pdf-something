#ifndef UUID_H
#define UUID_H

#include <string>
#include <vector>
#include <boost/functional/hash.hpp>
#include <boost/uuid/uuid.hpp> //uuid class

/*
  This class provides an astraction layer in order to allow us to choose the preferred method for dealing with uuids. 
  Here I am using boost
*/
class Uuid
{
public:
    Uuid();
    Uuid(std::string uuid_string);
    Uuid(boost::uuids::uuid boost_uuid);
    std::string to_string() const;
    bool is_valid() const;
    bool operator==(const Uuid & u) const;
    bool operator!=(const Uuid & u) const;

    //for using uuids in std::map
    friend bool operator<(Uuid const & lhs, Uuid const & rhs);
    friend std::ostream & operator<<(std::ostream & stream, const Uuid & obj);

    boost::uuids::uuid boost_uuid;
    bool empty_uuid = true;

private:    
    // if one needs to create more than one uuid, it is faster to use only one boost::uuids::random_generator, so I am passing the count argument and return a vector of Uuid
    static std::vector<Uuid> generate_uuids(int count); 
};

std::ostream & operator<<(std::ostream & stream, const Uuid & obj);

// for using uuids in std::unordered_map
namespace std {
    template<>
    struct hash<Uuid>
    {
        size_t operator () (const Uuid & u) const noexcept
        {
            return boost::hash<boost::uuids::uuid>()(u.boost_uuid);
        }
    };
}

#endif //UUID_H

#ifndef UUID_H
#define UUID_H

#include <string>
#include <vector>
#include <boost/functional/hash.hpp>
#include <boost/uuid/uuid.hpp> //uuid class

/*
  This structure is defined to be able to pass by copy the type uint8_t [16].
  A boost::uuids::uuid is stored in this format
*/
struct Compact_uuid {
    uint8_t data [16];
};

bool operator==(const Compact_uuid & lhs, const Compact_uuid & rhs);

/*
  This class provide an astraction layer in order to allow us to choose the preferred method for dealing with uuids. 
  Here I am using boost for doing that
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

    friend bool operator<(Uuid const & lhs, Uuid const & rhs);
    friend std::ostream & operator<<(std::ostream & stream, const Uuid & obj);

    // byte representation of an Uuid
    boost::uuids::uuid boost_uuid;
    Compact_uuid compact_uuid;
    bool empty_uuid = true;

private:    
    // if one needs to create more than one uuid, it is faster to use only one boost::uuids::random_generator, so I am passing the count argument and return a vector of uuids, represented as strings.
    static std::vector<Uuid> generate_uuids(int count); 
};

std::ostream & operator<<(std::ostream & stream, const Uuid & obj);

std::size_t hash_value(Uuid const & uuid);

// here I am defining my own hash because I am using Compact_uuid in some std::unordered_map and not boost::uuids::uuid
namespace std {
    template <>
    struct hash<Compact_uuid> {
        std::size_t operator()(const Compact_uuid & u) const noexcept {
            auto h = std::hash<uint8_t>{}(u.data[0]);
            for(int i = 1; i < 1; i++) {
                h ^= std::hash<uint8_t>{}(u.data[i]);
            }
            return h;
        }
    };
    // template <>
    // struct hash<Uuid> {
    //     std::size_t operator()(const Uuid & u) const noexcept {
    //         return std::hash<Compact_uuid>{}(u.compact_uuid);
    //     }
    // };
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

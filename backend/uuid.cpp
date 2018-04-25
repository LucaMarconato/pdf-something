#include "uuid.hpp"

#include <iostream>
#include <cstdio>

#include <boost/uuid/uuid.hpp> //uuid class
#include <boost/uuid/uuid_generators.hpp> //generate uuid
#include <boost/uuid/uuid_io.hpp> //streaming for uuids
#include <boost/lexical_cast.hpp> //for converting a boost::uuid to an std::string

bool operator==(const Compact_uuid & lhs, const Compact_uuid & rhs)
{
    bool equal = lhs.block0 == rhs.block0 && lhs.block1 == rhs.block1 && lhs.block2 == rhs.block2 && lhs.block3 == rhs.block3;
    return equal;
}

Uuid::Uuid()
{
    // this->uuid_string = Uuid::generate_uuids(1).front();
    this->empty_uuid = false;
}

Uuid::Uuid(std::string uuid_string)
{
    this->uuid_string = uuid_string;
    this->create_compact_uuid();
    this->empty_uuid = false;
}

bool Uuid::is_valid() const
{
    if(this->empty_uuid) {
        std::cerr << "warning: this->empty_uuid = " << this->empty_uuid << "\n";        
    }
    return !this->empty_uuid;
}

std::vector<std::string> Uuid::generate_uuids(int count)
{
    // std::cerr << "generated an uuid!\n";
    std::vector<std::string> uuids(count);
    boost::uuids::random_generator generator;

    for(int i = 0; i < count; i++) {
        boost::uuids::uuid uuid = generator();
        uuids[i] = boost::lexical_cast<std::string>(uuid);
    }
    return uuids;
}

bool Uuid::operator==(const Uuid & u) const
{
    return this->compact_uuid == u.compact_uuid;
}

bool Uuid::operator!=(const Uuid & u) const
{
    return !(this->operator==(u));
}

// void Uuid::bulk_generate_uuid_async()
// {
    
// }

bool operator<(Uuid const & lhs, Uuid const & rhs)
{
    return lhs.uuid_string < rhs.uuid_string;
}

void Uuid::create_compact_uuid()
{
    /*
      Example of an uuid: 123e4567-e89b-12d3-a456-426655440000
                          |   |   |   |   |   |   |   |   |         
                          0   4   8   12  16  20  24  28  32  
    */
    char block[9];
    block[8] = '\0';
    
    //first 8 hex digits
    for(int i = 0; i < 8; i++) {
        block[i] = this->uuid_string[i];
    }
    this->compact_uuid.block0 = strtol(block, NULL, 16);

    //next 8 hex digits
    for(int i = 0; i < 4; i++) {
        block[i] = this->uuid_string[9+i];
        block[4+i] = this->uuid_string[14+i];
    }
    this->compact_uuid.block1 = strtol(block, NULL, 16);

    //next 8 hex digits
    for(int i = 0; i < 4; i++) {
        block[i] = this->uuid_string[19+i];
        block[4+i] = this->uuid_string[24+i];
    }
    this->compact_uuid.block2 = strtol(block, NULL, 16);

    //last 8 hex digits
    for(int i = 0; i < 8; i++) {
        block[i] = this->uuid_string[28+i];
    }
    this->compact_uuid.block3 = strtol(block, NULL, 16);    
}

// Uuid::operator Compact_uuid()
// {
//     if(this->empty_uuid) {
//         std::cerr << "error: attempting to cast an empty Uuid, aborting\n";
//         exit(1);
//     }
//     return this->compact_uuid;
// }

std::ostream & operator<<(std::ostream & stream, const Uuid & obj)
{
    stream << obj.uuid_string;
    return stream;
}

std::size_t hash_value(Uuid const & uuid)
{
    boost::hash<std::string> hasher;
    return hasher(uuid.uuid_string);
}

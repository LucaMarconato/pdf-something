#include "uuid.hpp"

#include <iostream>

#include <boost/uuid/uuid.hpp> //uuid class
#include <boost/uuid/uuid_generators.hpp> //generate uuid
#include <boost/uuid/uuid_io.hpp> //streaming for uuids
#include <boost/lexical_cast.hpp> //for converting a boost::uuid to an std::string

Uuid::Uuid()
{
    this->uuid_string = Uuid::generate_uuids(1).front();
    this->empty_uuid = false;
}

Uuid::Uuid(std::string uuid_string)
{
    this->uuid_string = uuid_string;
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
    return this->uuid_string == u.uuid_string;
}

bool Uuid::operator!=(const Uuid & u) const
{
    return !(this->operator==(u));
}

bool operator<(Uuid const & lhs, Uuid const & rhs)
{
    return lhs.uuid_string < rhs.uuid_string;
}

std::ostream & operator<<(std::ostream & stream, const Uuid & obj)
{
    stream << obj.uuid_string;
    return stream;
}

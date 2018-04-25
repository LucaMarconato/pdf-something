#include "uuid.hpp"

#include <iostream>
#include <cstdio>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_generators.hpp> //generate uuid
#include <boost/uuid/uuid_io.hpp> //streaming for uuids


bool operator==(const Compact_uuid & lhs, const Compact_uuid & rhs)
{
    for(int i = 0; i < 16; i++) {
        if(lhs.data[i] != rhs.data[i]) {
            return false;
        }
    }
    return true;
}

Uuid::Uuid()
{
    this->empty_uuid = true;
}

Uuid::Uuid(boost::uuids::uuid boost_uuid)
{
    this->boost_uuid = boost_uuid;
    memcpy(this->compact_uuid.data,boost_uuid.data,16);
    this->empty_uuid = false;
}

Uuid::Uuid(std::string uuid_string)
{
    this->boost_uuid = boost::lexical_cast<boost::uuids::uuid>(uuid_string);
    memcpy(this->compact_uuid.data,boost_uuid.data,16);
    this->empty_uuid = false;
}

bool Uuid::is_valid() const
{
    if(this->empty_uuid) {
        std::cerr << "error: this->empty_uuid = " << this->empty_uuid << "\n";
        exit(1);
    }
    return !this->empty_uuid;
}

std::vector<Uuid> Uuid::generate_uuids(int count)
{
    std::vector<Uuid> uuids(count);
    boost::uuids::random_generator generator;

    for(int i = 0; i < count; i++) {
        boost::uuids::uuid boost_uuid = generator();
        uuids.emplace_back(boost_uuid);
    }
    return uuids;
}

std::string Uuid::to_string() const
{
    return boost::lexical_cast<std::string>(this->boost_uuid);
}

bool Uuid::operator==(const Uuid & u) const
{
    return this->compact_uuid == u.compact_uuid;
}

bool Uuid::operator!=(const Uuid & u) const
{
    return !(this->operator==(u));
}

bool operator<(Uuid const & lhs, Uuid const & rhs)
{
    for(int i = 0; i < 16; i++) {
        if(lhs.compact_uuid.data[i] < rhs.compact_uuid.data[i]) {
            return true;
        } else if(lhs.compact_uuid.data[i] > rhs.compact_uuid.data[i]) {
            return false;
        }
    }
    //the uuids are equals
    return false;
}

std::ostream & operator<<(std::ostream & stream, const Uuid & obj)
{
    stream << obj.to_string();
    return stream;
}

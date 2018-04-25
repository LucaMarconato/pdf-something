#include "uuid.hpp"

#include <iostream>
#include <cstdio>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_generators.hpp> //generate uuid
#include <boost/uuid/uuid_io.hpp> //streaming for uuids

Uuid::Uuid() {}

Uuid::Uuid(boost::uuids::uuid boost_uuid)
{
    this->boost_uuid = boost_uuid;
    this->empty_uuid = false;
}

Uuid::Uuid(std::string uuid_string)
{
    this->boost_uuid = boost::lexical_cast<boost::uuids::uuid>(uuid_string);
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
    return this->boost_uuid == u.boost_uuid;
}

bool Uuid::operator!=(const Uuid & u) const
{
    return !(this->operator==(u));
}

bool operator<(Uuid const & lhs, Uuid const & rhs)
{
    return lhs.boost_uuid < rhs.boost_uuid;
}

std::ostream & operator<<(std::ostream & stream, const Uuid & obj)
{
    stream << obj.to_string();
    return stream;
}

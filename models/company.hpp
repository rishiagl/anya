#pragma once

#include <string>
#include <vector>
#include "database.hpp"

namespace models::company
{
    typedef struct attributes
    {
        int id;
        std::string company_id;
        std::string name;
        std::string address;
        std::string city;
        std::string state;
        std::string country;
    } attributes;

    std::vector<attributes> get();
    std::string add(attributes);
    attributes get(std::string id);
}

template <>
struct glz::meta<models::company::attributes>
{
    using T = models::company::attributes;
    static constexpr auto value = object("id", &T::id, "company_id", &T::company_id, "name", &T::name, "address", &T::address, "city", &T::city, "state", &T::state, "country", &T::country);
};
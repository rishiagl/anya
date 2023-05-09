#pragma once

#include <string>
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

    attributes get();
    attributes get(int id);
    //attributes get(std::string company_id);
}

template <>
struct glz::meta<models::company::attributes>
{
    using T = models::company::attributes;
    static constexpr auto value = object("id", &T::id, "company_id", &T::company_id, "name", &T::name, "address", &T::address, "city", &T::city, "state", &T::state, "country", &T::country);
};
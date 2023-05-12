#pragma once

#include <string>
#include <vector>
#include "database.hpp"

namespace models::company
{
    typedef struct attributes
    {
        int pid;
        std::string sid;
        std::string name;
        std::string address;
        std::string city;
        std::string state;
        std::string country;
        std::string cin;
        std::string pan;
        std::string gstin;
    } attributes;

    std::vector<attributes> get();
    std::string add(attributes);
    attributes get(std::string sid);
    void update(attributes att, std::string sid);
    void remove(std::string sid);
}

template <>
struct glz::meta<models::company::attributes>
{
    using T = models::company::attributes;
    static constexpr auto value = object("pid", &T::pid, "sid", &T::sid, "name", &T::name, "address", &T::address, "city", &T::city, "state", &T::state, "country", &T::country, "cin", &T::cin, "pan", &T::pan, "gstin", &T::gstin);
};
#pragma once

#include <string>
#include <vector>
#include "database.hpp"

namespace models::tax_class
{
    typedef struct attributes
    {
        int pid;
        int code;
        std::string type_of_code;
        std::string description;
        int rate;
    } attributes;

    std::vector<attributes> get();
    int add(attributes);
    attributes get(int code);
    void update(attributes att, int code);
    void remove(int code);
}

template <>
struct glz::meta<models::tax_class::attributes>
{
    using T = models::tax_class::attributes;
    static constexpr auto value = object("pid", &T::pid, "code", &T::code, "type_of_code", &T::type_of_code, "description", &T::description, "rate", &T::rate);
};
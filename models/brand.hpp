#pragma once

#include <string>
#include <vector>
#include "database.hpp"

namespace models::brand
{
    typedef struct attributes
    {
        int pid;
        std::string sid;
        std::string name;
        std::string company_sid;
    } attributes;

    std::vector<attributes> get();
    std::string add(attributes);
    attributes get(std::string sid);
    void update(attributes att, std::string sid);
    void remove(std::string sid);
}

template <>
struct glz::meta<models::brand::attributes>
{
    using T = models::brand::attributes;
    static constexpr auto value = object("pid", &T::pid, "sid", &T::sid, "name", &T::name, "company_sid", &T::company_sid);
};
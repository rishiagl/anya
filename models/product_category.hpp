#pragma once

#include <string>
#include <vector>
#include "database.hpp"

namespace models::product_category
{
    typedef struct attributes
    {
        int pid;
        std::string sid;
        std::string name;
    } attributes;

    std::vector<attributes> get();
    std::string add(attributes);
    attributes get(std::string sid);
    void update(attributes att, std::string sid);
    void remove(std::string sid);
}

template <>
struct glz::meta<models::product_category::attributes>
{
    using T = models::product_category::attributes;
    static constexpr auto value = object("pid", &T::pid, "sid", &T::sid, "name", &T::name);
};
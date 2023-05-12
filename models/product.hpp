#pragma once

#include <string>
#include <vector>
#include "database.hpp"

namespace models::product
{
    typedef struct attributes
    {
        int pid;
        std::string sid;
        std::string name;
        std::string brand_sid;
        std::string category_sid;
        std::string tax_class_code;
        std::string type_of_supply;
    } attributes;

    std::vector<attributes> get();
    std::string add(attributes);
    attributes get(std::string sid);
    void update(attributes att, std::string sid);
    void remove(std::string sid);
}

template <>
struct glz::meta<models::product::attributes>
{
    using T = models::product::attributes;
    static constexpr auto value = object("pid", &T::pid, "sid", &T::sid, "name", &T::name, "brand_sid", &T::brand_sid, "category_sid", &T::category_sid, "tax_class_code", &T::tax_class_code, "type_of_supply", &T::type_of_supply);
};
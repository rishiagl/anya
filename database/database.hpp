#pragma once

#include <drogon/orm/DbClient.h>
#include <glaze/glaze.hpp>

namespace database
{
    void storeDBClient(drogon::orm::DbClientPtr &dbclient);
    drogon::orm::DbClientPtr getDBClient();
}

namespace entity
{
    typedef struct company
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
    } company;

    typedef struct brand
    {
        int pid;
        std::string sid;
        std::string name;
        std::string company_sid;
    } brand;

    typedef struct product_category
    {
        int pid;
        std::string sid;
        std::string name;
    } product_category;

    typedef struct tax_class
    {
        int pid;
        int code;
        std::string type_of_code;
        std::string description;
        int rate;
    } tax_class;

    typedef struct product
    {
        int pid;
        std::string sid;
        std::string name;
        std::string brand_sid;
        std::string category_sid;
        std::string tax_class_code;
        std::string type_of_supply;
    } product;

    typedef struct account
    {
        int pid;
        std::string sid;
        std::string name;
        std::string usrname;
        std::string passwd;
    } account;

    typedef struct User{
        int pid;
        std::string name;
        std::string email;
        std::string usrname;
        std::string passwd;
    }
}

template <>
struct glz::meta<entity::brand>
{
    using T = entity::brand;
    static constexpr auto value = object("pid", &T::pid, "sid", &T::sid, "name", &T::name, "company_sid", &T::company_sid);
};

template <>
struct glz::meta<entity::company>
{
    using T = entity::company;
    static constexpr auto value = object("pid", &T::pid, "sid", &T::sid, "name", &T::name, "address", &T::address, "city", &T::city, "state", &T::state, "country", &T::country, "cin", &T::cin, "pan", &T::pan, "gstin", &T::gstin);
};

template <>
struct glz::meta<entity::product_category>
{
    using T = entity::product_category;
    static constexpr auto value = object("pid", &T::pid, "sid", &T::sid, "name", &T::name);
};

template <>
struct glz::meta<entity::tax_class>
{
    using T = entity::tax_class;
    static constexpr auto value = object("pid", &T::pid, "code", &T::code, "type_of_code", &T::type_of_code, "description", &T::description, "rate", &T::rate);
};

template <>
struct glz::meta<entity::product>
{
    using T = entity::product;
    static constexpr auto value = object("pid", &T::pid, "sid", &T::sid, "name", &T::name, "brand_sid", &T::brand_sid, "category_sid", &T::category_sid, "tax_class_code", &T::tax_class_code, "type_of_supply", &T::type_of_supply);
};

template <>
struct glz::meta<entity::account>
{
    using T = entity::account;
    static constexpr auto value = object("pid", &T::pid, "sid", &T::sid, "name", &T::name, "usrname", &T::usrname, "passwd", &T::passwd);
};

template <>
struct glz::meta<entity::User>
{
    using T = entity::User;
    static constexpr auto value = object("pid", &T::pid, "name", &T::name, "email", &T::email, "usrname", &T::usrname, "passwd", &T::passwd);
};
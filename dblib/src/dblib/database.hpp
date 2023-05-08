#ifndef DBLIB_HPP_INCLUDED
#define DBLIB_HPP_INCLUDED
#include <drogon/orm/DbClient.h>
#include <rapidjson/document.h>

namespace dblib
{
    namespace company{
        struct attributes {
        int id;
        std::string company_id;
        std::string name;
        std::string address;
        std::string city;
        std::string state;
        std::string country;
        }company;

        attributes* getByID(int id);
        attributes* getByID(std::string company_id);
    }
    void storeDBClient(drogon::orm::DbClientPtr& dbclient);
    drogon::orm::DbClientPtr getDBClient();
    std::string getCompanyIdbyId(int id);
}

#endif
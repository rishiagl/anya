#ifndef DBLIB_HPP_INCLUDED
#define DBLIB_HPP_INCLUDED
#include <drogon/orm/DbClient.h>
#include <drogon/orm/SqlBinder.h>
namespace dblib{
    void storeDBClient(drogon::orm::DbClientPtr dbclient);
    drogon::orm::DbClientPtr getDBClient();
    std::string getCompanyIdbyId(int id); 
}

#endif
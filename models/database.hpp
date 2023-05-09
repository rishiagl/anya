#pragma once

#include <drogon/orm/DbClient.h>

#include "glaze/glaze.hpp"

namespace models
{
    void storeDBClient(drogon::orm::DbClientPtr& dbclient);
    drogon::orm::DbClientPtr getDBClient();
    std::string getCompanyIdbyId(int id);
}
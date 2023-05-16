#include <drogon/drogon.h>
#include <iostream>
#include "database/database.hpp"

int main()
{
    drogon::app().loadConfigFile("../config.json");
    drogon::app().registerBeginningAdvice([]()
                                          {
                                            LOG_DEBUG << "Server started";
                                            auto dbClient = drogon::app().getDbClient("postgres");
                                            database::storeDBClient(dbClient); });
    drogon::app().run();
    return 0;
}

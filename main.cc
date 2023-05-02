#include <drogon/drogon.h>
#include <iostream>
#include<dblib/database.hpp>
int main()
{
    drogon::app().loadConfigFile("../config.json");
    drogon::app().registerBeginningAdvice([]()
                                          {
        LOG_DEBUG << "begin advice";
        auto dbClient = drogon::app().getDbClient("postgres");
        dblib::storeDBClient(dbClient);
        auto db = dblib::getDBClient();

        LOG_DEBUG<<"dbClient:"<<dbClient.get();
        LOG_DEBUG<<"company_id for id = 1 = "<<dblib::getCompanyIdbyId(1);});
    drogon::app().run();
    return 0;
}

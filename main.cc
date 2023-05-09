#include <drogon/drogon.h>
#include <iostream>
#include "models/database.hpp"

int main()
{
    drogon::app().loadConfigFile("../config.json");
    drogon::app().registerBeginningAdvice([]()
                                          {
                                              LOG_DEBUG << "begin advice";
                                              //   auto dbClient = drogon::app().getDbClient("postgres");
                                              //   std::string cid;
                                              //   try
                                              //   {
                                              //       auto result = dbClient->execSqlSync("SELECT shop_id FROM anya.company WHERE id=$1 ", 1);
                                              //       for (auto row : result)
                                              //       {
                                              //           cid = row["shop_id"].as<std::string>();
                                              //       }
                                              //   }
                                              //   catch (const drogon::orm::DrogonDbException &e)
                                              //   {
                                              //       std::cerr << "error:" << e.base().what() << std::endl;
                                              //   }
                                              //   LOG_DEBUG << "dbClient:" << dbClient.get();
                                              //   LOG_DEBUG<<"company_id for id = 1 = "<< cid;
                                            auto dbClient = drogon::app().getDbClient("postgres");
                                            models::storeDBClient(dbClient);
                                            LOG_DEBUG << models::getCompanyIdbyId(1); });
    drogon::app().run();
    return 0;
}

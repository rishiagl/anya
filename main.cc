#include <drogon/drogon.h>
#include <iostream>
#include "database/database.hpp"

int main()
{
  drogon::app().loadConfigFile("../config.json");
  drogon::app().registerBeginningAdvice([]()
                                        {
                                            LOG_DEBUG << "Server started";
                                            try
                                            {
                                                auto dbClient = drogon::app().getDbClient("postgres");
                                                database::storeDBClient(dbClient);
                                            }
                                            catch(const std::exception& e)
                                            {
                                              std::cerr << e.what() << '\n';
                                            } 
                                        });
  drogon::app().run();
  return 0;
}

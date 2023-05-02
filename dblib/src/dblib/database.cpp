#include <dblib/database.hpp>
#include <drogon/orm/Exception.h>
#include <drogon/orm/SqlBinder.h>
#include <drogon/orm/Row.h>
#include <drogon/orm/Result.h>


drogon::orm::DbClientPtr pgclient;
void dblib::storeDBClient(drogon::orm::DbClientPtr dbclient) {
     pgclient = dbclient;
}

drogon::orm::DbClientPtr dblib::getDBClient(){
    return pgclient;
}

std::string dblib::getCompanyIdbyId(int id){
    std::string cid = "";
    std::cout << pgclient;
    pgclient->execSqlAsync("SELECT company_id FROM anya.company WHERE id=$1 ",
                            [](const drogon::orm::Result &result) {
                                // std::cout << result.size() << " rows selected!" << std::endl;
                                // int i = 0;
                                // for (auto row : result)
                                // {
                                //     std::cout << i++ << ": user name is " << row["user_name"].as<std::string>() << std::endl;
                                // }
                            },
                            [](const drogon::orm::DrogonDbException &e) {
                                std::cerr << "error:" << e.base().what() << std::endl;
                            },
                            id);
    // try {
    //     auto result = pgclient->execSqlSync("SELECT company_id FROM anya.company WHERE id=$1 ", id); // Block until we get the result or catch the exception;
    //     for (auto row : result) {
    //         cid = row["company_id"].as<std::string>();
    //     }
    //     std::cout << result.affectedRows() << " rows updated!" << std::endl;
    // }
    // catch (const drogon::orm::DrogonDbException &e) {
    // std::cerr << "error:" << e.base().what() << std::endl;
    // }
    return cid;
}


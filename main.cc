#include <drogon/drogon.h>
#include <iostream>
int main()
{
    // Set HTTP listener address and port
    // drogon::app().addListener("0.0.0.0", 1024);
    // std::cout.flush();
    // std::cout << "Entered"
    //           << "\n";
    drogon::app().loadConfigFile("../config.json");

    // Load config file
    // drogon::app().loadConfigFile("../config.json");
    // Run HTTP framework,the method will block in the internal event loop
    // std::cout << "Entered"
    //           << "\n";
    // auto clientPtr = drogon::app().getDbClient("postgres");
    // std::cout << "Entered"
    //           << "\n";
    // auto f = clientPtr->execSqlAsyncFuture("SELECT * FROM anya.company WHERE id=$1", 1);
    // std::cout << "Entered"
    //           << "\n";
    // try
    // {
    //     std::cout << "Entered"
    //               << "\n";
    //     auto result = f.get(); // Block until we get the result or catch the exception;
    //     std::cout << result.size() << " rows selected!"
    //               << "\n";
    //     int i = 0;
    //     std::cout << "Entered"
    //               << "\n";
    //     for (auto row : result)
    //     {
    //         std::cout << i++ << ": Shop id is " << row["shop_id"].as<std::string>() << "\n";
    //     }
    // }
    // catch (const drogon::orm::DrogonDbException &e)
    // {
    //     std::cerr << "error:" << e.base().what() << "\n";
    // }
    drogon::app().run();
    std::cout.flush();
    std::cout << "Entered"
              << "\n";
    auto clientPtr = drogon::app().getDbClient("postgres");
    std::cout << "Entered"
              << "\n";
    auto f = clientPtr->execSqlAsyncFuture("SELECT * FROM anya.company WHEREC id=$1", 1);
    std::cout << "Entered"
              << "\n";
    try
    {
        std::cout << "Entered"
                  << "\n";
        auto result = f.get(); // Block until we get the result or catch the exception;
        std::cout << result.size() << " rows selected!"
                  << "\n";
        int i = 0;
        std::cout << "Entered"
                  << "\n";
        for (auto row : result)
        {
            std::cout << i++ << ": Shop id is " << row["shop_id"].as<std::string>() << "\n";
        }
    }
    catch (const drogon::orm::DrogonDbException &e)
    {
        std::cerr << "error:" << e.base().what() << "\n";
    }
    return 0;
}

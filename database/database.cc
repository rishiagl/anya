#include <drogon/orm/DbClient.h>

int getDbClient() {
    auto dbClient=drogon::app().getDbClient("testDB");
}
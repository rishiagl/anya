add_library(
    dblib SHARED
    src/dblib/database.cpp
    src/dblib/database.hpp
)

target_include_directories(dblib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
cmake_minimum_required(VERSION 3.9)

project(test_sqlite)

# check_library_exists(sqlite3 sqlite3_open "" HAVE_SQLITE3)
message("HAVE_SQLITE3: " ${HAVE_SQLITE3})
find_library(SQLITE3_LIBRARY sqlite3)
message("SQLITE3_LIBRARY: " ${SQLITE3_LIBRARY})

    
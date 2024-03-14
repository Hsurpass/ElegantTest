cmake_minimum_required(VERSION 3.9)

project(test_leveldb)

find_library(LEVELDB_LIB NAMES leveldb)
find_path(LEVELDB_INCLUDE_PATH NAMES leveldb/db.h)

message("LEVELDB_LIBRARY: " ${LEVELDB_LIB})
message("LEVELDB_INCLUDE_PATH: " ${LEVELDB_INCLUDE_PATH})




    
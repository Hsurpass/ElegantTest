cmake_minimum_required(VERSION 3.1)

project(test_libevent)

find_package(Libevent REQUIRED)

message("Libevent_FOUND: " ${Libevent_FOUND})
message("LIBEVENT_INCLUDE_DIR: " ${LIBEVENT_INCLUDE_DIR})
message("LIBEVENT_INCLUDE_DIRS: " ${LIBEVENT_INCLUDE_DIRS})
message("LIBEVENT_LIBRARIES: " ${LIBEVENT_LIBRARIES})



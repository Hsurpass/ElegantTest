cmake_minimum_required(VERSION 3.20)

project(fastddsdemo)

find_package(fastcdr REQUIRED)
find_package(fastrtps REQUIRED)


message("fastcdr_VERSION: " ${fastcdr_VERSION})
message("fastrtps_VERSION: " ${fastrtps_VERSION})



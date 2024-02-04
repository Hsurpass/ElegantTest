cmake_minimum_required(VERSION 3.0)

project(demo)

find_package(Eigen3 REQUIRED)

message(${EIGEN3_VERSION_STRING})
message(${EIGEN3_VERSION_MAJOR})
message(${EIGEN3_VERSION_MINOR})
message(${EIGEN3_VERSION_PATCH})

add_executable(${PROJECT_NAME} demo.cpp)

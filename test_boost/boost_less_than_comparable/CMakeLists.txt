cmake_minimum_required (VERSION 2.8)

project(BOOSTless_than_comparable)

FIND_PACKAGE(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
message("CMAKE_INSTALL_PREFIX: " ${CMAKE_PREFIX_INSTALL})
message("CMAKE_BUILD_TYPE: " ${CMAKE_BUILD_TYPE})


aux_source_directory(. SRC)
add_executable(boost_less_than_comparable ${SRC})
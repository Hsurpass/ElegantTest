# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# ZERO_CHECK 目标将不会生成
# set(CMAKE_SUPPRESS_REGENERATION FALSE)

MESSAGE(STATUS "cmake BINARY dir: " ${CMAKE_BINARY_DIR})
MESSAGE(STATUS "hello BINARY dir: " ${Hello_BINARY_DIR})
MESSAGE(STATUS "project binary dir: " ${PROJECT_BINARY_DIR})
MESSAGE(STATUS "cmake source dir: " ${CMAKE_SOURCE_DIR})
MESSAGE(STATUS "hello source dir: " ${Hello_SOURCE_DIR})
MESSAGE(STATUS "project source dir: " ${PROJECT_SOURCE_DIR})
MESSAGE(STATUS "CMAKE_CURRENT_LIST_DIR: " ${CMAKE_CURRENT_LIST_DIR})

MESSAGE(STATUS "--------------------------------------")
# 设置项目名称
project (multiDirMultiFile_hello02)

MESSAGE(STATUS "cmake BINARY dir: " ${CMAKE_BINARY_DIR})
MESSAGE(STATUS "hello BINARY dir: " ${Hello_BINARY_DIR})
MESSAGE(STATUS "project binary dir: " ${PROJECT_BINARY_DIR})
MESSAGE(STATUS "cmake source dir: " ${CMAKE_SOURCE_DIR})
MESSAGE(STATUS "hello source dir: " ${Hello_SOURCE_DIR})
MESSAGE(STATUS "project source dir: " ${PROJECT_SOURCE_DIR})
MESSAGE(STATUS "CMAKE_CURRENT_LIST_DIR: " ${CMAKE_CURRENT_LIST_DIR})


INCLUDE_DIRECTORIES(include)

set(src main.cpp src/hello.cpp)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

# 指定生成目标
add_executable(hello ${src})


cmake_minimum_required(VERSION 3.15)
project(my_project)

set(CMAKE_CXX_STANDARD 17)

message("CMAKE_BINARY_DIR: " ${CMAKE_BINARY_DIR})

# 引入 Conan 生成的文件
# include(${CMAKE_BINARY_DIR}/build/Release/generators/conanbuildinfo.cmake)
# include(${CMAKE_BINARY_DIR}/build/Release/generators/conan_toolchain.cmake)
# conan_basic_setup()

# 添加可执行文件
add_executable(my_project src/main.cpp)

# 链接依赖库
find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)
target_link_libraries(my_project fmt::fmt spdlog::spdlog)

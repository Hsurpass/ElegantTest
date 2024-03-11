cmake_minimum_required(VERSION 3.20)

project(DDSHelloWorld)

if(NOT fastcdr_FOUND)
    find_package(fastcdr 2 REQUIRED)
endif()

if(NOT fastrtps_FOUND)
    find_package(fastrtps 2.12 REQUIRED)
endif()

message("fastcdr_VERSION: " ${fastcdr_VERSION})
message("fastrtps_VERSION: " ${fastrtps_VERSION})

# CMake加载一个模块，用于检查C++编译器的编译选项。
include(CheckCXXCompilerFlag)
# 检查当前使用的C++编译器是否是GNU或Clang。如果是这两个编译器之一，才会执行后续的代码。
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANG OR 
        CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    # 调用check_cxx_compiler_flag函数，检查编译器是否支持-std=c++11编译选项。如果编译器支持C++11标准，则SUPPORTS_CXX11变量会被设置为TRUE，否则为FALSE。
    check_cxx_compiler_flag(-std=c++11 SUPPORTS_CXX11)
    if(SUPPORTS_CXX11)
        add_compile_options(-std=c++11)
    else()
        message(FATAL_ERROR "Compiler doesn't support C++11")
    endif()
    
endif()

message(STATUS "Configuring HelloWorld publisher/subscriber example...")
file(GLOB DDS_HELLOWORLD_SOURCES_CXX "src/*.cxx")
# file(GLOB DDS_HELLOWORLD_SOURCES_CPP "*.cpp")

add_executable(publisher 
    src/publisher.cpp
    ${DDS_HELLOWORLD_SOURCES_CXX} 
    # ${DDS_HELLOWORLD_SOURCES_CPP}
)
target_link_libraries(publisher 
    fastrtps
    fastcdr
    # fastdds::optionparser
    # ssl
    # crypto
)

add_executable(subscriber 
    src/subscriber.cpp
    ${DDS_HELLOWORLD_SOURCES_CXX} 
    # ${DDS_HELLOWORLD_SOURCES_CPP}
)
target_link_libraries(subscriber 
    fastrtps
    fastcdr
    # fastdds::optionparser
    # ssl
    # crypto
)




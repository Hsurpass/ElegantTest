cmake_minimum_required(VERSION 3.5)

project(helloexample)
find_package(Boost)

execute_process(
    COMMAND /bin/bash -c "commonapi-core-generator-linux-x86_64 -sk ${CMAKE_CURRENT_SOURCE_DIR}/helloworld.fidl"
)
execute_process(
    COMMAND /bin/bash -c "commonapi-someip-generator-linux-x86_64 ${CMAKE_CURRENT_SOURCE_DIR}/helloworld.fdepl"
)

include_directories(
    /usr/local/include/CommonAPI-3.2
    src-gen
)

file(GLOB_RECURSE SRC_GEN "src-gen/*.cpp")
message("SRC_GEN: " ${SRC_GEN})

set(DEPEND_LIB
    vsomeip3
    pthread
    boost_thread
    boost_system
    boost_log
    CommonAPI 
    CommonAPI-SomeIP
)

add_executable(client
    commonapi_helloclient.cpp
    ${SRC_GEN}
)
target_link_libraries(client ${DEPEND_LIB})

add_executable(server
    commonapi_helloserver.cpp
    ${SRC_GEN}
)
target_link_libraries(server ${DEPEND_LIB})


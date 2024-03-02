cmake_minimum_required(VERSION 3.9)

project(echo)

find_package(OpenSSL)
message(STATUS ${OPENSSL_INCLUDE_DIR})    # /usr/local/include
message(STATUS ${OPENSSL_CRYPTO_LIBRARY}) # /usr/local/lib/libcrypto.so
message(STATUS ${OPENSSL_SSL_LIBRARY})    # /usr/local/lib/libssl.so

find_package(Protobuf)
include(FindThreads)
include(FindProtobuf)
execute_process(COMMAND bash -c "protoc -I. --cpp_out=${CMAKE_CURRENT_BINARY_DIR} echo.proto")
protobuf_generate_cpp(PROTO_SRC PROTO_HEADER echo.proto)  
message(STATUS ${PROTO_SRC})
message(STATUS ${PROTO_HEADER})
message(STATUS "PROTOBUF_INCLUDE_DIR: " ${PROTOBUF_INCLUDE_DIR})   # /usr/local/include
message(STATUS "PROTOBUF_LIBRARIES: " ${PROTOBUF_LIBRARIES})   # /usr/local/lib/libprotobuf.a

include_directories(${CMAKE_CURRENT_BINARY_DIR})

# find_package(Threads)
# include(FindThreads)
# message(STATUS "CMAKE_THREAD_LIBS_INIT: " ${CMAKE_THREAD_LIBS_INIT}) # none

find_package(Thrift)
message(STATUS "THRIFT_LIBRARIES: " ${THRIFT_INCLUDE_DIR})
message(STATUS "THRIFT_LIBRARIES: " ${THRIFT_LIBRARIES})
find_library(THRIFT_LIB NAMES thriftd) # debug版本要加d
message(STATUS "THRIFT_LIB: " ${THRIFT_LIB}) # /usr/local/lib/libthriftd.a

# find_package(Z)
# message(STATUS "Z: " ${Z_LIBRARIES}) #none

# find_package(LevelDb)
# message(STATUS "LEVELDB_LIBRARIES: " ${LEVELDB_LIBRARIES}) # none
# message(STATUS "LEVELDB_INCLUDE_DIR: " ${LEVELDB_INCLUDE_DIR}) # none
find_path(LEVELDB_INCLUDE_PATH NAMES leveldb/db.h)
find_library(LEVELDB_LIB NAMES leveldb)
message("LEVELDB_INCLUDE_PATH: " ${LEVELDB_INCLUDE_PATH}) # xxx/leveldb/install/include
message("LEVELDB_LIB: " ${LEVELDB_LIB}) # /usr/local/lib/libthriftd.a

FIND_PACKAGE(gflags)
message("GFLAGS_INCLUDE_DIR: " ${GFLAGS_INCLUDE_DIR}) # /usr/include
message("GFLAGS_LIBRARIES: " ${GFLAGS_LIBRARIES}) # gflags_shared
find_path(GFLAGS_INCLUDE_PATH gflags/gflags.h)
find_library(GFLAGS_LIBRARY NAMES gflags libgflags)
message("GFLAGS_INCLUDE_PATH: " ${GFLAGS_INCLUDE_PATH}) # /usr/include
message("GFLAGS_LIBRARY: " ${GFLAGS_LIBRARY}) # /usr/lib/x86_64-linux-gnu/libgflags.so

# find_package(brpc)
# message(STATUS "BRPC_INCLUDE_DIR: " ${BRPC_INCLUDE_DIR}) # none
# message(STATUS "BRPC_LIBRARIES: " ${BRPC_LIBRARIES}) # nonde
find_library(BRPC_LIB NAMES libbrpc.a brpc)
message(STATUS "BRPC_LIB: " ${BRPC_LIB}) # xxx/brpc/install/lib/libbrpc.a

# add_executable(server 
#     server.cpp 
#     ${PROTO_SRC}    
# )
# target_link_libraries(server 
#     ${GFLAGS_LIBRARIES}
#     ${BRPC_LIB}
#     ${PROTOBUF_LIBRARIES}
#     ${OPENSSL_CRYPTO_LIBRARY}
#     ${OPENSSL_SSL_LIBRARY}
#     ${LEVELDB_LIB}
#     dl
#     z
# )

add_executable(client 
    client.cpp 
    ${PROTO_SRC}    
)
target_link_libraries(client 
    ${GFLAGS_LIBRARIES}
    ${BRPC_LIB}
    ${PROTOBUF_LIBRARIES}
    ${OPENSSL_CRYPTO_LIBRARY}
    ${OPENSSL_SSL_LIBRARY}
    ${LEVELDB_LIB}
    dl
    z
)

    
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

project(DEMO)

set(exec "bash compile.sh")

if(WIN32)

set(exec "compile.bat")
MESSAGE(STATUS "CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")
set(CMAKE_MODULE_PATH "D:\\WorkSpace\\4openSourceCode\\ProtoBuf\\installvs2019")
MESSAGE(STATUS "CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")

endif()
message("exec: " ${exec})

FIND_PACKAGE(Protobuf)

MESSAGE(STATUS "Protobuf_FOUND:" ${Protobuf_FOUND})
MESSAGE(STATUS "Protobuf_VERSION:" ${Protobuf_VERSION})
message("Protobuf_INCLUDE_DIRS: " ${Protobuf_INCLUDE_DIRS})
message("Protobuf_LIBRARIES: " ${Protobuf_LIBRARIES})
message("Protobuf_PROTOC_LIBRARIES: " ${Protobuf_PROTOC_LIBRARIES})
message("Protobuf_LITE_LIBRARIES: " ${Protobuf_LITE_LIBRARIES})

EXEC_PROGRAM(${exec} ${CMAKE_SOURCE_DIR}/proto OUTPUT_VARIABLE output RETURN_VALUE rvalue)
message("OUTPUT_VARIABLE: " ${output})
message("RETURN_VALUE: " ${rvalue})

include_directories(
    ${Protobuf_INCLUDE_DIRS}
)
aux_source_directory(${CMAKE_SOURCE_DIR}/pbsrc PBSRC)
message("PBSRC:" ${PBSRC})
set(SRC main.cpp)

add_executable(demo ${SRC} ${PBSRC})
target_link_directories(demo ${Protobuf_LIBRARIES})




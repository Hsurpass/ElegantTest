CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# cmake 3.15及以后推荐用这个
# if(POLICY CMP0091)
#     message("POLICY CMP0091")
#     cmake_policy(SET CMP0091 NEW)
# endif()

project(DEMO)

set(exec "bash compile.sh")

if(WIN32)

set(exec "compile.bat")
MESSAGE(STATUS "CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")
# set(CMAKE_MODULE_PATH "D:\\WorkSpace\\4openSourceCode\\ProtoBuf\\installvs2019")
MESSAGE(STATUS "CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")

endif()
message("exec: " ${exec})

FIND_PACKAGE(Protobuf REQUIRED COMPONENTS protobuf)

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

#cmake 3.15之前用这个
if(WIN32)
message("CMAKE_CXX_FLAGS_RELEASE: " ${CMAKE_CXX_FLAGS_RELEASE})
message("CMAKE_CXX_FLAGS_DEBUG: " ${CMAKE_CXX_FLAGS_DEBUG})
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
message("CMAKE_CXX_FLAGS_RELEASE: " ${CMAKE_CXX_FLAGS_RELEASE})
message("CMAKE_CXX_FLAGS_DEBUG: " ${CMAKE_CXX_FLAGS_DEBUG})
endif(WIN32)

# cmake 3.15及以后推荐用这个
# reference: https://blog.csdn.net/Copperxcx/article/details/123084367
# if(WIN32)
#     message("MSVC_RUNTIME_LIBRARY")
#     set_property(TARGET demo PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
# endif()

target_link_libraries(demo ${Protobuf_LIBRARIES})




cmake_minimum_required (VERSION 2.8)

MESSAGE(STATUS "cmake BINARY dir: " ${CMAKE_BINARY_DIR})
MESSAGE(STATUS "hello BINARY dir: " ${Hello_BINARY_DIR})
MESSAGE(STATUS "project binary dir: " ${PROJECT_BINARY_DIR})
MESSAGE(STATUS "cmake source dir: " ${CMAKE_SOURCE_DIR})
MESSAGE(STATUS "hello source dir: " ${Hello_SOURCE_DIR})
MESSAGE(STATUS "project source dir: " ${PROJECT_SOURCE_DIR})

MESSAGE(STATUS "--------------------------------------")

MESSAGE(STATUS "cmake BINARY dir: " ${CMAKE_BINARY_DIR})
MESSAGE(STATUS "hello BINARY dir: " ${Hello_BINARY_DIR})
MESSAGE(STATUS "project binary dir: " ${PROJECT_BINARY_DIR})
MESSAGE(STATUS "cmake source dir: " ${CMAKE_SOURCE_DIR})
MESSAGE(STATUS "hello source dir: " ${Hello_SOURCE_DIR})
MESSAGE(STATUS "project source dir: " ${PROJECT_SOURCE_DIR})
MESSAGE(STATUS "CMAKE_INSTALL_PREFIX: " ${CMAKE_INSTALL_PREFIX})

MESSAGE(STATUS "CMAKE_CURRENT_SOURCE_DIR: " ${CMAKE_CURRENT_SOURCE_DIR})
MESSAGE(STATUS "CMAKE_CURRENT_BINARY_DIR: " ${CMAKE_CURRENT_BINARY_DIR})

MESSAGE(STATUS "CMAKE_COMPILER_IS_GNUCXX: " ${CMAKE_COMPILER_IS_GNUCXX})
MESSAGE(STATUS "CMAKE_COMPILER_IS_GNUCC: " ${CMAKE_COMPILER_IS_GNUCC})
MESSAGE(STATUS "CMAKE_COMPILER_IS_GNUG77: " ${CMAKE_COMPILER_IS_GNUG77})

MESSAGE(STATUS "CMAKE_C_FLAGS: " ${CMAKE_CXX_STANDARD})
MESSAGE(STATUS "CMAKE_C_COMPILER: " ${CMAKE_C_COMPILER})
MESSAGE(STATUS "CMAKE_CXX_FLAGS: " ${CMAKE_CXX_COMPILER})

MESSAGE(STATUS "CMAKE_C_FLAGS: " ${CMAKE_C_FLAGS})
MESSAGE(STATUS "CMAKE_CXX_FLAGS: " ${CMAKE_CXX_FLAGS})

MESSAGE(STATUS "EXECUTABLE_OUTPUT_PATH: " ${EXECUTABLE_OUTPUT_PATH})
MESSAGE(STATUS "LIBRARY_OUTPUT_PATH: " ${LIBRARY_OUTPUT_PATH})
MESSAGE(STATUS "CMAKE_MODULE_PATH:" ${CMAKE_MODULE_PATH})

MESSAGE(STATUS "CMAKE_SYSTEM_APPBUNDLE_PATH: " ${CMAKE_SYSTEM_APPBUNDLE_PATH})
MESSAGE(STATUS "CMAKE_SYSTEM_FRAMEWORK_PATH: " ${CMAKE_SYSTEM_FRAMEWORK_PATH})
MESSAGE(STATUS "CMAKE_SYSTEM_IGNORE_PATH: " ${CMAKE_SYSTEM_IGNORE_PATH})
MESSAGE(STATUS "CMAKE_SYSTEM_INCLUDE_PATH: " ${CMAKE_SYSTEM_INCLUDE_PATH})
MESSAGE(STATUS "CMAKE_SYSTEM_LIBRARY_PATH: " ${CMAKE_SYSTEM_LIBRARY_PATH})
MESSAGE(STATUS "CMAKE_SYSTEM_NAME: " ${CMAKE_SYSTEM_NAME})
MESSAGE(STATUS "CMAKE_SYSTEM_PREFIX_PATH: " ${CMAKE_SYSTEM_PREFIX_PATH})
MESSAGE(STATUS "CMAKE_SYSTEM_PROCESSOR: " ${CMAKE_SYSTEM_PROCESSOR})
MESSAGE(STATUS "CMAKE_SYSTEM_PROGRAM_PATH: " ${CMAKE_SYSTEM_PROGRAM_PATH})
MESSAGE(STATUS "CMAKE_SYSTEM_VERSION: " ${CMAKE_SYSTEM_VERSION})

MESSAGE(STATUS "CMAKE_BUILD_TYPE: " ${CMAKE_BUILD_TYPE})
MESSAGE(STATUS "CMAKE_BUILD_TYPE:  ${CMAKE_BUILD_TYPE}")

IF(CMAKE_COMPILER_IS_GNUCXX)

ENDIF(CMAKE_COMPILER_IS_GNUCXX)


AUX_SOURCE_DIRECTORY(. SRCLIST)
FOREACH(F ${SRCLIST})
    MESSAGE(STATUS ${F})
ENDFOREACH()

FOREACH(VAR RANGE 10)
    # MESSAGE(STATUS ${VAR})
ENDFOREACH()

FOREACH(VAR RANGE 5 15 3)
    MESSAGE(STATUS ${VAR})
ENDFOREACH()

MESSAGE(STATUS "PATH: $ENV{PATH}")
MESSAGE(STATUS "PATH: " $ENV{PATH})
MESSAGE(STATUS "USER: " $ENV{USER})

MESSAGE(STATUS "CMAKE_GENERATOR: " ${CMAKE_GENERATOR})

MESSAGE(STATUS "CMAKE_LIBRARY_OUTPUT_DIRECTORY: " ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
MESSAGE(STATUS "CMAKE_ARCHIVE_OUTPUT_DIRECTORY: " ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
MESSAGE(STATUS "CMAKE_RUNTIME_OUTPUT_DIRECTORY: " ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

MESSAGE(STATUS "WIN32: " ${WIN32})
MESSAGE(STATUS "WIN64: " ${WIN64})
MESSAGE(STATUS "LINUX: " ${LINUX})

IF(WIN32)
    MESSAGE("WIN32")
ELSEIF(CMAKE_GENERATOR STREQUAL "Unix Makefiles")
    MESSAGE("LINUX")
ENDIF()

IF(WIN32)
    MESSAGE(STATUS "WIN")
ELSEIF(WIN32)
    MESSAGE(STATUS "LINUX")
ENDIF(WIN32)

IF(WIN32)
    MESSAGE(STATUS "WIN")
ELSE(UNIX)
    MESSAGE(STATUS "UNIX")
ENDIF()


function(print x y z)
    message(STATUS "CALL print func:")
    message("x = ${x}")
    message("y = " ${y})
    message("z = " ${z})
    message("argc: ${ARGC},  argv0: ${ARGV0}, argv1: ${ARGV1}, argv2: ${ARGV2}, all: ${ARGV}")
    message("argc: ,argv0: ,argv1: , argv2: , all: " ${ARGC}, ${ARGV0}, ${ARGV1}, ${ARGV2}, ${ARGV})
endfunction(print x y z)

print(1 2 3)

EXECUTE_PROCESS(COMMAND ls OUTPUT_VARIABLE ls_output RESULT_VARIABLE return_output)
message(STATUS "ls_output: " ${ls_output})
message(STATUS "return_output: " ${return_output})

set(list1 1 2 3 4)
set(list2 5;6;7;8)
set(list3 "9;10;11;12")
message(${list1})
message(${list2})
message(${list3})
message("${list1}")
message("${list2}")
message("${list3}")

list(LENGTH list1 length)
message("length: ${length}")
list(GET list1 2 var)
message("var: " ${var})
MESSAGE("---------------------------")
list(APPEND list1 5)
list(LENGTH list1 length)
message("length: ${length}")
list(GET list1 2 var)
message("var: " ${var})

LIST(REVERSE list1)
message(${list1})
LIST(SORT list1)
message(${list1})



MESSAGE("--------------BOOST-----------------")
# set(BOOST_ROOT "D:\\WorkSpace\\4openSourceCode\\Boost\\winBoost176")
# SET(BOOST_INCLDUEDIR "D:\\WorkSpace\\4openSourceCode\\Boost\\winBoost176\\include\\boost-1_76")
message("BOOST_INCLUDEDIR:" ${BOOST_INCLDUEDIR})
# set(BOOST_LIBRARYDIR "D:\\WorkSpace\\4openSourceCode\\Boost\\winBoost176\\lib")
message("BOOST_LIBRARYDIR:" ${BOOST_LIBRARYDIR})

# module模式搜索
# set(CMAKE_MODULE_PATH "D:\\WorkSpace\\4openSourceCode\\Boost\\winBoost176Build\\cmake")
MESSAGE(STATUS "CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")


#config模式搜索顺序
#1. PACKAGE_ROOT
message(STATUS "BOOST_ROOT:" ${BOOST_ROOT})
message(STATUS "BOOSTROOT:" ${BOOSTROOT})
#2.cmake特定的缓存变量 CMAKE_PREFIX_PATH CMAKE_FRAMEWORK_PATH CMAKE_APPBUNDLE_PATH
MESSAGE(STATUS "CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")
MESSAGE(STATUS "CMAKE_FRAMEWORK_PATH: ${CMAKE_FRAMEWORK_PATH}")
MESSAGE(STATUS "CMAKE_APPBUNDLE_PATH: ${CMAKE_APPBUNDLE_PATH}")
#3.cmake特定的环境变量 packagename_DIR CMAKE_PREFIX_PATH CMAKE_FRAMEWORK_PATH CMAKE_APPBUNDLE_PATH
message(STATUS "Boost_DIR: " ${Boost_DIR}) 
#4.HINTS字段指定的路径
#5.系统环境变量PATH
#6.存储在CMake的"User Package Registry"(用户包注册表)中的路径。
#7.设定为当前系统定义的cmake变量 CMAKE_SYSTEM_PREFIX_PATH CMAKE_SYSTEM_FRAMEWORK_PATH CMAKE_SYSTEM_APPBUNDLE_PATH
MESSAGE(STATUS "CMAKE_SYSTEM_PREFIX_PATH: ${CMAKE_SYSTEM_PREFIX_PATH}")
MESSAGE(STATUS "CMAKE_SYSTEM_FRAMEWORK_PATH: ${CMAKE_SYSTEM_FRAMEWORK_PATH}")
MESSAGE(STATUS "CMAKE_SYSTEM_APPBUNDLE_PATH: ${CMAKE_SYSTEM_APPBUNDLE_PATH}")
#8.在cmake的"System Package Registry"(系统包注册表）中查找
#9.从PATHS字段指定的路径中查找


# find_package(Boost)
find_package(Boost COMPONENTS atomic thread)

message(STATUS "Boost_VERSION:" ${Boost_VERSION})
MESSAGE("Boost_VERSION_MACRO:" ${Boost_VERSION_MACRO})
MESSAGE("Boost_VERSION_STRING:" ${Boost_VERSION_STRING})
MESSAGE("Boost_LIB_VERSION:" ${Boost_LIB_VERSION})
MESSAGE("Boost_MAJOR_VERSION:" ${Boost_MAJOR_VERSION})
MESSAGE("Boost_MINOR_VERSION:" ${Boost_MINOR_VERSION})
MESSAGE("Boost_VERSION_PATCH:" ${Boost_VERSION_PATCH})
MESSAGE("Boost_VERSION_COUNT:" ${Boost_VERSION_COUNT})
MESSAGE("Boost_LIB_DIAGNOSTIC_DEFINITIONS :" ${Boost_LIB_DIAGNOSTIC_DEFINITIONS})

message(STATUS "Boost_FOUND:" ${Boost_FOUND})
message(STATUS "Boost_ATOMIC_FOUND:" ${Boost_ATOMIC_FOUND})
message(STATUS "Boost_THREAD_FOUND:" ${Boost_THREAD_FOUND})
message(STATUS "Boost_CHRONO_FOUND:" ${Boost_CHRONO_FOUND})
message(STATUS "Boost_ATOMIC_LIBRARY:" ${Boost_ATOMIC_LIBRARY})
message(STATUS "Boost_THREAD_LIBRARY:" ${Boost_THREAD_LIBRARY})


message(STATUS "Boost_INCLUDE_DIRS:" ${Boost_INCLUDE_DIRS})
message(STATUS "Boost_LIBRARY_DIRS:" ${Boost_LIBRARY_DIRS})
message(STATUS "Boost_LIBRARIES:" ${Boost_LIBRARIES})
message(STATUS "Boost_ATOMIC_LIBRARY:" ${Boost_ATOMIC_LIBRARY})
message(STATUS "Boost_THREAD_LIBRARY:" ${Boost_THREAD_LIBRARY})
message(STATUS "Boost_SYSTEM_LIBRARY:" ${Boost_SYSTEM_LIBRARY})
message(STATUS "Boost_LIBRARY_DIR_RELEASE:" ${Boost_LIBRARY_DIR_RELEASE})
message(STATUS "Boost_LIBRARY_DIR_DEBUG:" ${Boost_LIBRARY_DIR_DEBUG})

message("################BOOST cache 变量################")
message(STATUS "Boost_INCLUDE_DIR:" ${Boost_INCLUDE_DIR})    # cache变量
message(STATUS "Boost_LIBRARY_DIR_RELEASE:" ${Boost_LIBRARY_DIR_RELEASE})    # cache变量
message(STATUS "Boost_LIBRARY_DIR_DEBUG:" ${Boost_LIBRARY_DIR_DEBUG})    # cache变量
message(STATUS "Boost_ATOMIC_LIBRARY_DEBUG:" ${Boost_ATOMIC_LIBRARY_DEBUG})    # cache变量
message(STATUS "Boost_ATOMIC_LIBRARY_RELEASE:" ${Boost_ATOMIC_LIBRARY_RELEASE})    # cache变量




MESSAGE("---------------PROTOBUF-------------------")
# MESSAGE(STATUS "CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")
# list(APPEND CMAKE_PREFIX_PATH "D:\\WorkSpace\\4openSourceCode\\ProtoBuf\\installvs2019")
# MESSAGE(STATUS "CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")
MESSAGE(STATUS "CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")
# set(CMAKE_MODULE_PATH "D:\\WorkSpace\\4openSourceCode\\ProtoBuf\\installvs2019")
MESSAGE(STATUS "CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")


find_package(Protobuf)
MESSAGE(STATUS "Protobuf_FOUND:" ${Protobuf_FOUND})
MESSAGE(STATUS "Protobuf_VERSION:" ${Protobuf_VERSION})
message("Protobuf_INCLUDE_DIRS: " ${Protobuf_INCLUDE_DIRS})
message("Protobuf_LIBRARIES: " ${Protobuf_LIBRARIES})
message("Protobuf_PROTOC_LIBRARIES: " ${Protobuf_PROTOC_LIBRARIES})
message("Protobuf_LITE_LIBRARIES: " ${Protobuf_LITE_LIBRARIES})
# CACHE 变量
message(STATUS "Protobuf_INCLUDE_DIR: " ${Protobuf_INCLUDE_DIR})
message("Protobuf_LIBRARY: " ${Protobuf_LIBRARY})
message("Protobuf_PROTOC_LIBRARY" ${Protobuf_PROTOC_LIBRARY})
message("Protobuf_INCLUDE_DIR:" ${Protobuf_INCLUDE_DIR})
message("Protobuf_PROTOC_EXECUTABLE: " ${Protobuf_PROTOC_EXECUTABLE})
message("Protobuf_LIBRARY_DEBUG: " ${Protobuf_LIBRARY_DEBUG})
message("Protobuf_PROTOC_LIBRARY_DEBUG: " ${Protobuf_PROTOC_LIBRARY_DEBUG})
message("Protobuf_LITE_LIBRARY: " ${Protobuf_LITE_LIBRARY})
message("Protobuf_LITE_LIBRARY_DEBUG: " ${Protobuf_LITE_LIBRARY_DEBUG})

# EXEC_PROGRAM cmake3.0之后被废弃了 使用execute_process
EXEC_PROGRAM(
    "/bin/bash" 
    ARGS "-c" "echo Hello" 
    OUTPUT_VARIABLE OUT
    RETURN_VALUE RET
)
message("EXEC_PROGRAM Output val is: ${OUT}, return val: ${RET} ")

# EXECUTE_PROCESS
EXECUTE_PROCESS(
    # COMMAND "/bin/bash" "-c" "echo Hello" 
    COMMAND /bin/bash -c "echo Hello"
    OUTPUT_VARIABLE OUT
    RESULT_VARIABLE RET
)
message("EXECUTE_PROCESS Output val is: ${OUT}, return val: ${RET} ")

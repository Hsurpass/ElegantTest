# 查找头文件路径
find_path(Hello_INCLUDE_DIRS hello.h ${CMAKE_SOURCE_DIR}/include)
message("find path Hello_INCLUDE_DIRS: " ${Hello_INCLUDE_DIRS})
message("find path CMAKE_INCLUDE_PATH: " ${CMAKE_INCLUDE_PATH})

#查找库路径
# find_library(Hello_LIBRARIES Hello ${CMAKE_SOURCE_DIR}/lib/libHello.a)
find_library(Hello_LIBRARIES Hello ${CMAKE_SOURCE_DIR}/lib)
message("find_library Hello_LIBRARIES: " ${Hello_LIBRARIES})
message("find_library CMAKE_LIBRARY_PATH: " ${CMAKE_LIBRARY_PATH})

# 设置Hello_FOUND
if(Hello_INCLUDE_DIRS AND Hello_LIBRARIES)
    set(Hello_FOUND TRUE)
endif()

message("HELLO_FIND_QUIETLY: " ${HELLO_FIND_QUIETLY})
message("HELLO_FIND_REQUIRED: " ${HELLO_FIND_REQUIRED})
IF (HELLO_FOUND)
    IF (NOT HELLO_FIND_QUIETLY)
        MESSAGE(STATUS "Found Hello: ${HELLO_LIBRARY}")
    ENDIF (NOT HELLO_FIND_QUIETLY)
ELSE (HELLO_FOUND)
    IF (HELLO_FIND_REQUIRED)
        MESSAGE(FATAL_ERROR "Could not find hello library")
    ENDIF (HELLO_FIND_REQUIRED)
ENDIF (HELLO_FOUND)
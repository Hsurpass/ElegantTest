MESSAGE(STATUS "srcList: " ${srcList})

aux_source_directory(. subList)
message(STATUS "subList: ${subList}")

# find_path(filePath ${subList} .)
# message(STATUS "filePath: ${filePath}")

list(APPEND srcList ${CMAKE_CURRENT_SOURCE_DIR}/hello.cpp)
MESSAGE(STATUS "srcList: ${srcList}")

aux_source_directory(. SRC)
message(****************status************** ${SRC})
message(****************status************** ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
message(****************status************** ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
message(****************status************** ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_library(helloFunc SHARED ${SRC})
# add_library(helloFunc ${SRC})
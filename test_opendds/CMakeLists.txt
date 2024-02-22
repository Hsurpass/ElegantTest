cmake_minimum_required(VERSION 3.20)

project(messengerDemo)

# find_package(opendds REQUIRED)  #right
find_package(OpenDDS REQUIRED)
message("OPENDDS_VERSION: " ${OPENDDS_VERSION})
message("CMAKE_CURRENT_BINARY_DIR:" ${CMAKE_CURRENT_BINARY_DIR})


# IDL TypeSupport Library
add_library(messenger_idl)
opendds_target_sources(messenger_idl PUBLIC "Messenger.idl")
target_link_libraries(messenger_idl PUBLIC OpenDDS::Dcps)

get_target_property(GENERATED_DIRECTORY messenger_idl OPENDDS_GENERATED_DIRECTORY)
MESSAGE("GENERATED_DIRECTORY: " ${GENERATED_DIRECTORY})

file(GLOB idl_src_files "${GENERATED_DIRECTORY}/*.cpp")
message("idl_src_files: " ${idl_src_files})

# get_target_property(PASSED_IDL_INTERFACE_FILES messenger_idl OPENDDS_PASSED_IDL_INTERFACE_FILES)
# MESSAGE("PASSED_IDL_INTERFACE_FILES: " ${PASSED_IDL_INTERFACE_FILES})

# get_target_property(LANGUAGE_MAPPINGS messenger_idl OPENDDS_LANGUAGE_MAPPINGS)
# MESSAGE("LANGUAGE_MAPPINGS: " ${LANGUAGE_MAPPINGS})

# get_target_property(GENERATED_IDL_INTERFACE_FILES messenger_idl OPENDDS_GENERATED_IDL_INTERFACE_FILES)
# MESSAGE("GENERATED_IDL_INTERFACE_FILES: " ${GENERATED_IDL_INTERFACE_FILES})

# get_target_property(ALL_IDL_INTERFACE_FILES messenger_idl OPENDDS_ALL_IDL_INTERFACE_FILES)
# MESSAGE("ALL_IDL_INTERFACE_FILES: " ${ALL_IDL_INTERFACE_FILES})

get_target_property(GENERATED_HEADER_FILES messenger_idl OPENDDS_GENERATED_HEADER_FILES)
MESSAGE("GENERATED_HEADER_FILES: " ${GENERATED_HEADER_FILES})

# get_target_property(ALL_GENERATED_INTERFACE_FILES messenger_idl OPENDDS_ALL_GENERATED_INTERFACE_FILES)
# MESSAGE("ALL_GENERATED_INTERFACE_FILES: " ${ALL_GENERATED_INTERFACE_FILES})

# get_target_property(ALL_INTERFACE_FILES messenger_idl OPENDDS_ALL_INTERFACE_FILES)
# MESSAGE("ALL_INTERFACE_FILES: " ${ALL_INTERFACE_FILES})


set(opendds_libs
    OpenDDS::Dcps # Core OpenDDS Librarys
)

add_executable(publisher publisher.cpp ${idl_src_files})
target_link_libraries(publisher 
    ${opendds_libs}
)

add_executable(subscriber 
    subscriber.cpp
    dataReaderListenerImpl.cpp  
    ${idl_src_files})
target_link_libraries(subscriber 
    ${opendds_libs}
)
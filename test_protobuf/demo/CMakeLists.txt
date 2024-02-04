CMAKE_MINIMUM_REQUIRED(VERSION 3.15)

# cmake 3.15及以后推荐用这个
# if(POLICY CMP0091)
#     message("POLICY CMP0091")
#     cmake_policy(SET CMP0091 NEW)
# endif()

project(DEMO)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(exec "bash compile.sh")

if(WIN32)

set(exec "compile.bat")
MESSAGE(STATUS "CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")
# set(CMAKE_MODULE_PATH "D:\\WorkSpace\\4openSourceCode\\ProtoBuf\\installvs2019")
MESSAGE(STATUS "CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")

endif()
message("exec: " ${exec})

FIND_PACKAGE(Protobuf REQUIRED COMPONENTS protobuf)
#FIND_PACKAGE(Protobuf REQUIRED CONFIG COMPONENTS protobuf)

MESSAGE(STATUS "Protobuf_FOUND:" ${Protobuf_FOUND})
MESSAGE(STATUS "Protobuf_VERSION:" ${Protobuf_VERSION})
message("Protobuf_INCLUDE_DIRS: " ${Protobuf_INCLUDE_DIRS})
message("Protobuf_LIBRARIES: " ${Protobuf_LIBRARIES})
message("Protobuf_PROTOC_LIBRARIES: " ${Protobuf_PROTOC_LIBRARIES})
message("Protobuf_LITE_LIBRARIES: " ${Protobuf_LITE_LIBRARIES})

EXEC_PROGRAM(
    ${exec} ${CMAKE_SOURCE_DIR}/proto 
    OUTPUT_VARIABLE output 
    RETURN_VALUE rvalue
)
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

target_link_libraries(demo 
    pthread
    protobuf
    # protobuf-lite
    # ${Protobuf_LIBRARIES}
    # ${Protobuf_LITE_LIBRARIES}
    # utf8_range
    # utf8_validity
    # gmock

    # absl_bad_any_cast_impl
    # absl_bad_optional_access
    # absl_bad_variant_access
    # absl_base
    # absl_city
    # absl_civil_time
    # absl_cord
    # absl_cord_internal
    # absl_cordz_functions
    # absl_cordz_handle
    # absl_cordz_info
    # absl_cordz_sample_token
    # absl_crc32c
    # absl_crc_cord_state
    # absl_crc_cpu_detect
    # absl_crc_internal
    # absl_debugging_internal
    # absl_demangle_internal
    # absl_die_if_null
    # absl_examine_stack
    # absl_exponential_biased
    # absl_failure_signal_handler
    # absl_flags
    # absl_flags_commandlineflag
    # absl_flags_commandlineflag_internal
    # absl_flags_config
    # absl_flags_internal
    # absl_flags_marshalling
    # absl_flags_parse
    # absl_flags_private_handle_accessor
    # absl_flags_program_name
    # absl_flags_reflection
    # absl_flags_usage
    # absl_flags_usage_internal
    # absl_graphcycles_internal
    # absl_hash
    # absl_hashtablez_sampler
    # absl_int128
    # absl_leak_check
    # absl_log_entry
    # absl_log_flags
    # absl_log_globals
    # absl_log_initialize
    # absl_log_internal_check_op
    # absl_log_internal_conditions
    # absl_log_internal_format
    # absl_log_internal_globals
    # absl_log_internal_log_sink_set
    # absl_log_internal_message
    # absl_log_internal_nullguard
    # absl_log_internal_proto
    # absl_log_severity
    # absl_log_sink
    # absl_low_level_hash
    # absl_malloc_internal
    # absl_periodic_sampler
    # absl_random_distributions
    # absl_random_internal_distribution_test_util
    # absl_random_internal_platform
    # absl_random_internal_pool_urbg
    # absl_random_internal_randen
    # absl_random_internal_randen_hwaes
    # absl_random_internal_randen_hwaes_impl
    # absl_random_internal_randen_slow
    # absl_random_internal_seed_material
    # absl_random_seed_gen_exception
    # absl_random_seed_sequences
    # absl_raw_hash_set
    # absl_raw_logging_internal
    # absl_scoped_mock_log
    # absl_scoped_set_env
    # absl_spinlock_wait
    # absl_stacktrace
    # absl_status
    # absl_statusor
    # absl_str_format_internal
    # absl_strerror
    # absl_strings
    # absl_strings_internal
    # absl_symbolize
    # absl_synchronization
    # absl_throw_delegate
    # absl_time
    # absl_time_zone
)




# cmake -B build -DCMAKE_PREFIX_PATH=/mnt/d/WorkSpace/4openSourceCode/grpc/_install/
cmake_minimum_required(VERSION 3.1)

project(hello)

find_package(Protobuf REQUIRED )
MESSAGE(STATUS "Protobuf_FOUND:" ${Protobuf_FOUND})
MESSAGE(STATUS "Protobuf_VERSION:" ${Protobuf_VERSION})
message("Protobuf_INCLUDE_DIRS: " ${Protobuf_INCLUDE_DIRS})
message("Protobuf_LIBRARIES: " ${Protobuf_LIBRARIES})   # /usr/local/lib/libprotobuf.a
message("Protobuf_PROTOC_LIBRARIES: " ${Protobuf_PROTOC_LIBRARIES}) # /usr/local/lib/libprotoc.a
message("Protobuf_LITE_LIBRARIES: " ${Protobuf_LITE_LIBRARIES}) # /usr/local/lib/libprotobuf-lite.a
message("PROTOBUF_PROTOC: " ${Protobuf_PROTOC})
# message("protobuf::protoc: " ${protobuf::protoc})
message("Protobuf_PROTOC_EXECUTABLE: " ${Protobuf_PROTOC_EXECUTABLE})


find_package(gRPC REQUIRED )
MESSAGE("gRPC_FOUND: " ${gRPC_FOUND})
# MESSAGE("gRPC_FOUND: " ${gRPC_INCLUDE_DIRS})
# MESSAGE("gRPC_FOUND: " ${gRPC_LIBRARIES})
# message("_GRPC_GRPCPP: " ${_GRPC_GRPCPP})

# Proto file
get_filename_component(hw_proto "./helloworld.proto" ABSOLUTE)
get_filename_component(hw_proto_path "${hw_proto}" PATH)
message("hw_proto: " ${hw_proto})
message("hw_proto_path: " ${hw_proto_path})
message("CMAKE_CURRENT_SOURCE_DIR: " ${CMAKE_CURRENT_SOURCE_DIR})

# Generated sources
set(protodir ${CMAKE_CURRENT_SOURCE_DIR}/proto)
set(hw_proto_srcs "${protodir}/helloworld.pb.cc")
set(hw_proto_hdrs "${protodir}/helloworld.pb.h")
set(hw_grpc_srcs "${protodir}/helloworld.grpc.pb.cc")
set(hw_grpc_hdrs "${protodir}/helloworld.grpc.pb.h")

message("hw_proto_srcs: " ${hw_proto_srcs})
message("hw_proto_hdrs: " ${hw_proto_hdrs})

EXECUTE_PROCESS(
    COMMAND bash -c "mkdir proto"
    WORKING_DIRECTORY .
    OUTPUT_VARIABLE OUT
    RESULT_VARIABLE RET
)

add_custom_command(
    OUTPUT "${hw_proto_srcs}" "${hw_proto_hdrs}" "${hw_grpc_srcs}" "${hw_grpc_hdrs}"
    COMMAND ${Protobuf_PROTOC_EXECUTABLE} 
    ARGS --cpp_out "${protodir}" -I "${hw_proto_path}" 
        --grpc_out=${protodir} --plugin=protoc-gen-grpc=`which grpc_cpp_plugin`
        "${hw_proto}"
    DEPENDS "${hw_proto}"
)

# hw_grpc_proto
add_library(hw_grpc_proto
  ${hw_grpc_srcs}
  ${hw_grpc_hdrs}
  ${hw_proto_srcs}
  ${hw_proto_hdrs}
)
target_link_libraries(hw_grpc_proto
#   ${_REFLECTION}
#   ${_GRPC_GRPCPP}
    gRPC::grpc++_reflection
    gRPC::grpc++
    ${Protobuf_LIBRARIES}
)


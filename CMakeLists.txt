﻿cmake_minimum_required(VERSION 3.15)

project(updater_service LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROTO_DIR ${CMAKE_SOURCE_DIR}/proto)
set(PROTO_FILE ${PROTO_DIR}/updater-service.proto)

set(GENERATED_DIR ${CMAKE_SOURCE_DIR}/updater-service)

file(MAKE_DIRECTORY ${GENERATED_DIR})

find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)

set(PROTO_SRCS "${GENERATED_DIR}/updater-service.pb.cc")
set(PROTO_HDRS "${GENERATED_DIR}/updater-service.pb.h")
set(GRPC_SRCS "${GENERATED_DIR}/updater-service.grpc.pb.cc")
set(GRPC_HDRS "${GENERATED_DIR}/updater-service.grpc.pb.h")

add_custom_command(
    OUTPUT ${PROTO_SRCS} ${PROTO_HDRS} ${GRPC_SRCS} ${GRPC_HDRS}
    COMMAND ${Protobuf_PROTOC_EXECUTABLE}
    ARGS --grpc_out=${GENERATED_DIR}
         --cpp_out=${GENERATED_DIR}
         --plugin=protoc-gen-grpc=/opt/hostedtoolcache/grpc/1.51.1/x64/bin/grpc_cpp_plugin
         -I ${PROTO_DIR}
         ${PROTO_FILE}
    DEPENDS ${PROTO_FILE}
)

set(SOURCES
    updater-service/updater-service.cpp
    updater-service/main.cpp
    ${PROTO_SRCS}
    ${GRPC_SRCS}
)

add_executable(updater_service ${SOURCES})

target_include_directories(updater_service PRIVATE ${CMAKE_SOURCE_DIR}/updater-service)
target_link_libraries(updater_service PRIVATE gRPC::grpc++ protobuf::libprotobuf)

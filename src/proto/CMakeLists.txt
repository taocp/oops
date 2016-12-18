# XXX oops, ugly code

set(ProtobufIncludePath ${CMAKE_CURRENT_BINARY_DIR}
    CACHE INTERNAL "Path to generated protobuf files.")
set(PROTOBUF_INCLUDE_DIR ../../thirdparty/include/google/protobuf/)
set(PROTOBUF_LIBRARY ../../thirdparty/lib/)
set(PROTOBUF_PROTOC_EXECUTABLE ${CMAKE_CURRENT_BINARY_DIR}/../../../thirdparty/bin/protoc)

FIND_PACKAGE(Protobuf REQUIRED)
INCLUDE_DIRECTORIES(${PROTOBUF_INCLUDE_DIR})
PROTOBUF_GENERATE_CPP(PROTO_SRC PROTO_HEADER master.proto)
ADD_LIBRARY(proto ${PROTO_HEADER} ${PROTO_SRC})

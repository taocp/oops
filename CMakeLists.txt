cmake_minimum_required(VERSION 3.3.0)
project (oops)

include_directories(thirdparty/include thirdparty/boost_1_58_0 . src src/proto)

set(CMAKE_CXX_STANDARD 11)
set(OOPS_LINK_LIBS libsofa-pbrpc.a libgflags.a libprotobuf.a libsnappy.a)
link_directories(thirdparty/lib/)

# XXX
ADD_SUBDIRECTORY(src/proto src/proto)

file(GLOB common src/common/*.cc)
file(GLOB flag src/flags.cc)
file(GLOB rpc src/rpc/*.cc)
file(GLOB master src/master/*.cc)
file(GLOB cli src/client/*.cc)

include_directories(${ProtobufIncludePath})

add_executable(oopsmaster ${flag} ${common} ${master})
target_link_libraries(oopsmaster ${OOPS_LINK_LIBS} proto pthread z)

add_executable(oopscli ${flag} ${rpc} ${common} ${cli})
target_link_libraries(oopscli ${OOPS_LINK_LIBS} proto pthread z)

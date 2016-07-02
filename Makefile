include ./depends.mk

CXX=g++

INCPATH=-I. -Isrc/proto/ -I$(SOFA_PBRPC_DIR)/include -I$(GFLAGS_DIR)/include -I$(PROTOBUF_DIR)/include \
				-I$(SNAPPY_DIR)/include -I$(ZLIB_DIR)/include
CXXFLAGS += -g -pipe -W -Wall -fPIC -D_GNU_SOURCE -D__STDC_LIMIT_MACROS $(INCPATH)
LIBRARY=$(SOFA_PBRPC_DIR)/lib/libsofa-pbrpc.a $(GFLAGS_DIR)/lib/libgflags.a $(PROTOBUF_DIR)/lib/libprotobuf.a $(SNAPPY_DIR)/lib/libsnappy.a
LDFLAGS += -lpthread -lz

PROTO_FILES := $(wildcard src/proto/*.proto)
PROTO_OUT_CC := $(PROTO_FILES:.proto=.pb.cc)
PROTO_OUT_H := $(PROTO_FILES:.proto=.pb.h)

PROTO_SRC := $(filter-out %.pb.cc, $(wildcard src/proto/*.cc)) $(PROTO_OUT_CC)
PROTO_OBJ := $(PROTO_SRC:.cc=.o)

%.pb.o: %.pb.cc
		$(CXX) $(CXXFLAGS) -c $< -o $@
%.pb.cc: %.proto
		$(PROTOBUF_DIR)/bin/protoc $(PROTO_OPTIONS) --cpp_out=. $<

%.o: %.cc $(PROTO_OBJ)
		$(CXX) $(CXXFLAGS) -c $< -o $@

master: $(PROTO_OBJ) src/flags.o src/master/master.o
		$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBRARY) $(LDFLAGS)

client: $(PROTO_OBJ) src/flags.o src/client/client.o
		$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBRARY) $(LDFLAGS)

clean:
	rm src/master/*.o src/client/*.o src/worker/*.o src/proto/*.pb.* master client

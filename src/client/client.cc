#include <iostream>

#include <gflags/gflags.h>
#include <sofa/pbrpc/pbrpc.h>

#include "master.pb.h"

DECLARE_string(taocipian_master_hostname);
DECLARE_string(taocipian_master_port);

// Using global RpcClient object can help share resources such as threads and buffers.
sofa::pbrpc::RpcClient g_rpc_client;

int main(int argc, char* argv[])
{
    ::google::ParseCommandLineFlags(&argc, &argv, true);

    // Define an rpc channel.
    sofa::pbrpc::RpcChannelOptions channel_options;
    sofa::pbrpc::RpcChannel rpc_channel(&g_rpc_client, FLAGS_taocipian_master_hostname + ":" + FLAGS_taocipian_master_port, channel_options);

    // Prepare parameters.
    sofa::pbrpc::RpcController* cntl = new sofa::pbrpc::RpcController();
    cntl->SetTimeout(10000);
    taocipian::sample::EchoRequest* request =
        new taocipian::sample::EchoRequest();
    request->set_message("Hello from taocipian");
    taocipian::sample::EchoResponse* response =
        new taocipian::sample::EchoResponse();

    // Sync call.
    taocipian::sample::MasterServer_Stub* stub =
        new taocipian::sample::MasterServer_Stub(&rpc_channel);
    stub->Echo(cntl, request, response, NULL);

    // Check if failed.
    if (cntl->Failed()) {
        std::cerr << "rpc error:" << cntl->ErrorText() << std::endl;
    } else {
        std::cout << "rpc done:" << response->message() << std::endl;
    }

    // Destroy objects.
    delete cntl;
    delete request;
    delete response;
    delete stub;

    return 0;
}

#include <iostream>

#include <gflags/gflags.h>
#include <sofa/pbrpc/pbrpc.h>

#include "master.pb.h"
#include "rpc/master_client.h"

DECLARE_string(taocipian_master_hostname);
DECLARE_string(taocipian_master_port);

int main(int argc, char* argv[])
{
    ::google::ParseCommandLineFlags(&argc, &argv, true);

    taocipian::master::MasterClient master_client(FLAGS_taocipian_master_hostname + ":" + FLAGS_taocipian_master_port);
    taocipian::master::EchoRequest* request =
        new taocipian::master::EchoRequest();
    request->set_message("Hello from taocipian");
    taocipian::master::EchoResponse* response =
        new taocipian::master::EchoResponse();
    if (master_client.Echo(request, response, NULL)) {
        std::cout << response->message() << std::endl;
    }

    return 0;
}

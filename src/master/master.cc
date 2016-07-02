#include <signal.h>
#include <unistd.h>

#include <iostream>

#include <gflags/gflags.h>
#include <sofa/pbrpc/pbrpc.h>

#include "master.pb.h"

DECLARE_string(taocipian_master_hostname);
DECLARE_string(taocipian_master_port);

namespace taocipian {
namespace master {

class MasterImpl : public taocipian::sample::MasterServer
{
public:
    MasterImpl() {}
    virtual ~MasterImpl() {}

private:
    virtual void Echo(google::protobuf::RpcController* controller,
                      const taocipian::sample::EchoRequest* request,
                      taocipian::sample::EchoResponse* response,
                      google::protobuf::Closure* done) {
        sofa::pbrpc::RpcController* cntl = static_cast<sofa::pbrpc::RpcController*>(controller);
        // XXX handles request in master-thread-pool instead of rpc-thread-pool
        std::cout << "Echo for " << cntl->RemoteAddress() << std::endl;
        response->set_message("echo message: " + request->message());
        done->Run();
    }

    // ThreadPool* pool_;
};

} // namespace master
} // namespace taocipian

bool thread_init_func()
{
    return true;
}

void thread_dest_func()
{
}

int main(int argc, char* argv[])
{
    ::google::ParseCommandLineFlags(&argc, &argv, true);

    // Define an rpc server.
    sofa::pbrpc::RpcServerOptions options;
    options.work_thread_init_func = sofa::pbrpc::NewPermanentExtClosure(&thread_init_func);
    options.work_thread_dest_func = sofa::pbrpc::NewPermanentExtClosure(&thread_dest_func);
    sofa::pbrpc::RpcServer rpc_server(options);

    // Start rpc server.
    if (!rpc_server.Start(FLAGS_taocipian_master_hostname + ":" + FLAGS_taocipian_master_port)) {
        std::cerr << "start server failed" << std::endl;
        return 1;
    }

    // Register service.
    taocipian::sample::MasterServer* master_service = new taocipian::master::MasterImpl();
    if (!rpc_server.RegisterService(master_service)) {
        std::cerr << "export service failed" << std::endl;
        return 2;
    }

    // Wait signal.
    rpc_server.Run();

    // Stop rpc server.
    rpc_server.Stop();

    // Delete closures.
    // Attention: should delete the closures after server stopped, or may be crash.
    delete options.work_thread_init_func;
    delete options.work_thread_dest_func;

    return 0;
}

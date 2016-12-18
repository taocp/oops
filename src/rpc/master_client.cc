#include <string>

#include <gflags/gflags.h>

#include "rpc/master_client.h"

namespace taocipian {
namespace master {

MasterClient::MasterClient(const std::string& server_addr,
                           int32_t rpc_timeout)
    : RpcClient<MasterServer::Stub>(server_addr),
      rpc_timeout_(rpc_timeout) {}

MasterClient::~MasterClient() {}

bool MasterClient::Echo(const EchoRequest* request,
                        EchoResponse* response,
                        Closure<void, EchoRequest*, EchoResponse*, bool, int>* done) {
    return SendMessageWithRetry(&MasterServer::Stub::Echo,
                                request, response, done, "Echo", rpc_timeout_);
}

} // namespace master
} // namespace taocipian

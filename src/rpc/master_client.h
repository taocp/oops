// Copyright (c) 2015, Baidu.com, Inc. All Rights Reserved
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef TAOCIPIAN_MASTER_MASTER_CLIENT_H_
#define TAOCIPIAN_MASTER_MASTER_CLIENT_H_

#include <string>

#include "common/base/closure.h"

#include "master.pb.h"
#include "rpc/rpc_client.h"

DECLARE_int32(taocipian_rpc_timeout_period);

namespace taocipian {
namespace master {

class MasterClient : public RpcClient<MasterServer::Stub> {
public:
    MasterClient(const std::string& server_addr = "",
                 int32_t rpc_timeout = FLAGS_taocipian_rpc_timeout_period);
    virtual ~MasterClient();

    virtual bool Echo(const EchoRequest* request,
                      EchoResponse* response,
                      Closure<void, EchoRequest*, EchoResponse*, bool, int>* done);


private:
    int32_t rpc_timeout_;
};

} // namespace master
} // namespace taocipian

#endif // TAOCIPIAN_MASTER_MASTER_CLIENT_H_

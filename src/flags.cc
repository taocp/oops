#include <gflags/gflags.h>

DEFINE_int32(taocipian_rpc_timeout_period, 60000, "in ms");
DEFINE_string(taocipian_master_hostname, "", "master hostname");
DEFINE_string(taocipian_master_port, "", "master port");
DEFINE_int32(taocipian_master_task_pool_thread_num, 10, "");

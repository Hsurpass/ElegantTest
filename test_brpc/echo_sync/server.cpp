#include <butil/endpoint.h>
#include <functional>
#include <gflags/gflags.h>
#include <butil/logging.h>
#include <brpc/server.h>
#include <json2pb/pb_to_json.h>
#include <iostream>
#include <string>
#include "echo.pb.h"

using namespace std;

DEFINE_bool(echo_attachment, true, "Echo attachment as well");
DEFINE_int32(port, 8000, "TCP Port of this server");
DEFINE_string(listen_addr,
              "",
              "Server listen address, may be IPV4/IPV6/UDS."
              " If this is set, the flag port will be ignored");

/*
如果一个连接在ServerOptions.idle_timeout_sec对应的时间内没有读取或写出数据，则被视为”闲置”而被server主动关闭。默认值为-1，代表不开启。
打开-log_idle_connection_close后关闭前会打印一条日志。
Name	                    Value	Description	                                    Defined At
log_idle_connection_close	false	Print log when an idle connection is closed	    src/brpc/socket.cpp
*/
DEFINE_int32(idle_timeout_s,
             -1,
             "Connection will be closed if there is no "
             "read/write operations during the last `idle_timeout_s'");

namespace example
{
class EchoServiceImpl : public EchoService
{
public:
    EchoServiceImpl()
    {}
    virtual ~EchoServiceImpl()
    {}

    void Echo(google::protobuf::RpcController* cntl_base,
              const EchoRequest* request,
              EchoResponse* response,
              google::protobuf::Closure* done) override

    {
        // 放在第一行，保证函数结束或中途退出时，确保done->Run()能被调用
        brpc::ClosureGuard done_guard(done);

        brpc::Controller* cntl = static_cast<brpc::Controller*>(cntl_base);

        // set a callback function which is called after response is sent
        // and before cntl/req/res is destructed.
        cntl->set_after_rpc_resp_fn(std::bind(&EchoServiceImpl::CallAfterRpc,
                                              std::placeholders::_1,
                                              std::placeholders::_2,
                                              std::placeholders::_3));

        LOG(INFO) << "Received request[log_id=" << cntl->log_id() << "] from " << cntl->remote_side() << " to "
                  << cntl->local_side() << ": " << request->message() << " (attached=" << cntl->request_attachment()
                  << ")";

        // set response
        response->set_message(request->message());

        if (FLAGS_echo_attachment) {
            cntl->response_attachment().append(cntl->request_attachment());
        }
    }

    static void CallAfterRpc(brpc::Controller* cntl,
                             const google::protobuf::Message* req,
                             const google::protobuf::Message* res)
    {
        std::string req_str;
        std::string res_str;
        json2pb::ProtoMessageToJson(*req, &req_str, NULL);
        json2pb::ProtoMessageToJson(*res, &res_str, NULL);
        LOG(INFO) << "req: " << req_str << ", res: " << res_str << endl;
    }
};

} // namespace example

int main(int argc, char* argv[])
{
    // 解析命令行参数
    // GFLAGS_NS::ParseCommandLineFlags(argc, &argv, true);
    GFLAGS_NAMESPACE::ParseCommandLineFlags(&argc, &argv, true);
    // create server
    brpc::Server server;

    // INIT SERVICE INSTANCE
    example::EchoServiceImpl echo_service_impl;

    // add service
    // SERVER_OWNS_SERVICE: 表示server在析构时会一并删除service
    // SERVER_DOESNT_OWN_SERVICE: 表示不删除service, 因为echo_service_impl放在栈上。
    if (server.AddService(&echo_service_impl, brpc::SERVER_DOESNT_OWN_SERVICE) != 0) {
        LOG(ERROR) << "Fail to add service!";
        return -1;
    }

    butil::EndPoint ep;
    if (!FLAGS_listen_addr.empty()) {
        if (butil::str2endpoint(FLAGS_listen_addr.c_str(), &ep) < 0) {
            LOG(ERROR) << "Invalid listen address:" << FLAGS_listen_addr;
            return -1;
        }
    }
    else {
        ep = butil::EndPoint(butil::IP_ANY, FLAGS_port);
    }

    // start server
    brpc::ServerOptions options;
    options.idle_timeout_sec = FLAGS_idle_timeout_s;
    if (server.Start(ep, &options) != 0) {
        LOG(ERROR) << "Fail to start EchoServer";
        return -1;
    }
    else {
        LOG(INFO) << "start server " << ep;
    }

    // 等待服务结束并退出
    server.RunUntilAskedToQuit();

    return 0;
}
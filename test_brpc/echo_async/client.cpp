#include <brpc/controller.h>
#include <gflags/gflags.h>
#include <butil/logging.h>
#include <butil/time.h>
#include <brpc/channel.h>
#include "echo.pb.h"
#include <gflags/gflags_declare.h>
#include <iostream>
#include <memory>
#include <unistd.h>

using namespace std;

DEFINE_string(attachment, "async你好brpc", "Carry this along with requests");
DEFINE_string(protocol, "baidu_std", "Protocol type. Defined in src/brpc/options.proto");
DEFINE_string(connection_type, "", "Connection type. Available values: single, pooled, short");
DEFINE_string(server, "0.0.0.0:8000", "IP Address of server");
DEFINE_string(load_balancer, "", "The algorithm for load balancing");
DEFINE_int32(timeout_ms, 100, "RPC timeout in milliseconds");
DEFINE_int32(max_retry, 3, "Max retries(not including the first RPC)");
DEFINE_int32(interval_ms, 1000, "Milliseconds between consecutive requests");

void HandleEchoResponse(brpc::Controller* cntl, example::EchoResponse* response)
{
    std::unique_ptr<brpc::Controller> cntl_guard(cntl);
    std::unique_ptr<example::EchoResponse> response_guard(response);

    if (cntl->Failed()) {
        LOG(ERROR) << "Fail to send EchoReqquest" << cntl->ErrorText();
        return;
    }
    LOG(INFO) << "receive response from " << cntl->remote_side() << ": " << response->message()
              << " (attached=" << cntl->response_attachment() << ")"
              << "latency=" << cntl->latency_us() << "us";
}

int main(int argc, char* argv[])
{
    GFLAGS_NAMESPACE::ParseCommandLineFlags(&argc, &argv, true);

        // channel 是线程安全的。
    brpc::Channel channel;

    // init the channel, NULL means using default options
    brpc::ChannelOptions options;
    options.protocol = FLAGS_protocol;
    options.connection_type = FLAGS_connection_type;
    options.timeout_ms = FLAGS_timeout_ms;
    options.max_retry = FLAGS_max_retry;
    // channel.Init()不是线程安全的
    if (channel.Init(FLAGS_server.c_str(), FLAGS_load_balancer.c_str(), &options) != 0) {
        LOG(ERROR) << "Fail to initialize channel";
        return -1;
    }

    // create stub
    example::EchoService_Stub stub(&channel);

    int log_id = 0;
    while (!brpc::IsAskedToQuit()) {
        //receive response async
        // 因为是异步接收消息，所以在收到消息之前，要保证定义的变量一直有效，不能是栈变量
        example::EchoResponse* response = new example::EchoResponse();
        brpc::Controller* cntl = new brpc::Controller();

        example::EchoRequest request;
        request.set_message("hello world");
        cntl->set_log_id(log_id++);
        // attach 直接通过网络传输，而不通过protobuf序列化
        cntl->request_attachment().append(FLAGS_attachment);

        // done is not NULL, set async callback
        ::google::protobuf::Closure* done = brpc::NewCallback(&HandleEchoResponse, cntl, response);
        stub.Echo(cntl, &request, response, done);
        // if (!cntl->Failed()) {
        //     LOG(INFO) << "Received response from " << cntl->remote_side() << " to " << cntl->local_side() << ": "
        //               << response->message() << " (attached=" << cntl->response_attachment() << ")"
        //               << " latency=" << cntl->latency_us() << "us";
        // }
        // else {
        //     LOG(WARNING) << cntl.ErrorText();
        // }
        usleep(FLAGS_interval_ms * 1000);
    }

    LOG(INFO) << "EchoClient is going to quit";
    return 0;
}
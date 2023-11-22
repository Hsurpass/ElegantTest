#include <cstdint>
#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>
#include <sstream>
#include <string>

#include <thread>
#include <thrift/TToString.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/server/TThreadedServer.h>
#include <thrift/server/TThreadPoolServer.h>
#include <thrift/server/TNonblockingServer.h>

#include <thrift/protocol/TProtocol.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/protocol/TCompactProtocol.h>

#include <thrift/transport/TBufferTransports.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TServerTransport.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransport.h>
#include <thrift/transport/TNonblockingServerSocket.h>

#include "gen-cpp/tutorial_types.h"
#include "gen-cpp/shared_types.h"
#include "gen-cpp/Calculator.h"

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::concurrency;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;

class CalculatorHandler : public tutorial::CalculatorIf
{
public:
    CalculatorHandler() = default;

    void ping(std::string& _return) override
    {
        cout << "ping" << endl;
        _return = "pong";
    }

    int32_t add(const int32_t num1, const int32_t num2) override
    {
        cout << "add(" << num1 << ", " << num2 << ")" << endl;
        return num1 + num2;
    }

    int32_t calculate(const int32_t logid, const tutorial::Work& w) override
    {
        cout << "calculate(" << logid << ", " << w << ")" << endl;
        int32_t ret;
        switch (w.op) {
        case tutorial::Operation::ADD:
            ret = w.num1 + w.num2;
            break;
        case tutorial::Operation::SUBTRACT:
            ret = w.num1 - w.num2;
            break;
        case tutorial::Operation::MULTIPLY:
            ret = w.num1 * w.num2;
            break;
        case tutorial::Operation::DIVIDE:
            if (w.num2 == 0) {
                tutorial::InvalidOperation iop;
                iop.whatOp = w.op;
                iop.why = "cannot divide by 0";
                throw iop;
            }
            break;
        default:
            tutorial::InvalidOperation iop;
            iop.whatOp = w.op;
            iop.why = "Invalid Operation";
            throw iop;
        }

        shared::SharedStruct ss;
        ss.key = logid;
        ss.value = apache::thrift::to_string(ret);
        log[logid] = ss;

        return ret;
    }

    void getStruct(shared::SharedStruct& _return, const int32_t key) override
    {
        cout << "getStruct(" << key << ")" << endl;
        _return = log[key];
    }

    void zip() override
    {
        cout << "zip()" << endl;
    }


private:
    std::map<int32_t, shared::SharedStruct> log;
};

class CalculatorHandlerFactory : public tutorial::CalculatorIfFactory
{
public:
    ~CalculatorHandlerFactory() override = default;

    // 使用工厂模式可以获取对端的连接信息
    tutorial::CalculatorIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) override
    {
        std::shared_ptr<transport::TSocket> sock = std::dynamic_pointer_cast<TSocket>(connInfo.transport);
        cout << "Incoming connection\n";
        cout << "\tSocketInfo: " << sock->getSocketInfo() << "\n";
        cout << "\tPeerHost: " << sock->getPeerHost() << "\n";
        cout << "\tPeerAddress: " << sock->getPeerAddress() << "\n";
        cout << "\tPeerPort: " << sock->getPeerPort() << "\n";
        cout << "\tthread id: " << std::this_thread::get_id() << "\n";

        return new CalculatorHandler;
    }
    void releaseHandler(::shared::SharedServiceIf* handler) override
    {
        delete handler;
    }
};

void test_TThreadedServer()
{
    std::shared_ptr<CalculatorHandler> calHandler = std::make_shared<CalculatorHandler>();
    std::shared_ptr<tutorial::CalculatorProcessor> calProcessor =
        std::make_shared<tutorial::CalculatorProcessor>(calHandler);
    std::shared_ptr<transport::TServerTransport> transport = std::make_shared<transport::TServerSocket>(9090);
    std::shared_ptr<transport::TTransportFactory> buffer = std::make_shared<transport::TBufferedTransportFactory>();
    shared_ptr<protocol::TProtocolFactory> protocol = std::make_shared<protocol::TBinaryProtocolFactory>();

    // apache::thrift::server::TThreadedServer server(calProcessor, transport, buffer, protocol);

    std::shared_ptr<CalculatorHandlerFactory> calHandlerFac = std::make_shared<CalculatorHandlerFactory>();
    shared_ptr<apache::thrift::TProcessorFactory> processorFactory =
        std::make_shared<tutorial::CalculatorProcessorFactory>(calHandlerFac);
    server::TThreadedServer server(processorFactory, transport, buffer, protocol);

    cout << "Starting the server..." << endl;
    server.serve();
    cout << "Done." << endl;
}

void test_simpleServer()
{
     // This server only allows one connection at a time, but spawns no threads
    TSimpleServer server(std::make_shared<tutorial::CalculatorProcessor>(std::make_shared<CalculatorHandler>()),
                         std::make_shared<TServerSocket>(9090),
                         std::make_shared<TBufferedTransportFactory>(),
                         std::make_shared<TBinaryProtocolFactory>());

    cout << "Starting the server..." << endl;
    server.serve();
    cout << "Done." << endl;
}

void test_TThreadPoolServer()
{
    const int workerCount = 4;
    std::shared_ptr<ThreadManager> threadManager = ThreadManager::newSimpleThreadManager(workerCount);
    threadManager->threadFactory(std::make_shared<ThreadFactory>());
    threadManager->start();

    // This server allows "workerCount" connection at a time, and reuses threads
    TThreadPoolServer server(
        std::make_shared<tutorial::CalculatorProcessorFactory>(std::make_shared<CalculatorHandlerFactory>()),
        std::make_shared<TServerSocket>(9090),
        std::make_shared<TBufferedTransportFactory>(),
        std::make_shared<TBinaryProtocolFactory>(),
        threadManager);

    cout << "Starting the server..." << endl;
    server.serve();
    cout << "Done." << endl;
}

void test_TNonblockingServer()
{

    std::shared_ptr<CalculatorHandlerFactory> calHandlerFac = std::make_shared<CalculatorHandlerFactory>();
    shared_ptr<apache::thrift::TProcessorFactory> processorFactory =
        std::make_shared<tutorial::CalculatorProcessorFactory>(calHandlerFac);

    std::shared_ptr<apache::thrift::transport::TNonblockingServerTransport> nonTransport =
        std::make_shared<apache::thrift::transport::TNonblockingServerSocket>(9090);

    shared_ptr<protocol::TProtocolFactory> protocolFac = std::make_shared<protocol::TCompactProtocolFactory>();
    std::shared_ptr<transport::TTransportFactory> buffer = std::make_shared<transport::TFramedTransportFactory>();

    // server::TNonblockingServer server(processorFactory,nonTransport);

    const int workerCount = 4;
    std::shared_ptr<ThreadManager> threadManager = ThreadManager::newSimpleThreadManager(workerCount);
    threadManager->threadFactory(std::make_shared<ThreadFactory>());
    threadManager->start();
    server::TNonblockingServer server(processorFactory, protocolFac, nonTransport, threadManager);

    // server::TNonblockingServer server(processorFactory, buffer, buffer, protocolFac, protocolFac, nonTransport); //error

    cout << "Starting the server, main thread id: " << std::this_thread::get_id() << endl;
    server.serve();
    cout << "Done." << endl;
}

int main()
{
    // test_TThreadedServer();
    // test_simpleServer();
    // test_TThreadPoolServer();
    test_TNonblockingServer();

    return 0;
}
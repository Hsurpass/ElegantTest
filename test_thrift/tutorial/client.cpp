#include <cstdint>
#include <iostream>
#include <memory>
#include <thrift/Thrift.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/protocol/TCompactProtocol.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransport.h>
#include <thrift/transport/TTransportUtils.h>

#include "gen-cpp/Calculator.h"
#include "gen-cpp/shared_types.h"
#include "gen-cpp/tutorial_types.h"

// #include "Calculator.h"
// #include "shared_types.h"
// #include "tutorial_types.h"

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

void test_client()
{
    std::shared_ptr<transport::TTransport> socket(new transport::TSocket("localhost", 9090));
    // std::shared_ptr<transport::TTransport> transport(new transport::TBufferedTransport(socket));
    std::shared_ptr<transport::TTransport> transport(new transport::TFramedTransport(socket));
    // std::shared_ptr<protocol::TProtocol> protocol(new TBinaryProtocol(transport));
    std::shared_ptr<protocol::TProtocol> protocol(new TCompactProtocol(transport));

    tutorial::CalculatorClient client(protocol);

    try {
        transport->open();
        std::string ret;
        client.ping(ret);
        cout << ret << endl;

        cout << "1+1 = " << client.add(1, 1) << endl;

        tutorial::Work work;
        work.op = tutorial::Operation::DIVIDE;
        work.num1 = 1;
        work.num2 = 0;

        try {
            client.calculate(1, work);
            cout << "Whoa? We can divide by zero!" << endl;
        }
        catch (tutorial::InvalidOperation& e) {
            cout << "InvalidOperation: " << e.whatOp << e.why << endl;
        }

        work.op = tutorial::Operation::SUBTRACT;
        work.num1 = 15;
        work.num2 = 10;
        int32_t diff = client.calculate(1, work);
        cout << "15 - 10 = " << diff << endl;

        shared::SharedStruct ss;
        client.getStruct(ss, 1);
        cout << "Received log: " << ss << endl;

        transport->close();
    }
    catch (apache::thrift::TException& tx) {
        cout << "error: " << tx.what() << endl;
    }
}

int main()
{
    test_client();

    return 0;
}
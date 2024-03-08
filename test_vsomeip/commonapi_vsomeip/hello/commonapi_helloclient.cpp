#include "v1/helloexample/HelloWorld.hpp"
#include "v1/helloexample/HelloWorldProxyBase.hpp"
#include <chrono>
#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <functional>

#include <CommonAPI/CommonAPI.hpp>
#include <v1/helloexample/HelloWorldProxy.hpp>

using namespace std;
using namespace std::placeholders;

string callstatusToString(const CommonAPI::CallStatus& status)
{
    string str;
    switch (status) {
    case CommonAPI::CallStatus::SUCCESS:
        str = "SUCCESS";
        break;
    case CommonAPI::CallStatus::OUT_OF_MEMORY:
        str = "OUT_OF_MEMORY";
        break;

    case CommonAPI::CallStatus::NOT_AVAILABLE:
        str = "NOT_AVAILABLE";
        break;

    case CommonAPI::CallStatus::CONNECTION_FAILED:
        str = "CONNECTION_FAILED";
        break;

    case CommonAPI::CallStatus::REMOTE_ERROR:
        str = "REMOTE_ERROR";
        break;

    case CommonAPI::CallStatus::UNKNOWN:
        str = "UNKNOWN";
        break;

    case CommonAPI::CallStatus::INVALID_VALUE:
        str = "INVALID_VALUE";
        break;

    case CommonAPI::CallStatus::SUBSCRIPTION_REFUSED:
        str = "SUBSCRIPTION_REFUSED";
        break;

    case CommonAPI::CallStatus::SERIALIZATION_ERROR:
        str = "SERIALIZATION_ERROR";
        break;
    default:
        str = "NONE";
    }

    return str;
}

void sayHello_cb(const CommonAPI::CallStatus& status,
                 const v1::helloexample::HelloWorld::sayHelloError& error,
                 const std::string& out_msg)
{
    cout << __func__ << ", status: " << callstatusToString(status) << " ,error: " << error.toString()
         << ", out_msg: " << out_msg << endl;
}

void attr_sub_cb(const string& calledfunc, const int32_t& val)
{
    std::cout << __func__ << "|" << calledfunc << ", Received change message: " << val << std::endl;
}

void broadcast_sub_cb(const string& calledfunc, const string& val)
{
    std::cout << __func__ << ", calledfunc:" << calledfunc << ", Received change message: " << val << std::endl;
}

void callStatus_cb(const string& calledfunc, const CommonAPI::CallStatus callStatus)
{
    std::cout << __func__ << "calledfunc: " << calledfunc
              << ", Received status change : " << callstatusToString(callStatus) << std::endl;
}

void attributeAsyncCallback(const string& calledfunc, const CommonAPI::CallStatus& status, int32_t value)
{
    cout << __func__ << "calledfunc: " << calledfunc << ", status:" << callstatusToString(status) << " value:" << value
         << endl;
}

int main()
{
    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();
    string domain = "local";
    string instance = "helloexample.HelloWorld";

    std::shared_ptr<v1::helloexample::HelloWorldProxy<>> myproxy =
        runtime->buildProxy<v1::helloexample::HelloWorldProxy>(domain, instance, "helloclient");

    std::cout << "Checking availability!" << std::endl;
    while (!myproxy->isAvailable()) {
        std::this_thread::sleep_for(std::chrono::microseconds(10));
    }
    std::cout << "Available..." << std::endl;

    // x
    std::this_thread::sleep_for(std::chrono::seconds(2));
    CommonAPI::CallStatus callStatus;
    int32_t value = 0;
    myproxy->getXAttribute().getValue(callStatus, value);
    std::cout << "Getting x attribute value: " << value << ", callStatus: " << callstatusToString(callStatus)
              << std::endl;
    value = 100;
    myproxy->getXAttribute().setValueAsync(value, std::bind(&attributeAsyncCallback, "setValueAsync", _1, _2));
    myproxy->getXAttribute().getValueAsync(std::bind(&attributeAsyncCallback, "getValueAsync", _1, _2));
    myproxy->getXAttribute().getChangedEvent().subscribe(std::bind(&attr_sub_cb, "x_ChangedEvent", _1));

    // sayHello
    int32_t id = 11;
    string in_msg = "hello";
    v1::helloexample::HelloWorld::sayHelloError error;
    std::string out_msg;
    myproxy->sayHello(id, in_msg, callStatus, error, out_msg);
    cout << "-----sayHello callstatus: " << callstatusToString(callStatus) << ", error:" << error.toString()
         << ", res: " << out_msg << endl;
    myproxy->sayHelloAsync(id, in_msg, sayHello_cb);

    // foo fireforget函数只有同步调用
    int32_t foo_id = 12;
    string foo_in_msg = "FOO";
    myproxy->foo(foo_id, foo_in_msg, callStatus);
    cout << "foo callstatus: " << callstatusToString(callStatus) << endl;

    // broadcast
    myproxy->getMyStatusEvent().subscribe(std::bind(&broadcast_sub_cb, "MyStatusEvent", std::placeholders::_1),
                                          std::bind(callStatus_cb, "MyStatusEvent().subscribe", _1));
    myproxy->getStatusSpecialSelectiveEvent().subscribe(
        std::bind(&broadcast_sub_cb, "SpecialSelectiveEvent", std::placeholders::_1),
        std::bind(callStatus_cb, "StatusSpecialSelectiveEvent().subscribe", _1));

    unordered_map<unsigned int, std::string> hashmap;
    myproxy->getMyhashmapAttribute().getValue(callStatus, hashmap);
    cout << "hashmap: " << endl;
    for (auto x : hashmap) {
        cout << x.first << ", " << x.second << endl;
    }

    cout << "struct:" << endl;
    v1::helloexample::HelloWorld::MyStruct mystruct;
    myproxy->getMystructAttribute().getValue(callStatus, mystruct);
    cout << mystruct.getA() << ", " << mystruct.getB() << "," << mystruct.getC() << endl;

    cout << "union:" << endl;
    v1::helloexample::HelloWorld::MyUnion myunion;
    myproxy->getMyunionAttribute().getValue(callStatus, myunion);
    if (myunion.hasValue()) {
        cout << myunion.getValueType() << endl;
        // cout << myunion.get<int32_t>() << endl;
    }

    while (1) {
        std::cout << "Waiting for calls... (Abort with CTRL+C)" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(30));
    }

    return 0;
}
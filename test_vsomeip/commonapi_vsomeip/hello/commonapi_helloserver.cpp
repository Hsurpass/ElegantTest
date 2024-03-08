#include <chrono>
#include <cstdint>
#include <iostream>
#include <memory>
#include <thread>
#include <string>

#include <CommonAPI/CommonAPI.hpp>
#include "helloserverImpl.hpp"
#include "v1/helloexample/HelloWorld.hpp"

using namespace std;

int main()
{
    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();
    string domain = "local";
    string instance = "helloexample.HelloWorld";

    std::shared_ptr<HelloWorldStubImpl> helloservice = std::make_shared<HelloWorldStubImpl>();
    while (!runtime->registerService(domain, instance, helloservice)) {
        cout << "service is registering..." << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    cout << "service register success." << endl;

    int32_t x = helloservice->getXAttribute();
    cout << "x: " << x << endl;
    helloservice->setXAttribute(10);

    v1::helloexample::HelloWorld::MyHashmap myhashmap;
    myhashmap.emplace(1234, "aabb");
    helloservice->setMyhashmapAttribute(myhashmap);

    v1::helloexample::HelloWorld::MyStruct mystruct;
    mystruct.setA(6666);
    mystruct.setB(7777);
    mystruct.setC(8888);
    helloservice->setMystructAttribute(mystruct);

    // CommonAPI::Variant<int32_t> a(9999, "dddd");
    // v1::helloexample::HelloWorld::MyUnion myunion(a);

    // helloservice->setMyunionAttribute(myunion);

    while (1) {
        std::cout << "Waiting for calls... (Abort with CTRL+C)" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(30));
    }

    return 0;
}
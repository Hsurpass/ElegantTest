// env VSOMEIP_CONFIGURATION=./vsomeip_local_multiserver_multiclient.json ./build/helloclient1

#include <memory>
#include <vector>
#include <iostream>
#include <iomanip>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <sstream>
#include <set>

#include <vsomeip/application.hpp>
#include <vsomeip/constants.hpp>
#include <vsomeip/message.hpp>
#include <vsomeip/payload.hpp>
#include <vsomeip/primitive_types.hpp>
#include <vsomeip/runtime.hpp>
#include <vsomeip/vsomeip.hpp>
#include <vsomeip/internal/logger.hpp>

#include "service_ids.hpp"

using namespace std;

std::shared_ptr<vsomeip::application> app;
std::mutex mtx;
std::condition_variable condition;

void run()
{
    std::unique_lock<std::mutex> its_lock(mtx);
    condition.wait(its_lock);
    cout << "client1 run()" << endl;

    std::shared_ptr<vsomeip::message> request;
    request = vsomeip::runtime::get()->create_request();
    request->set_service(SAMPLE_SERVICE_ID);
    request->set_instance(SAMPLE_INSTANCE_ID);
    request->set_method(SAMPLE_METHOD_ID);

    std::shared_ptr<vsomeip::payload> request_payload = vsomeip::runtime::get()->create_payload();
    std::vector<vsomeip::byte_t> request_payload_data;
    for (vsomeip::byte_t i = 0; i < 10; i++) {
        request_payload_data.push_back(i % 256);
    }
    request_payload->set_data(request_payload_data);
    request->set_payload(request_payload);
    app->send(request);
    cout << "client1 send data..." << endl;

    std::set<vsomeip::eventgroup_t> event_groups;
    event_groups.insert(SAMPLE_EVENTGROUP_ID);
    app->request_event(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, SAMPLE_EVENT_ID, event_groups);
    app->subscribe(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, SAMPLE_EVENTGROUP_ID);
}

void run1()
{
    std::unique_lock<std::mutex> its_lock(mtx);
    condition.wait(its_lock);
    cout << "------client1 run1()" << endl;

    std::shared_ptr<vsomeip::message> request;
    request = vsomeip::runtime::get()->create_request();
    request->set_service(SAMPLE_SERVICE1_ID);
    request->set_instance(SAMPLE_INSTANCE1_ID);
    request->set_method(SAMPLE_METHOD1_ID);

    string req = "HELLO";
    std::shared_ptr<vsomeip::payload> request_payload = vsomeip::runtime::get()->create_payload();
    std::vector<vsomeip::byte_t> request_payload_data(req.begin(), req.end());

    request_payload->set_data(request_payload_data);
    request->set_payload(request_payload);
    app->send(request);
    cout << "-----client1 send data1..." << endl;
}

void on_message(const std::shared_ptr<vsomeip::message>& response)
{
    cout << "-----client on_message: " << endl;
    std::shared_ptr<vsomeip::payload> response_payload = response->get_payload();
    vsomeip::length_t payload_len = response_payload->get_length();
    cout << "-----payload_len: " << payload_len << endl;

    // Get payload
    if (response->get_service() == SAMPLE_SERVICE_ID) {
        std::stringstream ss;
        for (vsomeip::length_t i = 0; i < payload_len; i++) {
            ss << std::setw(2) << std::setfill('0') << std::hex << (int)*(response_payload->get_data() + i) << " ";
        }

        std::cout << "------CLIENT: Received message with Client/Session [" << std::setw(4) << std::setfill('0')
                  << std::hex << response->get_client() << "/" << std::setw(4) << std::setfill('0') << std::hex
                  << response->get_session() << "] [" << response->get_service() << "." << response->get_instance()
                  << "." << response->get_method() << "."
                  << "]" << ss.str() << std::endl;
    }
    else if (response->get_service() == SAMPLE_SERVICE1_ID) {
        payload_len = response_payload->get_length();
        const char* data = (const char*)response_payload->get_data();
        VSOMEIP_DEBUG << "-----SAMPLE_SERVICE1_ID data: " << data;
        string res(data, payload_len);
        std::cout << "------CLIENT: Received message with Client/Session [" << std::setw(4) << std::setfill('0')
                  << std::hex << response->get_client() << "/" << std::setw(4) << std::setfill('0') << std::hex
                  << response->get_session() << "] [" << response->get_service() << "." << response->get_instance()
                  << "." << response->get_method() << "."
                  << "]" << res << std::endl;
    }
    else {
        std::cout << "------OTHER CLIENT: Received message with Client/Session [" << std::setw(4) << std::setfill('0')
                  << std::hex << response->get_client() << "/" << std::setw(4) << std::setfill('0') << std::hex
                  << response->get_session() << "] [" << response->get_service() << "." << response->get_instance()
                  << "." << response->get_method() << "."
                  << "]" << std::endl;
    }
}

void on_availability(vsomeip::service_t _service, vsomeip::instance_t _instance, bool _is_available)
{
    std::cout << "-----Service [" << std::setw(4) << std::setfill('0') << std::hex << _service << "." << _instance
              << "] is " << (_is_available ? "available." : "NOT available.") << std::endl;

    if (_is_available) {
        std::cout << "-----service is available" << std::endl;
        condition.notify_one();
    }
    else {
        std::cout << "-----service is not available" << endl;
        // condition.notify_one();

        // std::cout << "-----service is not available, recall register_availability_handler" << std::endl;
        // app->register_availability_handler(_service, _instance, on_availability);
    }
}

int main()
{
    VSOMEIP_DEBUG << "someip client start...";
    std::cout << "someip client start..." << std::endl;

    app = vsomeip::runtime::get()->create_application("client1");
    app->init();

    // register server
    app->register_availability_handler(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, on_availability);
    app->request_service(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID);

    // register server1
    app->register_availability_handler(SAMPLE_SERVICE1_ID, SAMPLE_INSTANCE1_ID, on_availability);
    app->request_service(SAMPLE_SERVICE1_ID, SAMPLE_INSTANCE1_ID);

    // register response cb
    // app->register_message_handler(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, SAMPLE_METHOD_ID, on_message);
    app->register_message_handler(vsomeip::ANY_SERVICE, vsomeip::ANY_INSTANCE, vsomeip::ANY_METHOD, on_message);

        /*
        出现 “std::thread sender(run);” 的原因是：当我们尝试将请求从客户端发送给服务时，遇到了一个小问题。
        在发送消息之前必须启动应用程序（app->start()），因为我们需要一个正在运行的事件循环来处理消息。
        但是该方法 app->start() 不会返回，因为它内部有正在运行的事件循环。
        因此，就需要启动一个线程（run），并在此线程中等待 availability 回调的返回，然后再调用app->send(request)。
    */
    // std::thread sender(run);
    std::thread sender_server1(run1);

    app->start();

    // sender.join();
    sender_server1.join();

    return 0;
}

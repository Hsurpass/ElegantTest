// env VSOMEIP_CONFIGURATION=./vsomeip_local_multiserver_multiclient.json ./build/helloclient

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
    cout << "client run()" << endl;

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
    cout << "client send data..." << endl;

    std::set<vsomeip::eventgroup_t> event_groups;
    event_groups.insert(SAMPLE_EVENTGROUP_ID);
    app->request_event(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, SAMPLE_EVENT_ID, event_groups);
    app->subscribe(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, SAMPLE_EVENTGROUP_ID);
}

void on_message(const std::shared_ptr<vsomeip::message>& response)
{
    cout << "client on_message: " << endl;
    std::shared_ptr<vsomeip::payload> response_payload = response->get_payload();
    vsomeip::length_t payload_len = response_payload->get_length();
    cout << "payload_len: " << payload_len << endl;

    // Get payload
    std::stringstream ss;
    for (vsomeip::length_t i = 0; i < payload_len; i++) {
        ss << std::setw(2) << std::setfill('0') << std::hex << (int)*(response_payload->get_data() + i) << " ";
    }

    std::cout << "CLIENT: Received message with Client/Session [" << std::setw(4) << std::setfill('0') << std::hex
              << response->get_client() << "/" << std::setw(4) << std::setfill('0') << std::hex
              << response->get_session() << "] " << ss.str() << std::endl;
}

void on_availability(vsomeip::service_t _service, vsomeip::instance_t _instance, bool _is_available)
{
    std::cout << "-------------Service [" << std::setw(4) << std::setfill('0') << std::hex << _service << "."
              << _instance << "] is " << (_is_available ? "available." : "NOT available.") << std::endl;

    if (_is_available) {
        std::cout << "service is available" << std::endl;
        condition.notify_one();
    }
    else {
        std::cout << "service is not available" << std::endl;
        condition.notify_one();
    }
}

int main()
{
    VSOMEIP_DEBUG << "someip client start...";
    std::cout << "someip client start..." << std::endl;

    app = vsomeip::runtime::get()->create_application("client");
    app->init();

    app->register_availability_handler(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, on_availability);
    app->request_service(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID);

    // app->register_message_handler(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, SAMPLE_METHOD_ID, on_message);
    app->register_message_handler(vsomeip::ANY_SERVICE, vsomeip::ANY_INSTANCE, vsomeip::ANY_METHOD, on_message);
    /*
        出现 “std::thread sender(run);” 的原因是：当我们尝试将请求从客户端发送给服务时，遇到了一个小问题。
        在发送消息之前必须启动应用程序（app->start()），因为我们需要一个正在运行的事件循环来处理消息。
        但是该方法 app->start() 不会返回，因为它内部有正在运行的事件循环。
        因此，就需要启动一个线程（run），并在此线程中等待 availability 回调的返回，然后再调用app->send(request)。
    */
    std::thread sender(run);

    app->start();

    sender.join();

    return 0;
}

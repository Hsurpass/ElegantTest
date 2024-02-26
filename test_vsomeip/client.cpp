#include <memory>
#include <vector>
#include <vsomeip/application.hpp>
#include <vsomeip/constants.hpp>
#include <vsomeip/message.hpp>
#include <vsomeip/payload.hpp>
#include <vsomeip/primitive_types.hpp>
#include <vsomeip/runtime.hpp>
#include <vsomeip/vsomeip.hpp>
#include <iostream>
#include <iomanip>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <sstream>
#include <set>

using namespace std;

#define SAMPLE_SERVICE_ID 0x1234
#define SAMPLE_INSTANCE_ID 0x5678
#define SAMPLE_METHOD_ID 0x6666
#define SAMPLE_EVENTGROUP_ID 0x4465
#define SAMPLE_EVENT_ID 0x8778

std::shared_ptr<vsomeip::application> app;
std::mutex mtx;
std::condition_variable condition;

void run()
{
    std::unique_lock<std::mutex> its_lock(mtx);
    condition.wait(its_lock);

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
    std::cout << "Service [" << std::setw(4) << std::setfill('0') << std::hex << _service << "." << _instance << "] is "
              << (_is_available ? "available." : "NOT available.") << std::endl;
    condition.notify_one();
}

int main()
{
    app = vsomeip::runtime::get()->create_application("Hello");
    app->init();
    app->register_availability_handler(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, on_availability);
    app->request_service(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID);
    // app->register_message_handler(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, SAMPLE_METHOD_ID, on_message);
    app->register_message_handler(vsomeip::ANY_SERVICE, vsomeip::ANY_INSTANCE, vsomeip::ANY_METHOD, on_message);

    std::thread sender(run);
    app->start();

    sender.join();

    return 0;
}

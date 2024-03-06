// env VSOMEIP_CONFIGURATION=./vsomeip_local_multiserver_multiclient.json ./build/helloserver

#include <iomanip>
#include <ostream>
#include <sstream>
#include <vector>
#include <iostream>
#include <memory>
#include <set>

#include <vsomeip/application.hpp>
#include <vsomeip/message.hpp>
#include <vsomeip/payload.hpp>
#include <vsomeip/primitive_types.hpp>
#include <vsomeip/runtime.hpp>
#include <vsomeip/vsomeip.hpp>
#include <vsomeip/internal/logger.hpp>

#include "service_ids.hpp"

using namespace std;

std::shared_ptr<vsomeip::application> app;

void on_message(const std::shared_ptr<vsomeip::message>& request)
{
    cout << "server on_message" << endl;
    std::shared_ptr<vsomeip::payload> request_payload = request->get_payload();
    vsomeip::length_t data_len = request_payload->get_length();
    vsomeip::byte_t* data = request_payload->get_data();
    cout << "payload data length: " << data_len << endl;
    cout << "payload data: " << (char*)data << endl;

    // get data
    std::stringstream ss;
    for (vsomeip::length_t i = 0; i < data_len; i++) {
        ss << std::setw(2) << std::setfill('0') << std::hex << (int)*(data + i) << " ";
    }

    std::cout << "SERVICE: Received message with Client/Session [" << std::setw(4) << std::setfill('0') << std::hex
              << request->get_client() << "/" << std::setw(4) << std::setfill('0') << std::hex << request->get_session()
              << "] " << ss.str() << std::endl;

    //create response
    std::shared_ptr<vsomeip::message> its_response = vsomeip::runtime::get()->create_response(request);
    std::shared_ptr<vsomeip::payload> response_payload = vsomeip::runtime::get()->create_payload();
    std::vector<vsomeip::byte_t> response_payload_data;
    for (int i = 9; i >= 0; i--) {
        response_payload_data.push_back(i % 256);
    }
    response_payload->set_data(response_payload_data);
    its_response->set_payload(response_payload);
    app->send(its_response);
}

void offer_service()
{
    // offer service
    app->register_message_handler(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, SAMPLE_METHOD_ID, on_message);
    app->offer_service(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID);

    // offer event pub/sub
    // 每个事件都属于一个事件组！但它也可以属于多个事件组。
    // 事件不独立于服务而存在;如果尚未提供服务，则该服务对客户端不可用，并且客户端无法订阅。
    const vsomeip::byte_t event_data[] = {0x10};
    std::shared_ptr<vsomeip::payload> event_payload = vsomeip::runtime::get()->create_payload();
    event_payload->set_data(event_data, sizeof(event_data));
    std::set<vsomeip::eventgroup_t> event_groups;
    event_groups.insert(SAMPLE_EVENTGROUP_ID);
    app->offer_event(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, SAMPLE_EVENT_ID, event_groups);
    app->notify(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, SAMPLE_EVENT_ID, event_payload);
}

int main()
{
    // vsomeip::logging::
    // vsomeip::logging::logger::set_level(vsomeip::logging::level_e::LL_DEBUG); // 设置日志等级为DEBUG
    // vsomeip::logging::logger::set_pattern("%TimeStamp% [%ThreadID%] [%LogLevel%]: %Message%"); // 设置日志格式

    VSOMEIP_DEBUG << "someip server start...";
    std::cout << "---------------someip server start..." << std::endl;

    app = vsomeip::runtime::get()->create_application("server");
    app->init();

    offer_service();

    app->start();

    return 0;
}
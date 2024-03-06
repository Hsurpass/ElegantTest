// env VSOMEIP_CONFIGURATION=./vsomeip_local_multiserver_multiclient.json ./build/helloserver1

#include <iomanip>
#include <ostream>
#include <sstream>
#include <string>
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
    cout << "-----server on_message" << endl;
    std::shared_ptr<vsomeip::payload> request_payload = request->get_payload();
    vsomeip::length_t data_len = request_payload->get_length();
    vsomeip::byte_t* data = request_payload->get_data();
    cout << "-----payload data length: " << data_len << endl;
    cout << "-----payload data: " << (const char*)data << endl;
    string res((const char*)data, data_len);
    cout << "-----request payload data: " << res << endl;

    std::cout << "SERVICE: Received message with Client/Session [" << std::setw(4) << std::setfill('0') << std::hex
              << request->get_client() << "/" << std::setw(4) << std::setfill('0') << std::hex << request->get_session()
              << "] " << std::endl;

    //create response
    res += "_WORLD!!!";
    std::shared_ptr<vsomeip::message> its_response = vsomeip::runtime::get()->create_response(request);
    std::shared_ptr<vsomeip::payload> response_payload = vsomeip::runtime::get()->create_payload();
    std::vector<vsomeip::byte_t> response_payload_data(res.begin(), res.end());
    response_payload->set_data(response_payload_data);
    its_response->set_payload(response_payload);
    app->send(its_response);
}

void offer_service()
{
    // offer service
    app->register_message_handler(SAMPLE_SERVICE1_ID, SAMPLE_INSTANCE1_ID, SAMPLE_METHOD1_ID, on_message);
    app->offer_service(SAMPLE_SERVICE1_ID, SAMPLE_INSTANCE1_ID);
}

int main()
{
    // vsomeip::logging::
    // vsomeip::logging::logger::set_level(vsomeip::logging::level_e::LL_DEBUG); // 设置日志等级为DEBUG
    // vsomeip::logging::logger::set_pattern("%TimeStamp% [%ThreadID%] [%LogLevel%]: %Message%"); // 设置日志格式

    VSOMEIP_INFO << "--someip server start...";
    std::cout << "---------------someip server start..." << std::endl;

    app = vsomeip::runtime::get()->create_application("server1");
    app->init();

    offer_service();

    app->start();

    return 0;
}
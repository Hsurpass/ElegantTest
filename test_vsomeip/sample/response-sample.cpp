// Copyright (C) 2014-2023 Bayerische Motoren Werke Aktiengesellschaft (BMW AG)
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
#include <ostream>
#ifndef VSOMEIP_ENABLE_SIGNAL_HANDLING
#include <csignal>
#endif
#include <chrono>
#include <condition_variable>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <thread>

#include <vsomeip/vsomeip.hpp>

#include "sample-ids.hpp"

class service_sample
{
public:
    service_sample(bool _use_static_routing)
        : app_(vsomeip::runtime::get()->create_application("World")), is_registered_(false),
          use_static_routing_(_use_static_routing), blocked_(false), running_(true),
          offer_thread_(std::bind(&service_sample::run, this))
    {}

    bool init()
    {
        std::lock_guard<std::mutex> its_lock(mutex_);

        if (!app_->init()) {
            std::cerr << "-----Couldn't initialize application" << std::endl;
            return false;
        }
        app_->register_state_handler(std::bind(&service_sample::on_state, this, std::placeholders::_1));
        app_->register_message_handler(SAMPLE_SERVICE_ID,
                                       SAMPLE_INSTANCE_ID,
                                       SAMPLE_METHOD_ID,
                                       std::bind(&service_sample::on_message, this, std::placeholders::_1));

        std::cout << "-----Static routing " << (use_static_routing_ ? "ON" : "OFF") << std::endl;
        return true;
    }

    void start()
    {
        app_->start();
    }

#ifndef VSOMEIP_ENABLE_SIGNAL_HANDLING
    /*
     * Handle signal to shutdown
     */
    void stop()
    {
        running_ = false;
        blocked_ = true;
        app_->clear_all_handler();
        stop_offer();
        condition_.notify_one();
        std::cout << "------" << __func__ << " current-thread: " << std::this_thread::get_id()
                  << " offer-thread: " << offer_thread_.get_id() << std::endl;
        if (std::this_thread::get_id() != offer_thread_.get_id()) {
            if (offer_thread_.joinable()) {
                offer_thread_.join();
            }
        }
        else {
            offer_thread_.detach();
        }
        app_->stop();
    }
#endif

    void offer()
    {
        std::cout << "-----offer() service" << std::endl;
        app_->offer_service(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID);
        app_->offer_service(SAMPLE_SERVICE_ID + 1, SAMPLE_INSTANCE_ID);
    }

    void stop_offer()
    {
        std::cout << "-----stop_offer()" << std::endl;
        app_->stop_offer_service(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID);
        app_->stop_offer_service(SAMPLE_SERVICE_ID + 1, SAMPLE_INSTANCE_ID);
    }

    void on_state(vsomeip::state_type_e _state)
    {
        std::cout << "-----on_state Application " << app_->get_name() << " is "
                  << (_state == vsomeip::state_type_e::ST_REGISTERED ? "registered." : "deregistered.") << std::endl;

        if (_state == vsomeip::state_type_e::ST_REGISTERED) {
            if (!is_registered_) {
                is_registered_ = true;
                blocked_ = true;
                condition_.notify_one();
            }
        }
        else {
            is_registered_ = false;
        }
    }

    void on_message(const std::shared_ptr<vsomeip::message>& _request)
    {
        // get data
        std::shared_ptr<vsomeip::payload> request_payload = _request->get_payload();
        vsomeip::length_t data_len = request_payload->get_length();
        vsomeip::byte_t* data = request_payload->get_data();
        std::stringstream ss;
        for (vsomeip::length_t i = 0; i < data_len; i++) {
            ss << std::setw(2) << std::setfill('0') << std::hex << (int)*(data + i) << " ";
        }

        std::cout << "-----on_message Received a message with Client/Session [" << std::setfill('0') << std::hex
                  << std::setw(4) << _request->get_client() << "/" << std::setw(4) << _request->get_session() << "]"
                  << ", request data: " << ss.str() << std::endl;

        std::shared_ptr<vsomeip::message> its_response = vsomeip::runtime::get()->create_response(_request);

        std::shared_ptr<vsomeip::payload> its_payload = vsomeip::runtime::get()->create_payload();
        std::vector<vsomeip::byte_t> its_payload_data;
        for (std::size_t i = 0; i < 12; ++i)
            its_payload_data.push_back(vsomeip::byte_t(i % 256));
        its_payload->set_data(its_payload_data);
        its_response->set_payload(its_payload);

        app_->send(its_response);
    }

    void run()
    {
        std::unique_lock<std::mutex> its_lock(mutex_);
        while (!blocked_)
            condition_.wait(its_lock);

        std::cout << "-----server run..." << std::endl;
        bool is_offer(true);

        if (use_static_routing_) {
            offer();
            while (running_) {
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                // ;
            }
        }
        else {
            while (running_) {
                if (is_offer)
                    offer();
                else
                    stop_offer();

                for (int i = 0; i < 10 && running_; i++)
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                is_offer = !is_offer;
            }
        }
    }

private:
    std::shared_ptr<vsomeip::application> app_;
    bool is_registered_;
    bool use_static_routing_;

    std::mutex mutex_;
    std::condition_variable condition_;
    bool blocked_;
    bool running_;

    // blocked_ must be initialized before the thread is started.
    std::thread offer_thread_;
};

#ifndef VSOMEIP_ENABLE_SIGNAL_HANDLING
service_sample* its_sample_ptr(nullptr);
void handle_signal(int _signal)
{
    std::cout << __func__ << ", signal:" << _signal << std::endl;
    if (its_sample_ptr != nullptr && (_signal == SIGINT || _signal == SIGTERM))
        its_sample_ptr->stop();
}
#endif

int main(int argc, char** argv)
{
    std::cout << "------main-thread: " << std::this_thread::get_id() << std::endl;

#ifndef VSOMEIP_ENABLE_SIGNAL_HANDLING
    std::cout << "VSOMEIP_ENABLE_SIGNAL_HANDLING: " << false << std::endl;
#else
    std::cout << "VSOMEIP_ENABLE_SIGNAL_HANDLING: " << true << std::endl;
#endif
    bool use_static_routing(false);

    std::string static_routing_enable("--static-routing");

    for (int i = 1; i < argc; i++) {
        if (static_routing_enable == argv[i]) {
            use_static_routing = true;
        }
    }

    service_sample its_sample(use_static_routing);
#ifndef VSOMEIP_ENABLE_SIGNAL_HANDLING
    its_sample_ptr = &its_sample;
    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);
#endif
    if (its_sample.init()) {
        its_sample.start();
        return 0;
    }
    else {
        return 1;
    }
}

#include "HelloWorldPubSubTypes.h"
#include "HelloWorld.h"

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <fastdds/dds/domain/qos/DomainParticipantQos.hpp>
#include <fastdds/dds/topic/Topic.hpp>
#include <fastdds/dds/topic/qos/TopicQos.hpp>
#include <fastrtps/types/TypesBase.h>
#include <thread>
#include <iostream>

#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/subscriber/DataReaderListener.hpp>
#include <fastdds/dds/subscriber/qos/DataReaderQos.hpp>
#include <fastdds/dds/subscriber/SampleInfo.hpp>
#include <fastdds/dds/subscriber/Subscriber.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>

using namespace std;
using namespace eprosima::fastdds::dds;

class HelloWorldSubscriber
{
private:
    eprosima::fastdds::dds::DomainParticipant* participant_;
    eprosima::fastdds::dds::TypeSupport type_;
    eprosima::fastdds::dds::Topic* topic_;
    eprosima::fastdds::dds::Subscriber* subscriber_;
    eprosima::fastdds::dds::DataReader* reader_;

    class HelloDRListener : public eprosima::fastdds::dds::DataReaderListener
    {
    public:
        HelloDRListener() : samples_(0)
        {}
        ~HelloDRListener() override
        {}

        void on_subscription_matched(DataReader* reader, const SubscriptionMatchedStatus& info) override
        {
            cout << __func__ << endl;
            if (info.current_count_change == 1) {
                cout << "subscriber matched." << endl;
            }
            else if (info.current_count_change == -1) {
                cout << "subscriber unmatched." << endl;
            }
            else {
                cout << info.current_count_change
                     << " is not a valid value for SubscriptionMatchedStatus current count change" << std::endl;
            }
        }

        void on_data_available(DataReader* reader) override
        {
            cout << __func__ << endl;
            SampleInfo info;
            if (reader->take_next_sample(&hello_, &info) == ReturnCode_t::RETCODE_OK) {
                if (info.valid_data) {
                    samples_++;
                    std::cout << "Message: " << hello_.message() << " with index: " << hello_.index() << " RECEIVED."
                              << std::endl;
                }
            }
        }

        HelloWorld hello_;
        std::atomic_int samples_;
    } listener_;
public:
    HelloWorldSubscriber()
        : participant_(nullptr), subscriber_(nullptr), topic_(nullptr), reader_(nullptr),
          type_(new HelloWorldPubSubType())
    {}
    virtual ~HelloWorldSubscriber()
    {
        if (reader_ != nullptr) {
            subscriber_->delete_datareader(reader_);
        }
        if (topic_ != nullptr) {
            participant_->delete_topic(topic_);
        }
        if (subscriber_ != nullptr) {
            participant_->delete_subscriber(subscriber_);
        }
        DomainParticipantFactory::get_instance()->delete_participant(participant_);
    }

    bool init()
    {
        DomainParticipantQos participantQos;
        participantQos.name("Participant_subscriber");
        participant_ = DomainParticipantFactory::get_instance()->create_participant(0, participantQos);
        if (participant_ == nullptr) {
            return false;
        }

        // register type
        type_.register_type(participant_);

        // create topic
        topic_ = participant_->create_topic("HelloWorldTopic", "HelloWorld", TOPIC_QOS_DEFAULT);
        if (topic_ == nullptr) {
            return false;
        }

        // create subscriber
        subscriber_ = participant_->create_subscriber(SUBSCRIBER_QOS_DEFAULT, nullptr);
        if (subscriber_ == nullptr) {
            cout << "subscriber_ is nullptr" << endl;
            return false;
        }
        else {
            cout << "create subscriber success" << endl;
        }

        // create datareader
        reader_ = subscriber_->create_datareader(topic_, DATAREADER_QOS_DEFAULT, &listener_);
        if (reader_ == nullptr) {
            return false;
        }
        else {
            cout << "create reader success" << endl;
        }

        return true;
    }

    // run the subscriber
    void run(uint32_t samples)
    {
        while (listener_.samples_ < samples) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
};

int main()
{
    cout << "starting subscriber." << endl;
    uint32_t samples = 10;

    HelloWorldSubscriber* mysub = new HelloWorldSubscriber();
    if (mysub->init()) {
        mysub->run(samples);
    }

    delete mysub;

    return 0;
}
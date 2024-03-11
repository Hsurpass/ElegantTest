#include "HelloWorldPubSubTypes.h"
#include "HelloWorld.h"

#include <chrono>
#include <cstdint>
#include <fastdds/dds/domain/qos/DomainParticipantQos.hpp>
#include <fastdds/dds/publisher/qos/DataWriterQos.hpp>
#include <fastdds/dds/publisher/qos/PublisherQos.hpp>
#include <fastdds/dds/topic/Topic.hpp>
#include <fastdds/dds/topic/qos/TopicQos.hpp>
#include <thread>
#include <iostream>

#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/publisher/Publisher.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/DataWriterListener.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>

using namespace std;
using namespace eprosima::fastdds::dds;

class HelloWorldPublisher
{
private:
    HelloWorld hello_;
    eprosima::fastdds::dds::DomainParticipant* participant_;
    eprosima::fastdds::dds::Publisher* publisher_;
    eprosima::fastdds::dds::Topic* topic_;
    eprosima::fastdds::dds::DataWriter* writer_;
    eprosima::fastdds::dds::TypeSupport type_;

    class HelloDWListener : public eprosima::fastdds::dds::DataWriterListener
    {
    public:
        HelloDWListener() : matched_(0)
        {}
        ~HelloDWListener() override
        {}
        std::atomic_int matched_;

        void on_publication_matched(DataWriter* writer, const PublicationMatchedStatus& info) override
        {
            if (info.current_count_change == 1) {
                matched_ = info.total_count;
                std::cout << "publisher matched." << std::endl;
            }
            else if (info.current_count_change == -1) {
                matched_ = info.total_count;
                std::cout << "publisher unmatched." << std::endl;
            }
            else {
                cout << info.current_count_change
                     << " is not a valid value for PublicationMatchedStatus current count change." << std::endl;
            }
        }
    } dwListener_;
public:
    HelloWorldPublisher()
        : participant_(nullptr), publisher_(nullptr), topic_(nullptr), writer_(nullptr),
          type_(new HelloWorldPubSubType())
    {}

    virtual ~HelloWorldPublisher()
    {
        if (writer_ != nullptr) {
            publisher_->delete_datawriter(writer_);
        }
        if (publisher_ != nullptr) {
            participant_->delete_publisher(publisher_);
        }
        if (topic_ != nullptr) {
            participant_->delete_topic(topic_);
        }
        DomainParticipantFactory::get_instance()->delete_participant(participant_);
    }

    // init publisher
    bool init()
    {
        hello_.index(0);
        hello_.message("helloworld");
        DomainParticipantQos participantQos;
        participantQos.name("Participant_publisher");
        participant_ = DomainParticipantFactory::get_instance()->create_participant(0, participantQos);

        if (participant_ == nullptr) {
            return false;
        }

        // register the type
        type_.register_type(participant_);

        // create topic
        topic_ = participant_->create_topic("HelloWorldTopic", "HelloWorld", TOPIC_QOS_DEFAULT);
        if (topic_ == nullptr) {
            return false;
        }
        // create the publisher
        publisher_ = participant_->create_publisher(PUBLISHER_QOS_DEFAULT, nullptr);
        if (publisher_ == nullptr) {
            return false;
        }

        // create datawriter
        writer_ = publisher_->create_datawriter(topic_, DATAWRITER_QOS_DEFAULT, &dwListener_);
        if (writer_ == nullptr) {
            return false;
        }

        return true;
    }

    // publish data
    bool publish()
    {
        if (dwListener_.matched_ > 0) {
            hello_.index(hello_.index() + 1);
            writer_->write(&hello_);

            return true;
        }

        return false;
    }

    // run publisher
    void run(uint32_t samples)
    {
        uint32_t samples_sent = 0;
        while (samples_sent < samples) {
            if (publish()) {
                samples_sent++;
                std::cout << "Message: " << hello_.message() << " with index: " << hello_.index() << " SENT"
                          << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::microseconds(1000));
        }
    }
};

int main()
{
    cout << "starting publisher." << endl;
    uint32_t samples = 10;

    HelloWorldPublisher* mypub = new HelloWorldPublisher();
    if (mypub->init()) {
        mypub->run(samples);
    }

    delete mypub;
    return 0;

    return 0;
}
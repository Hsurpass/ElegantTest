#include <dds/DdsDcpsConditionSeqC.h>
#include <dds/DdsDcpsCoreC.h>
#include <dds/DdsDcpsDomainC.h>
#include <dds/DdsDcpsInfrastructureC.h>
#include <dds/DdsDcpsPublicationC.h>
#include <dds/DdsDcpsTopicC.h>
#include <dds/DCPS/Marked_Default_Qos.h>
#include <iostream>
#include <tao/Basic_Types.h>
#include "dds/DCPS/Service_Participant.h"
#include <dds/DCPS/WaitSet.h>
#include <ace/Log_Msg.h>

#include "build/opendds_generated/MessengerTypeSupportC.h"
#include "build/opendds_generated/MessengerTypeSupportImpl.h"
#include "build/opendds_generated/MessengerC.h"

using namespace std;

int main(int argc, char* argv[])
{
    // init domain participant
    DDS::DomainParticipantFactory_var dpf = TheParticipantFactoryWithArgs(argc, argv);
    // create domain participant
    DDS::DomainParticipant_var participant =
        dpf->create_participant(42, PARTICIPANT_QOS_DEFAULT, 0, OpenDDS::DCPS::DEFAULT_STATUS_MASK);
    if (!participant) {
        std::cerr << "create_participant failed." << std::endl;
        return 1;
    }

    // register typesupport
    Messenger::MessageTypeSupport_var mts = new Messenger::MessageTypeSupportImpl();
    if (DDS::RETCODE_OK != mts->register_type(participant, "")) {
        std::cerr << "register_type failed." << std::endl;
        return 1;
    }

    // create topic
    CORBA::String_var type_name = mts->get_type_name();
    cout << "type_name: " << type_name << endl;
    DDS::Topic_var topic = participant->create_topic("Movie Discussion List",
                                                     type_name,
                                                     TOPIC_QOS_DEFAULT,
                                                     0,
                                                     OpenDDS::DCPS::DEFAULT_STATUS_MASK);
    if (!topic) {
        std::cerr << "create topic failed." << std::endl;
        return 1;
    }

    // create publisher
    DDS::Publisher_var pub =
        participant->create_publisher(PUBLISHER_QOS_DEFAULT, 0, OpenDDS::DCPS::DEFAULT_STATUS_MASK);
    if (!pub) {
        std::cerr << "create_publisher failed." << std::endl;
        return 1;
    }

    // create data writer
    DDS::DataWriter_var writer =
        pub->create_datawriter(topic, DATAWRITER_QOS_DEFAULT, 0, OpenDDS::DCPS::DEFAULT_STATUS_MASK);

    Messenger::MessageDataWriter_var message_writer = Messenger::MessageDataWriter::_narrow(writer);

    // block until subscriber is available
    DDS::StatusCondition_var condition = writer->get_statuscondition();
    condition->set_enabled_statuses(DDS::PUBLICATION_MATCHED_STATUS);

    DDS::WaitSet_var ws = new DDS::WaitSet;
    ws->attach_condition(condition);

    while (true) {
        DDS::PublicationMatchedStatus matches;
        if (writer->get_publication_matched_status(matches) != DDS::RETCODE_OK) {
            std::cerr << "get_publication_matched_status failed!" << std::endl;
            return 1;
        }
        std::cout << matches.current_count << std::endl;
        if (matches.current_count >= 1) {
            break;
        }

        DDS::ConditionSeq conditions;
        DDS::Duration_t timeout = {60, 0};
        if (ws->wait(conditions, timeout) != DDS::RETCODE_OK) {
            std::cerr << "wait failed!" << std::endl;
            return 1;
        }
        else {
            std::cout << "wait set complete" << std::endl;
        }
    }

    ws->detach_condition(condition);

    // send data
    Messenger::Message message;
    message.subject_id = 99;
    message.from = "Comic Book Guy";
    message.subject = "Review";
    message.text = "Worst. Movie. Ever.";
    message.count = 0;

    // registering and using instance, more efficient
    // 如果没有显式注册，第一次写入会导致 OpenDDS 为该实例分配资源
    ::DDS::InstanceHandle_t handle = message_writer->register_instance(message);

    for (int i = 0; i < 10; ++i) {
        // DDS::ReturnCode_t error = message_writer->write(message, DDS::HANDLE_NIL);
        DDS::ReturnCode_t error = message_writer->write(message, handle);

        ++message.count;
        ++message.subject_id;

        if (error != DDS::RETCODE_OK) {
            return 1;
        }
    }

    // 等待subscriber收到所有的数据之后再clean up
    // 启用此操作需要subscriber的datareader的Qos设置为reliablity
    DDS::Duration_t shutdown_delay = {15, 0};
    DDS::ReturnCode_t result;
    result = writer->wait_for_acknowledgments(shutdown_delay);
    if (result != DDS::RETCODE_OK) {
        std::cerr << "Failed while waiting for acknowledgment of "
                  << "data being received by subscriptions, some data "
                  << "may not have been delivered." << std::endl;
    }
    else {
        std::cout << "wait_for_acknowledgments result: " << result << std::endl;
    }
    // clean up!!
    participant->delete_contained_entities(); // delete topic publisher subscriber
    dpf->delete_participant(participant); // delete participant
    TheServiceParticipant->shutdown();

    return 0;
}

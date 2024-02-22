#include <dds/DdsDcpsConditionSeqC.h>
#include <dds/DdsDcpsCoreC.h>
#include <dds/DdsDcpsDataReaderSeqC.h>
#include <dds/DdsDcpsDomainC.h>
#include <dds/DdsDcpsInfrastructureC.h>
#include <dds/DdsDcpsPublicationC.h>
#include <dds/DdsDcpsSubscriptionC.h>
#include <dds/DdsDcpsTopicC.h>
#include <dds/DCPS/Marked_Default_Qos.h>
#include <iostream>
#include <tao/Basic_Types.h>
#include "dds/DCPS/Service_Participant.h"
#include <dds/DCPS/WaitSet.h>

#include "build/opendds_generated/MessengerTypeSupportC.h"
#include "build/opendds_generated/MessengerTypeSupportImpl.h"
#include "build/opendds_generated/MessengerC.h"
#include "dataReaderListenerImpl.h"

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

    // create subscriber
    DDS::Subscriber_var sub =
        participant->create_subscriber(SUBSCRIBER_QOS_DEFAULT, 0, OpenDDS::DCPS::DEFAULT_STATUS_MASK);
    if (!sub) {
        std::cerr << "Failed to create_subscriber." << std::endl;
        return 1;
    }
    else {
        std::cout << "create_subscriber success." << std::endl;
    }

    DDS::DataReaderListener_var listener(new DataReaderListenerImpl);
    DDS::DataReaderQos reader_qos;
    sub->get_default_datareader_qos(reader_qos);
    reader_qos.reliability.kind = DDS::RELIABLE_RELIABILITY_QOS;

    DDS::DataReader_var dr = sub->create_datareader(topic, reader_qos, listener, OpenDDS::DCPS::DEFAULT_STATUS_MASK);
    if (!dr) {
        std::cerr << "create_datareader failed." << std::endl;
        return 1;
    }
    else {
        std::cout << "create datareader success." << std::endl;
    }

    DDS::StatusCondition_var condition = dr->get_statuscondition();
    condition->set_enabled_statuses(DDS::SUBSCRIPTION_MATCHED_STATUS);

    DDS::WaitSet_var ws = new DDS::WaitSet;
    ws->attach_condition(condition);
    while (true) {
        DDS::SubscriptionMatchedStatus matches;
        if (dr->get_subscription_matched_status(matches) != DDS::RETCODE_OK) {
            std::cerr << "get_subscription_matched_status failed" << std::endl;
        }

        if (matches.current_count == 0 && matches.total_count > 0) {
            break;
        }
        DDS::ConditionSeq conditions;
        DDS::Duration_t timeout = {60, 0};
        if (ws->wait(conditions, timeout) != DDS::RETCODE_OK) {
            std::cerr << "datareader wait failed" << std::endl;
        }
        else {
            std::cout << "datareader wait success" << std::endl;
        }
    }

    ws->detach_condition(condition);

    // Clean-up!
    participant->delete_contained_entities();
    dpf->delete_participant(participant);

    TheServiceParticipant->shutdown();

    return 0;
}
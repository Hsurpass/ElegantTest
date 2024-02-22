
#include "dataReaderListenerImpl.h"
#include "build/opendds_generated/MessengerC.h"
#include "build/opendds_generated/MessengerTypeSupportC.h"
#include <ace/Log_Msg.h>
#include <ace/Log_Priority.h>
#include <ace/OS_NS_stdlib.h>
#include <dds/DdsDcpsCoreC.h>
#include <dds/DdsDcpsInfrastructureC.h>
#include <tao/CORBA_methods.h>

void DataReaderListenerImpl::on_requested_deadline_missed(DDS::DataReader_ptr reader,
                                                          const DDS::RequestedDeadlineMissedStatus& status)
{}

void DataReaderListenerImpl::on_requested_incompatible_qos(DDS::DataReader_ptr reader,
                                                           const DDS::RequestedIncompatibleQosStatus& status)
{}

void DataReaderListenerImpl::on_sample_rejected(DDS::DataReader_ptr reader, const DDS::SampleRejectedStatus& status)
{}

void DataReaderListenerImpl::on_liveliness_changed(DDS::DataReader_ptr reader,
                                                   const DDS::LivelinessChangedStatus& status)
{}

// void DataReaderListenerImpl::on_data_available(DDS::DataReader_ptr reader)
// {
//     // ++num_reads_;
//     std::cout << __func__ << std::endl;

//     Messenger::MessageDataReader_var reader_i = Messenger::MessageDataReader::_narrow(reader);
//     if (!reader_i) {
//         std::cerr << "reader: _narrow failed." << std::endl;
//         return;
//     }
//     else {
//         std::cout << "reader: _narrow success." << std::endl;
//     }

//     Messenger::Message message;
//     DDS::SampleInfo si;
//     DDS::ReturnCode_t status = reader_i->take_next_sample(message, si);
//     if (status == DDS::RETCODE_OK) {
//         if (si.valid_data == 1) {
//             std::cout << "Message: subject_id = " << message.subject_id << std::endl;
//             std::cout << "Message: count = " << message.count << std::endl;
//             std::cout << "Message: subject = " << message.subject << std::endl;
//             // std::cout << "Message: subject = " << message.subject.in() << std::endl;
//             std::cout << "Message: from = " << message.from << std::endl;
//             std::cout << "Message: text = " << message.text << std::endl;
//         }
//         else if (si.instance_state == DDS::NOT_ALIVE_DISPOSED_INSTANCE_STATE) { // DataWriter 显式调用 dispose()
//             std::cout << "instance is disposed" << std::endl;
//         }
//         else if (si.instance_state == DDS::NOT_ALIVE_NO_WRITERS_INSTANCE_STATE) { //未注册
//             std::cout << "instance is unregistered" << std::endl;
//         }
//         else {
//             std::cerr << "ERROR: received unknown instance state " << si.instance_state << std::endl;
//         }
//     }
//     else if (status == DDS::RETCODE_NO_DATA) {
//         std::cerr << "ERROR: reader received DDS::RETCODE_NO_DATA!" << std::endl;
//     }
//     else {
//         std::cerr << "ERROR: read Message: Error: " << status << std::endl;
//     }
// }

// ZERO-COPY
void DataReaderListenerImpl::on_data_available(DDS::DataReader_ptr reader)
{
    Messenger::MessageDataReader_var reader_i = Messenger::MessageDataReader::_narrow(reader);
    if (CORBA::is_nil(reader_i.in())) {
        ACE_ERROR((LM_ERROR, ACE_TEXT("ERROR: %N:%l: on_data_available() -") ACE_TEXT(" _narrow failed!\n")));
        ACE_OS::exit(-1);
    }

    Messenger::MessageSeq messages;
    DDS::SampleInfoSeq infos;

    DDS::ReturnCode_t error = reader_i->take(messages,
                                             infos,
                                             ::DDS::LENGTH_UNLIMITED,
                                             ::DDS::ANY_SAMPLE_STATE,
                                             ::DDS::ANY_VIEW_STATE,
                                             ::DDS::ANY_INSTANCE_STATE);

    if (error == DDS::RETCODE_OK) {
        std::cout << "SampleInfo.sample_rank = " << infos[0].sample_rank << std::endl;
        std::cout << "SampleInfo.instance_state = " << infos[0].instance_state << std::endl;
        std::cout << "infos.length: " << infos.length() << std::endl;
        
        if (infos[0].valid_data) {
            std::cout << "Message: subject    = " << messages[0].subject.in() << std::endl
                      << "         subject_id = " << messages[0].subject_id << std::endl
                      << "         from       = " << messages[0].from.in() << std::endl
                      << "         count      = " << messages[0].count << std::endl
                      << "         text       = " << messages[0].text.in() << std::endl;
        }
    }
    else {
        ACE_ERROR((LM_ERROR, ACE_TEXT("ERROR: %N:%l: on_data_available() -") ACE_TEXT(" take failed!\n")));
    }

    reader_i->return_loan(messages, infos);
}

void DataReaderListenerImpl::on_subscription_matched(DDS::DataReader_ptr reader,
                                                     const DDS::SubscriptionMatchedStatus& status)
{}

void DataReaderListenerImpl::on_sample_lost(DDS::DataReader_ptr reader, const DDS::SampleLostStatus& status)
{}
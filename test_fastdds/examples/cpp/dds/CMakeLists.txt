# Copyright 2019 Proyectos y Sistemas de Mantenimiento SL (eProsima).
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

add_subdirectory(AdvancedConfigurationExample)
add_subdirectory(BasicConfigurationExample)
add_subdirectory(Configurability)
add_subdirectory(ContentFilteredTopicExample)
add_subdirectory(CustomListenerExample)
add_subdirectory(CustomPayloadPoolExample)
add_subdirectory(DeadlineQoSExample)
add_subdirectory(DisablePositiveACKs)
add_subdirectory(DiscoveryServerExample)
add_subdirectory(DynamicHelloWorldExample)
add_subdirectory(Filtering)
add_subdirectory(FlowControlExample)
add_subdirectory(HelloWorldExample)
add_subdirectory(HelloWorldExampleDataSharing)
add_subdirectory(HelloWorldExampleSharedMem)
add_subdirectory(HelloWorldExampleTCP)
add_subdirectory(HistoryKind)
add_subdirectory(Keys)
add_subdirectory(LateJoiners)
add_subdirectory(LifespanQoSExample)
add_subdirectory(LivelinessQoS)
add_subdirectory(OwnershipStrengthQoSExample)
add_subdirectory(RequestReplyExample)
add_subdirectory(SampleConfig_Controller)
add_subdirectory(SampleConfig_Events)
add_subdirectory(SampleConfig_Multimedia)
add_subdirectory(StaticHelloWorldExample)
add_subdirectory(TypeLookupService)
add_subdirectory(WriterLoansExample)
add_subdirectory(ZeroCopyExample)

if(SECURITY)
    add_subdirectory(SecureHelloWorldExample)
endif()

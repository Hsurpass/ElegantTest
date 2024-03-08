#include "v1/helloexample/HelloWorld.hpp"
#include <CommonAPI/CommonAPI.hpp>
#include <string>
#include <v1/helloexample/HelloWorldStubDefault.hpp>
#include <iostream>

using namespace std;

class HelloWorldStubImpl : public v1::helloexample::HelloWorldStubDefault
{
public:
    void sayHello(const std::shared_ptr<CommonAPI::ClientId> _client,
                  int32_t _id,
                  std::string _in_msg,
                  sayHelloReply_t _reply) override
    {
        cout << "client id:" << _client->getGid() << "|" << _client->getUid() << ", in_msg: " << _in_msg << endl;
        std::string res = "World";
        _reply(v1::helloexample::HelloWorld::sayHelloError(), res);
    }

    void foo(const std::shared_ptr<CommonAPI::ClientId> _client, int32_t _id, std::string _in_msg) override
    {
        cout << "client id:" << _client->getGid() << "|" << _client->getUid() << ", in_msg: " << _in_msg << endl;
    }

    void onRemoteXAttributeChanged() override
    {
        int x = getXAttribute();
        cout << "-----remote x attr changed, x:" << x << endl;
        fireXAttributeChanged(210);
    }

    void onStatusSpecialSelectiveSubscriptionChanged(
        const std::shared_ptr<CommonAPI::ClientId> _client,
        const CommonAPI::SelectiveBroadcastSubscriptionEvent _event) override
    {
        cout << __func__ << " client id:" << _client->getGid() << "|" << _client->getUid() << ", _event: " << _event
             << endl;
              // broadcast
        fireMyStatusEvent("TTTT");
        fireStatusSpecialSelective("YYYY");
    }
};

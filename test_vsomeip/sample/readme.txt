

To use the example applications you need two devices on the same network. The network addresses within
the configuration files need to be adapted to match the devices addresses.

To start the request/response-example from the build-directory do:

HOST1: env VSOMEIP_CONFIGURATION=./vsomeip_req_res_local.json VSOMEIP_APPLICATION_NAME=request-sample ./build/request-sample
HOST1: env VSOMEIP_CONFIGURATION=./vsomeip_req_res_local.json VSOMEIP_APPLICATION_NAME=response-sample ./build/response-sample --static-routing

To start the subscribe/notify-example from the build-directory do:

HOST1: env VSOMEIP_CONFIGURATION=./vsomeip_pub_sub_local.json VSOMEIP_APPLICATION_NAME=subscribe-sample ./build/subscribe-sample
HOST1: env VSOMEIP_CONFIGURATION=./vsomeip_pub_sub_local.json VSOMEIP_APPLICATION_NAME=notify-sample ./build/notify-sample

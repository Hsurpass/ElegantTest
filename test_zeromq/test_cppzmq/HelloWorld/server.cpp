// g++ server.cpp -lzmq
#include <zmq.hpp>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>

using namespace std;

int main()
{
    // initialize the zmq context with a single IO thread
    zmq::context_t context{1};
    // construct a REP (reply) socket and bind to interface
    zmq::socket_t socket{context, zmq::socket_type::rep};
    socket.bind("tcp://*:5555");

    int count = 0;
    while (1) {
        zmq::message_t request_msg;
        socket.recv(request_msg, zmq::recv_flags::none);
        // socket.recv()
        // cout << "server receive request: " << request_msg << endl;
        cout << "server receive request: " << request_msg.to_string() << endl;

        std::this_thread::sleep_for(1s);

        // send the reply to the client
        char buffer[10] = {0};
        snprintf(buffer, sizeof(buffer), "World_%d", count++);
        std::string buf(buffer);
        socket.send(zmq::buffer(buf), zmq::send_flags::none);
        // zmq::message_t response_msg(buffer, sizeof(buffer));
        // socket.send(response_msg, zmq::send_flags::none);
    }

    return 0;
}
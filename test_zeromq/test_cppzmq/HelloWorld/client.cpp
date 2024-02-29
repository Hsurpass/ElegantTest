#include <string>
#include <iostream>

#include <zmq.hpp>

int main()
{
    // initialize the zmq context with a single IO thread
    zmq::context_t context{1};

    // construct a REQ (request) socket and connect to interface
    zmq::socket_t socket{context, zmq::socket_type::req};
    socket.connect("tcp://localhost:5555");

    for (int i = 0; i < 10; i++) {
        // compose a message from a string and a number
        char buffer[10] = {0};
        snprintf(buffer, sizeof(buffer), "Hello_%d", i);
        zmq::mutable_buffer buf(buffer, strlen(buffer));

        // send the request message
        socket.send(buf, zmq::send_flags::none);

        // wait for reply from server
        zmq::message_t reply{};
        socket.recv(reply, zmq::recv_flags::none);

        std::cout << "client Received msg: " << reply.to_string() << std::endl;
    }

    return 0;
}

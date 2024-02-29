// g++ client.cpp -o client -lzmqpp -lzmq
#include <zmqpp/zmqpp.hpp>
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    const string endpoint = "tcp://localhost:5555";

    // initialize the 0MQ context
    zmqpp::context context;

    // generate a push socket
    zmqpp::socket_type type = zmqpp::socket_type::req;
    zmqpp::socket socket(context, type);

    // open the connection
    cout << "Connecting to hello world server…" << endl;
    socket.connect(endpoint);
    for (int i = 0; i < 10; i++) {
        // send a message
        zmqpp::message message;
        // compose a message from a string and a number
        char buffer[10] = {0};
        snprintf(buffer, sizeof(buffer), "Hello_%d", i);
        message << buffer;
        socket.send(message);
        // socket.send(std::string)
        std::string buffer_;
        socket.receive(buffer_);

        cout << "client Received MSG: " << buffer_ << endl;
    }
}

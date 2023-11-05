#include <boost/asio/buffer.hpp>
#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <array>
#include <type_traits>
#include <vector>

using boost::asio::ip::udp;

int main(int argc, char* argv[])
{
    try {
        // if (argc != 2) {
        //     std::cerr << "Usage: client <host>" << std::endl;
        //     return 1;
        // }

        boost::asio::io_context io_context;

        udp::resolver resolver(io_context);
        udp::resolver::results_type server_endpoints = resolver.resolve(udp::v4(), "127.0.0.1", "1234");
        for (auto& endpoint : server_endpoints) {
            std::cout << endpoint.endpoint() << std::endl;
        }
        // udp::socket socket(io_context, udp::v4());
        udp::socket socket(io_context);
        socket.open(udp::v4());

        std::array<char, 128> send_buf = {{"rfd"}};
        int send_len = socket.send_to(boost::asio::buffer(send_buf), *server_endpoints.begin());
        std::cout << "client send data len: " << send_len << std::endl;

        std::vector<char> recv_buf(128);
        udp::endpoint senderPoint;
        int recv_len = socket.receive_from(boost::asio::buffer(recv_buf), senderPoint);
        std::cout << "senderPoint: " << senderPoint << ",recv_len: " << recv_len << ",recv_buf: " << recv_buf.data()
                  << std::endl;
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}
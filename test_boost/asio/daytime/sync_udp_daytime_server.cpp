#include <boost/asio/io_context.hpp>
#include <boost/system/detail/error_code.hpp>
#include <ctime>
#include <exception>
#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

std::string make_daytime_string()
{
    using namespace std; // For time_t, time and ctime;
    time_t now = time(0);
    return ctime(&now);
}

int main()
{
    try {
        boost::asio::io_context io_context;

        udp::socket socket(io_context, udp::endpoint(udp::v4(), 1234));

        for (;;) {
            boost::array<char, 32> recv_buf;
            udp::endpoint remote_endpoint;

            socket.receive_from(boost::asio::buffer(recv_buf), remote_endpoint);
            std::cout << "remote endpoint: " << remote_endpoint << ", recv buf: " << recv_buf.data() << std::endl;

            std::string msg = make_daytime_string();

            boost::system::error_code error;
            int send_num = socket.send_to(boost::asio::buffer(msg), remote_endpoint, 0, error);
            std::cout << "send_num: " << send_num << std::endl;
        }
    }
    catch (std::exception& e) {
        std::cout << "exception: " << e.what() << std::endl;
    }

    return 0;
}
#include <boost/asio/buffer.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/udp.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/system/detail/error_code.hpp>
#include <cstddef>
#include <exception>
#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <array>
#include <type_traits>
#include <vector>

using boost::asio::ip::udp;

std::string make_daytime_string()
{
    using namespace std; // For time_t, time and ctime;
    time_t now = time(0);
    return ctime(&now);
}

class udp_server
{
public:
    udp_server(boost::asio::io_context& io_context)
        : io_context_(io_context), socket_(io_context, udp::endpoint(udp::v4(), 1234)), recv_buff_(128)
    {
        start_receive();
    }

    void start_receive()
    {
        std::cout << "udp server start receive data..." << std::endl;
        socket_.async_receive_from(boost::asio::buffer(recv_buff_),
                                   remote_endpoint_,
                                   boost::bind(&udp_server::handle_receive,
                                               this,
                                               boost::asio::placeholders::error,
                                               boost::asio::placeholders::bytes_transferred));
    }

    void handle_receive(const boost::system::error_code& error, size_t bytes_transferred)
    {

        std::cout << "udp_server::handle_recv, error: " << error.message()
                  << ", bytes_transferred: " << bytes_transferred << ", remote_endpoint: " << remote_endpoint_
                  << ", recv_buff: " << recv_buff_.data() << std::endl;
        if (!error) {
            std::string str = make_daytime_string();
            socket_.async_send_to(boost::asio::buffer(str),
                                  remote_endpoint_,
                                  boost::bind(&udp_server::handle_send,
                                              this,
                                              boost::asio::placeholders::error,
                                              boost::asio::placeholders::bytes_transferred));
        }
        start_receive();
    }

    void handle_send(const boost::system::error_code& error, size_t bytes_transferred)
    {
        std::cout << "udp_server::handle_send, error: " << error.message() << "bytes_transferred: " << bytes_transferred
                  << std::endl;
    }

private:
    boost::asio::io_context& io_context_;
    udp::socket socket_;
    udp::endpoint remote_endpoint_;
    std::vector<char> recv_buff_;
};

int main()
{
    try {
        boost::asio::io_context io_context;
        udp_server server(io_context);

        io_context.run();
    }
    catch (std::exception& e) {
        std::cout << "exception: " << e.what() << std::endl;
    }
    return 0;
}
#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/address.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/write.hpp>
#include <boost/thread/thread.hpp>

#include <exception>
#include <functional>
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <system_error>
#include <thread>
#include <chrono>
#include <memory>

void sync_echo(std::string msg)
{
    msg += "\n";

    // boost::asio::ip::tcp::socket socket()
}

int main()
{
    // char* messages[] = {"John says hi", "so does James", "Lucy just got home", "Boost.Asio is Fun!", 0};

    boost::asio::io_context io_context;
    boost::asio::ip::tcp::socket connsock(io_context);

    boost::asio::ip::address addr;
    addr.from_string("127.0.0.1");
    boost::asio::ip::tcp::endpoint ep(addr, 1234);

    boost::system::error_code conn_error;
    boost::asio::connect(connsock, &ep, conn_error);
    std::cout << "connect error: " << conn_error.message() << std::endl;

    boost::system::error_code werror;
    std::string msg = "helloworld";
    // int len = boost::asio::write(connsock, boost::asio::buffer(msg), werror);
    int len = connsock.write_some(boost::asio::buffer(msg, msg.size()), werror);
    std::cout << "werror: " << werror.message() << "write len: " << len << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(3));

    boost::system::error_code werror1;
    connsock.write_some(boost::asio::buffer("tcpclient"), werror1);
    std::cout << "werror1: " << werror1.message() << std::endl;

    char buf[32] = {0};
    boost::system::error_code rerror;
    connsock.read_some(boost::asio::buffer(buf), rerror);
    std::cout << "rerror: " << rerror.message() << ", buf: " << buf << std::endl;
}
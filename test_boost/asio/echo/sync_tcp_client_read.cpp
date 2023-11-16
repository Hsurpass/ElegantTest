#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/address.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/asio/read.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/asio/write.hpp>
#include <boost/system/detail/error_code.hpp>
#include <boost/thread/thread.hpp>

#include <cstddef>
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

size_t read_complete(char* buf, char split, const boost::system::error_code& error, size_t bytes)
{
    std::cout << "read_complete error: " << error.message() << ", buf: " << buf << std::endl;
    bool found = std::find(buf, buf + bytes, split) < buf + bytes;
    // bool found = std::find(buf, buf + bytes, split) != buf + bytes; // 不等于end说明找到了

    // 我们一个一个读取直到读到回车，不缓存
    std::cout << "found: " << found << (found ? 0 : 1) << std::endl;
    return found ? 0 : 1;

    // std::cout << "found: " << (found ? 1 : 0) << std::endl;
    // return found;
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

    // boost::system::error_code werror;
    // std::string msg = "helloworld";
    // // int len = boost::asio::write(connsock, boost::asio::buffer(msg), werror);
    // int len = connsock.write_some(boost::asio::buffer(msg, msg.size()), werror);
    // std::cout << "werror: " << werror.message() << "write len: " << len << std::endl;

    // std::this_thread::sleep_for(std::chrono::seconds(3));

    // boost::system::error_code werror1;
    // connsock.write_some(boost::asio::buffer("tcpclient"), werror1);
    // std::cout << "werror1: " << werror1.message() << std::endl;

    // char buf[32] = {0};
    // boost::system::error_code rerror;
    // connsock.read_some(boost::asio::buffer(buf), rerror);
    // std::cout << "rerror: " << rerror.message() << ", buf: " << buf << std::endl;

    char buf[32] = {0};
    boost::system::error_code rerror;
    // 读到指定字节数才会返回，否则一直阻塞
    // boost::asio::read(connsock, boost::asio::buffer(buf), rerror);
    // boost::asio::read(connsock, boost::asio::buffer(buf, 15), rerror);

        // 读到指定结束标记才会返回，否则一直阻塞
    // boost::asio::read(connsock, boost::asio::buffer(buf), "\n", rerror); // compile error
    boost::asio::read(connsock,
                      boost::asio::buffer(buf),
                      boost::bind(read_complete,
                                  buf,
                                  '\n',
                                  boost::asio::placeholders::error,
                                  boost::asio::placeholders::bytes_transferred),
                      rerror);
    // boost::asio::read_until(connsock, boost::asio::buffer(buf), "\n");   //compile error
    std::cout << "rerror: " << rerror.message() << ", buf: " << buf << std::endl;
}
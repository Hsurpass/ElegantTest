// g++ sync_tcp_daytime_client.cpp -lboost_system -std=c++11 -lpthread

#include <array>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/ip/address.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/system/detail/error_code.hpp>
#include <boost/system/system_error.hpp>
#include <iostream>
#include <ostream>
#include <vector>
#include <array>
#include <exception>

// using boost;
using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
    try {
    //     if (argc != 2) {
    //         std::cerr << "Usage: client <host>" << std::endl;
    //         return 0;
    //     }
        boost::asio::ip::address addr;
        addr.from_string("127.0.0.1");
        // boost::asio::ip::tcp::endpoint end(addr, 1234); // 127.0.0.1:1234
        boost::asio::ip::tcp::endpoint end(boost::asio::ip::tcp::v4(), 1234); // 0.0.0.0:1234
        std::cout << end << std::endl;
        std::cout << "address: " << end.address() << std::endl;
        std::cout << "port: " << end.port() << std::endl;

        boost::asio::io_context io_context;
        tcp::resolver resolver(io_context);
        // tcp::resolver::query q("www.baidu.com", "http");
        // tcp::resolver::results_type endpoints = resolver.resolve(q);
        // tcp::resolver::results_type endpoints = resolver.resolve("www.baidu.com", "http");
        // tcp::resolver::results_type endpoints = resolver.resolve("127.0.0.1", "http"); //127.0.0.1:80
        // tcp::resolver::results_type endpoints = resolver.resolve("127.0.0.1", "https"); //127.0.0.1:443
        // tcp::resolver::results_type endpoints = resolver.resolve("127.0.0.1", "ftp"); //127.0.0.1:21
        // tcp::resolver::results_type endpoints = resolver.resolve("127.0.0.1", "0"); //127.0.0.1:0
        tcp::resolver::results_type endpoints = resolver.resolve("127.0.0.1", "1234"); //127.0.0.1:1234

        std::cout << "endpoints size: " << endpoints.size() << std::endl;
        for (auto& r : endpoints) {
            std::cout << "address: " << r.endpoint().address() << std::endl;
            std::cout << "address: " << r.endpoint().address().to_string() << std::endl;
            std::cout << ", is ipv4: " << r.endpoint().address().is_v4() << std::endl;
            std::cout << ", is ipv6: " << r.endpoint().address().is_v6() << std::endl;
            std::cout << ", is loopback: " << r.endpoint().address().is_loopback() << std::endl;
            std::cout << ", is multicast: " << r.endpoint().address().is_multicast() << std::endl;
            std::cout << ", is unspecified: " << r.endpoint().address().is_unspecified() << std::endl;
            std::cout << ", port: " << r.endpoint().port() << std::endl;
            std::cout << ", protocol: " << r.endpoint().protocol().protocol() << std::endl;
            std::cout << ", family: " << r.endpoint().protocol().family() << std::endl;
            std::cout << ", type: " << r.endpoint().protocol().type() << std::endl;
            std::cout << ", ipv4: " << r.endpoint().protocol().v4().family() << std::endl;
            std::cout << ", ipv6: " << r.endpoint().protocol().v6().family() << std::endl;
        }

        std::cout << "---------------------" << std::endl;

        tcp::resolver::iterator itr = resolver.resolve("127.0.0.1", "1234"); //127.0.0.1:1234
        tcp::resolver::iterator enditr;
        while (itr != enditr) {
            boost::asio::ip::tcp::endpoint endpoint = *itr++;
            std::cout << endpoint << std::endl;
        }

        tcp::socket socket(io_context);
        boost::asio::connect(socket, endpoints);
        // boost::asio::connect(socket, itr);

        for (;;) {
            // char[] buf = {0};
            // boost::array<char, 128> buf;
            std::array<char, 128> buf;
            // std::vector<char> buf;
            boost::system::error_code error;

            size_t len = socket.read_some(boost::asio::buffer(buf), error);
            if (error == boost::asio::error::eof) {
                std::cout << "boost::asio::error::eof" << std::endl;
                break;
            }
            else if (error) {
                throw boost::system::system_error(error);
            }

            std::cout.write(buf.data(), len);
        }

        // io_context.run();
    }
    catch (std::exception& e) {
        std::cerr << "exception: " << e.what() << std::endl;
    }

    return 0;
}
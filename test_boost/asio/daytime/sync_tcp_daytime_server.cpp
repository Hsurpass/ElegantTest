#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/write.hpp>
#include <boost/exception/exception.hpp>
#include <boost/system/detail/error_code.hpp>
#include <ctime>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

using boost::asio::ip::tcp;

std::string make_daytime_string()
{
    std::time_t now = std::time(0);

    return std::ctime(&now);
}

int main()
{
    try {
        boost::asio::io_context io_context;
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 1234));

        tcp::socket socket(io_context);
        acceptor.accept(socket);

        std::string msg = make_daytime_string();
        std::cout << msg << std::endl;

        boost::system::error_code ignored_error;
        boost::asio::write(socket, boost::asio::buffer(msg), ignored_error);
        std::this_thread::sleep_for(std::chrono::seconds(2));

        // io_context.run();
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
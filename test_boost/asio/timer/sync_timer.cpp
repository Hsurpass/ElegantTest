#include <boost/asio/steady_timer.hpp>
#include <chrono>
#include <iostream>
#include <boost/asio.hpp>
#include <thread>

int main()
{
    boost::asio::io_context io;
    boost::asio::steady_timer t(io, boost::asio::chrono::seconds(5));

    t.wait();
    std::cout << "hello, world" << std::endl;

    return 0;
}
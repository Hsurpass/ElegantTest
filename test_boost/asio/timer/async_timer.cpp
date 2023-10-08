#include <boost/asio/steady_timer.hpp>
#include <chrono>
#include <iostream>
#include <boost/asio.hpp>
#include <thread>

void print(const boost::system::error_code& err) {
    std::cout << "hello, world" << std::endl;
}

int main()
{
    boost::asio::io_context io;
    boost::asio::steady_timer t(io, boost::asio::chrono::seconds(5));

    t.async_wait(&print);

    io.run();
    
    return 0;
}
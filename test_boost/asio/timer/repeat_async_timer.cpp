#include <boost/asio/placeholders.hpp>
#include <boost/asio/steady_timer.hpp>
#include <chrono>
#include <iostream>
#include <thread>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>

void print(const boost::system::error_code& /*err*/, int* count, boost::asio::steady_timer* t)
{

    if (*count < 5) {
        std::cout << "hello, world, count: " << *count << std::endl;
        ++(*count);

        t->expires_after(std::chrono::seconds(2));
        // t->expires_at(t->expiry() + boost::asio::chrono::seconds(1));
        t->async_wait(boost::bind(&print, boost::asio::placeholders::error, count, t));
    }
}

int main()
{
    boost::asio::io_context io;
    boost::asio::steady_timer t(io, std::chrono::seconds(5));

    int count = 0;
    t.async_wait(boost::bind(&print, boost::asio::placeholders::error, &count, &t));

    io.run();

    return 0;
}

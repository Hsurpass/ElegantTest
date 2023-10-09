#include <boost/asio/placeholders.hpp>
#include <boost/asio/steady_timer.hpp>
#include <chrono>
#include <iostream>
#include <thread>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>

class Printer
{
public:
    Printer(boost::asio::io_context& io) : count(0), m_timer(io, std::chrono::seconds(5))
    {
        m_timer.async_wait(boost::bind(&Printer::print, this, boost::asio::placeholders::error));
    }
    void print(const boost::system::error_code& err)
    {

        if (count < 5) {
            std::cout << "hello, world, count: " << count << std::endl;
            ++count;

            m_timer.expires_after(std::chrono::seconds(2));
            // t->expires_at(t->expiry() + boost::asio::chrono::seconds(1));
            m_timer.async_wait(boost::bind(&Printer::print, this, boost::asio::placeholders::error));
        }
    }
private:
    boost::asio::steady_timer m_timer;
    int count = 0;
};

int main()
{
    boost::asio::io_context io;
    Printer p(io);
    std::cout << "start run" << std::endl;
    io.run();
    std::cout << "stop run" << std::endl;

    return 0;
}

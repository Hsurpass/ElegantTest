#include <boost/asio/io_context.hpp>
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
    Printer(boost::asio::io_context& io, int tag) : m_count(0), m_timer(io, std::chrono::seconds(5)), m_tag(tag)
    {
        m_timer.async_wait(boost::bind(&Printer::print, this, boost::asio::placeholders::error));
    }
    void print(const boost::system::error_code& err)
    {

        if (m_count < 5) {
            std::cout << "hello, world,tag[" << m_tag << "] threadid:[" << std::this_thread::get_id()
                      << "]count: " << m_count << std::endl;
            ++m_count;

            m_timer.expires_after(std::chrono::seconds(2));
            // t->expires_at(t->expiry() + boost::asio::chrono::seconds(1));
            m_timer.async_wait(boost::bind(&Printer::print, this, boost::asio::placeholders::error));
        }
    }
private:
    boost::asio::steady_timer m_timer;
    int m_count = 0;
    int m_tag;
};

void test1()
{
    boost::asio::io_context io;
    Printer p1(io, 1);
    Printer p2(io, 2);

    std::cout << "start run" << std::endl;
    io.run();
    std::cout << "stop run" << std::endl;
}

void print1()
{
    std::cout << "print1 start thread_id:" << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10));
    std::cout << "print1 end thread_id:" << std::this_thread::get_id() << std::endl;
}
void print2()
{
    std::cout << "print2 start thread_id:" << std::this_thread::get_id() << std::endl;
    std::cout << "print2 end thread_id:" << std::this_thread::get_id() << std::endl;
}

// 两个定时器的回调函数注册到一个io上，如果到期时间相同，另一个会被阻塞住。
void test2()
{
    boost::asio::io_context io;
    boost::asio::steady_timer timer1(io, std::chrono::seconds(1));
    boost::asio::steady_timer timer2(io, std::chrono::seconds(1));
    timer1.async_wait(std::bind(&print1));
    timer2.async_wait(std::bind(&print2));

    io.run();
}

int main()
{
    // test1();
    test2();
    return 0;
}

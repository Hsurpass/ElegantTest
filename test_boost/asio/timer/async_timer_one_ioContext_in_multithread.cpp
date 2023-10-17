// g++ -std=c++11 your_file.cpp -lboost_system -lboost_thread -lboost_chrono

#include <boost/asio/bind_executor.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/asio.hpp>
#include <boost/asio/strand.hpp>
#include <boost/thread/thread.hpp>
#include <boost/bind/bind.hpp>

#include <iostream>
#include <chrono>
#include <thread>
#include <functional>

class Printer
{
public:
    Printer(boost::asio::io_context& io, int tag)
        : m_count(0), m_strand(make_strand(io)), m_timer1(io, std::chrono::seconds(5)),
          m_timer2(io, std::chrono::seconds(5)), m_tag(tag)
    {
        m_timer1.async_wait(
            boost::asio::bind_executor(m_strand,
                                       boost::bind(&Printer::print1, this, boost::asio::placeholders::error)));
        m_timer2.async_wait(
            boost::asio::bind_executor(m_strand,
                                       boost::bind(&Printer::print2, this, boost::asio::placeholders::error)));
    }
    void print1(const boost::system::error_code& err)
    {

        if (m_count < 5) {
            std::cout << "print1,tag[" << m_tag << "] threadid:[" << std::this_thread::get_id()
                      << "]count: " << m_count << std::endl;
            ++m_count;

            // m_timer.expires_after(std::chrono::seconds(2));
            m_timer1.expires_at(m_timer1.expiry() + boost::asio::chrono::seconds(1));
            m_timer1.async_wait(
                boost::asio::bind_executor(m_strand,
                                           boost::bind(&Printer::print1, this, boost::asio::placeholders::error)));
        }
    }

    void print2(const boost::system::error_code& err)
    {

        if (m_count < 5) {
            std::cout << "print2,tag[" << m_tag << "] threadid:[" << std::this_thread::get_id()
                      << "]count: " << m_count << std::endl;
            ++m_count;

            // m_timer.expires_after(std::chrono::seconds(2));
            m_timer2.expires_at(m_timer2.expiry() + boost::asio::chrono::seconds(1));
            m_timer2.async_wait(
                boost::asio::bind_executor(m_strand,
                                           boost::bind(&Printer::print2, this, boost::asio::placeholders::error)));
        }
    }
    void test_thread()
    {}
private:
    boost::asio::strand<boost::asio::io_context::executor_type> m_strand;
    boost::asio::steady_timer m_timer1;
    boost::asio::steady_timer m_timer2;

    int m_count = 0;
    int m_tag;
};

void test1()
{
    boost::asio::io_context io;
    Printer p1(io, 1);

    std::thread t(boost::bind(&boost::asio::io_context::run, &io));
    std::cout << "start run" << std::endl;
    io.run();
    t.join();
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

// 两个定时器的回调函数注册到一个io上，io_context::run()跑在多个线程上， 如果到期时间相同，回调函数则会在任意线程上执行。
// 临界资源：std::cout
// 如果有多个线程执行同一个io_context的run函数，那么注册到该IO上的句柄如果访问到共享资源需要进行同步。
// 1.使用strand进行同步。
// 2.加锁同步
void test2()
{
    boost::asio::io_context io;
    boost::asio::steady_timer timer1(io, std::chrono::seconds(1));
    boost::asio::steady_timer timer2(io, std::chrono::seconds(1));

    // timer1.async_wait( std::bind(&print1));
    // timer2.async_wait(std::bind(&print2));

    // boost::asio::strand strand(io);
    boost::asio::strand<boost::asio::io_context::executor_type> strand = boost::asio::make_strand(io);
    timer1.async_wait(boost::asio::bind_executor(strand, std::bind(&print1)));
    timer2.async_wait(boost::asio::bind_executor(strand, std::bind(&print2)));

    boost::thread t(boost::bind(&boost::asio::io_context::run, &io));
    // Printer p(io, 1);
    // std::thread t1(std::bind(&Printer::test_thread, &p));    // true
    // std::thread t1(std::bind(&boost::asio::io_context::run, &io, boost::asio::placeholders::error)); // error
    // std::thread t1([&io] {
    //     io.run();
    // });  // true
    std::thread t2(boost::bind(&boost::asio::io_context::run, &io)); //true

    // io.run();
    t.join();
    // t1.join();
    t2.join();
}

int main()
{
    test1();
    // test2();
    return 0;
}

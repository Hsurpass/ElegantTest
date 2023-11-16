// g++ test1.cpp -lboost_system -lboost_thread
#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/system/detail/error_code.hpp>
#include <boost/bind/bind.hpp>
#include <iostream>

// using namespace boost::asio;

void signal_handler()
{
    std::cout << "receive signal" << std::endl;
}

void handle_signal(const boost::system::error_code& error, int signal)
{
    std::cout << "error: " << error.message() << ", signal: " << signal << std::endl;
}

void test_signal()
{
    boost::asio::io_context io_context;

    boost::asio::signal_set sig(io_context, SIGINT);
    // sig.add(SIGTERM);
    sig.async_wait(std::bind(signal_handler));
    sig.async_wait(boost::bind(&handle_signal,
                               boost::asio::placeholders::error,
                               boost::asio::placeholders::signal_number)); // 注册回调函数

    io_context.run();
}

int main()
{
    test_signal();

    return 0;
}

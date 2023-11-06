// #pragma once
#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/system/detail/error_code.hpp>
#include <boost/bind/bind.hpp>
#include <iostream>

// using namespace boost::asio;

// void handle_signal(const boost::system::error_code& error, int signal)
// {
//     std::cout << "error: " << error.message() << ", signal: " << signal << std::endl;
// }

// void test_signal()
// {
//     boost::asio::io_context io_context;

//     boost::asio::signal_set sig(io_context, SIGINT);
//     // sig.add(SIGTERM);
//     sig.async_wait(handle_signal);

//     io_context.run();
// }

// int main()
// {
//     test_signal();

//     return 0;
// }

// void signal_handler(const boost::system::error_code& /*e*/, int signal)
// {
//     std::cout << "Received signal.\n";
// }

void signal_handler()
{
    std::cout << "Received signal.\n";
}

int main()
{
    boost::asio::io_context io;
    boost::asio::signal_set signals(io, SIGINT); // 监听SIGINT信号（通常是Ctrl+C）
    // signals.async_wait(boost::bind(&signal_handler,
    //                                boost::asio::placeholders::error,
    //                                boost::asio::placeholders::signal_number)); // 注册回调函数
    // signals.async_wait(&signal_handler);
    signals.async_wait(boost::bind(&signal_handler));
    io.run(); // 运行io_context，开始监听信号

    return 0;
}
#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/address.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/system/detail/error_code.hpp>
#include <boost/thread/thread.hpp>

#include <cstddef>
#include <cstdio>
#include <cstring>
#include <exception>
#include <functional>
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <system_error>
#include <thread>
#include <chrono>
#include <memory>

void do_write(std::shared_ptr<boost::asio::ip::tcp::socket> socket, int seq);

void on_write(int seq, const boost::system::error_code& error, size_t byte_transferred)
{
    printf("on_write seq: %d, thread id: %ld\n", seq, std::this_thread::get_id());
}

void do_write(std::shared_ptr<boost::asio::ip::tcp::socket> socket, int seq)
{
    // std::string msg = "asyncserver";
    std::string msg = "asyncserver\n";
    socket->async_write_some(
        boost::asio::buffer(msg),
        boost::bind(on_write, seq, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

/*
void do_read(boost::asio::ip::tcp::socket& socket, int seq);
void on_read(int seq,
             boost::asio::ip::tcp::socket& socket,
             char* buf,
             const boost::system::error_code& error,
             size_t byte_transferred)
{
    printf("on_read seq: %d, thread id: %ld\n", seq, std::this_thread::get_id());
    if (error == boost::asio::error::eof) {
        std::cout << "on_read peer write close" << std::endl;
        delete[] buf;
        socket.close();

        return;
    }

    // std::string str(buf, byte_transferred);
    // std::string str(buf);
    std::cout << "on_read error: " << error.message() << ", bytes num: " << byte_transferred << ", buf:" << buf
              << std::endl;
    printf("buf:%s\n", buf);
    // for (int i = 0; i < byte_transferred; i++) {
    for (int i = 0; i < 12; i++) {
        std::cout << "buf [" << i << "]: " << buf[i] << std::endl;
    }
    delete[] buf;

    std::this_thread::sleep_for(std::chrono::seconds(5));
    // int count = 0;
    // while (count < 5) {
    //     printf("threadid[%ld]_count%d\n", std::this_thread::get_id(), count);
    //     ++count;
    //     std::this_thread::sleep_for(std::chrono::seconds(1));
    // }

    do_read(socket, seq);
}

void do_read(boost::asio::ip::tcp::socket& socket, int seq)
{
    // char buf[32] = {0}; //异步调用要保证传入的buf和socket一定是可用的。
    // std::vector<char> buf(32);
    char* const buf = new char[32];
    memset(buf, 0, 32);
    socket.async_read_some(boost::asio::buffer(buf, 32),
                           boost::bind(on_read,
                                       seq,
                                       boost::ref(socket),
                                       buf,
                                       boost::asio::placeholders::error,
                                       boost::asio::placeholders::bytes_transferred));
}
*/

void do_accept(boost::asio::io_context& io_context, boost::asio::ip::tcp::acceptor& acceptor);
void on_accept(boost::asio::io_context& io_context,
               boost::asio::ip::tcp::acceptor& acceptor,
               std::shared_ptr<boost::asio::ip::tcp::socket> socket,
               const boost::system::error_code& error)
{
    std::cout << "on accept error: " << error.message() << std::endl;
    if (error) {
        return;
    }

    // do_read(socket, 1);
    // do_read(socket, 2); // 多线程场景下，不要对一个socket同时进行读操作，会造成数据混乱
    // do_read(socket, 3);

    do_write(socket, 11);
    std::this_thread::sleep_for(std::chrono::seconds(5));
    do_write(socket, 11);
    std::this_thread::sleep_for(std::chrono::seconds(5));

    do_accept(io_context, acceptor);
}

void do_accept(boost::asio::io_context& io_context, boost::asio::ip::tcp::acceptor& acceptor)
{
    // boost::asio::ip::tcp::socket connsocket(io_context);  // 异步操作要保证传进去的值是始终有效的。
    std::shared_ptr<boost::asio::ip::tcp::socket> connsocket(new boost::asio::ip::tcp::socket(io_context));
    acceptor.async_accept(*connsocket,
                          boost::bind(on_accept,
                                      boost::ref(io_context),
                                      boost::ref(acceptor),
                                      connsocket,
                                      boost::asio::placeholders::error));
}

int main()
{
    boost::asio::io_context io_context;

    boost::asio::ip::tcp::endpoint ep(boost::asio::ip::tcp::v4(), 1234);
    boost::asio::ip::tcp::acceptor acceptor(io_context, ep);

    do_accept(io_context, acceptor);

    // 单线程场景：
    // io_context.run();

    // 多线程场景：
    boost::thread_group threads;
    for (int i = 0; i < 3; i++) {
        threads.create_thread([&io_context] {
            io_context.run();
        });
    }

    threads.join_all();
    // std::this_thread::sleep_for(std::chrono::seconds(2));
    // if (io_context.stopped()) {
    //     io_context.reset();
    //     io_context.restart();
    // }
}
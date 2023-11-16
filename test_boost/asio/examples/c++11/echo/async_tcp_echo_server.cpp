//
// async_tcp_echo_server.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2023 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class session : public std::enable_shared_from_this<session>
{
public:
    session(tcp::socket socket) : socket_(std::move(socket))
    {}//不能在构造函数中调用start,因为start中调用了shared_from_this()，但是对象还没构造完。

    void start()
    {
        do_read();
    }

private:
    void do_read()
    {
        auto self(shared_from_this());  // session引用计数+1，离开作用域-1
        socket_.async_read_some(
            boost::asio::buffer(data_, max_length),
            [this, self](
                boost::system::error_code ec,
                std::size_t
                    length) { // self session引用计数+1，因为do_write要使用socket, 所以要始终保持session有效，离开作用域-1
                if (!ec) {
                    do_write(length);
                } // 发生错误，离开作用域，引用计数减一，socket释放
            });
    }

    void do_write(std::size_t length)
    {
        auto self(shared_from_this()); // session引用计数+1，离开作用域-1
        boost::asio::async_write(socket_,
                                 boost::asio::buffer(data_, length),
                                 [this, self](boost::system::error_code ec, std::size_t /*length*/) {
                                     if (!ec) {
                                         do_read();
                                     } // 发生错误，离开作用域，引用计数减一，socket释放
                                 });
    }

    tcp::socket socket_;
    enum
    {
        max_length = 1024
    };
    char data_[max_length];
};

class server
{
public:
    server(boost::asio::io_context& io_context, short port) : acceptor_(io_context, tcp::endpoint(tcp::v4(), port))
    {
        do_accept();
    }

private:
    void do_accept()
    {
        acceptor_.async_accept([this](boost::system::error_code ec, tcp::socket socket) {
            if (!ec) {
                std::make_shared<session>(std::move(socket))->start(); // session引用计数+1，离开作用域-1
            }

            do_accept();
        });
    }

    tcp::acceptor acceptor_;
};

int main(int argc, char* argv[])
{
    try {
        if (argc != 2) {
            std::cerr << "Usage: async_tcp_echo_server <port>\n";
            return 1;
        }

        boost::asio::io_context io_context;

        server s(io_context, std::atoi(argv[1]));

        io_context.run();
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
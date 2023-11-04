#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/asio/write.hpp>
#include <boost/exception/exception.hpp>
#include <boost/system/detail/error_code.hpp>
#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <cstddef>
#include <ctime>
#include <exception>
#include <functional>
#include <iostream>
#include <string>
#include <system_error>
#include <thread>
#include <chrono>
#include <memory>

using boost::asio::ip::tcp;
// using boost::asio::placeholders;

std::string make_daytime_string()
{
    using namespace std; // For time_t, time and ctime;
    time_t now = time(0);
    return ctime(&now);
}

class tcp_connection : public std::enable_shared_from_this<tcp_connection>
{
public:
    typedef std::shared_ptr<tcp_connection> TcpConnectionPointer;

    static TcpConnectionPointer create(boost::asio::io_context& io_context)
    {
        return TcpConnectionPointer(new tcp_connection(io_context));
    }

    tcp::socket& socket()
    {
        return m_socket;
    }

    void start()
    {
        m_message = make_daytime_string();

        boost::asio::async_write(m_socket,
                                 boost::asio::buffer(m_message),
                                 boost::bind(&tcp_connection::handle_write,
                                             shared_from_this(),
                                             boost::asio::placeholders::error,
                                             boost::asio::placeholders::bytes_transferred));
    }

    void handle_write(const boost::system::error_code& error, size_t bytes_transferred)
    {
        std::cout << "tcp_connection::handle_write, error: " << error.message()
                  << ", bytes_transferred: " << bytes_transferred << std::endl;
    }

    ~tcp_connection()
    {
        std::cout << "destroy connection: " << this << std::endl;
    }
private:
    tcp_connection(boost::asio::io_context& io_context) : m_socket(io_context)
    {}

    tcp::socket m_socket;
    std::string m_message;
};

class tcp_server
{
public:
    tcp_server(boost::asio::io_context& io_context)
        : io_context_(io_context), acceptor_(io_context, tcp::endpoint(tcp::v4(), 1234))
    {
        start_accept();
    }

    void start_accept()
    {
        std::cout << "tcp_server::start_accept..." << std::endl;
        tcp_connection::TcpConnectionPointer conn_socket = tcp_connection::create(io_context_);
        acceptor_.async_accept(
            conn_socket->socket(),
            boost::bind(&tcp_server::handle_accept, this, conn_socket, boost::asio::placeholders::error));
    }

private:
    void handle_accept(tcp_connection::TcpConnectionPointer new_connection, const boost::system::error_code& error)
    {
        // std::cout << "tcp_server::handle_accept, connection:" << new_connection.get() << std::endl;
        if (!error) {
            new_connection->start();
        }

        start_accept();
    }

    boost::asio::io_context& io_context_;
    tcp::acceptor acceptor_;
};

int main()
{
    try {
        boost::asio::io_context io_context;
        tcp_server server(io_context);

        io_context.run();
    }
    catch (std::exception& e) {
        std::cerr << "exception:" << e.what() << std::endl;
    }

    return 0;
}


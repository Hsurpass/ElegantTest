// g++ server.cpp -L/lib/x86_64-linux-gnu  -lssl -lcrypto -o server

#include <iostream>
#include <exception>
#include <cstdlib>
#include <functional>

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

using namespace std;

class server
{
public:
    server(boost::asio::io_context& io_context, unsigned short port)
        : acceptor_(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
          context_(boost::asio::ssl::context::sslv23)
    {
        context_.set_options(boost::asio::ssl::context::default_workarounds | boost::asio::ssl::context::no_sslv2 |
                             boost::asio::ssl::context::single_dh_use);
        context_.set_password_callback(std::bind(&server::get_password, this));
        context_.use_certificate_chain_file("server.pem");
        context_.use_private_key_file("server.pem", boost::asio::ssl::context::pem);
        context_.use_tmp_dh_file("dh4096.pem");
    }
private:
    std::string get_password() const
    {
        return "test";
    }
    boost::asio::ip::tcp::acceptor acceptor_;
    boost::asio::ssl::context context_;
};

int main(int argc, char* argv[])
{
    try {
        if (argc != 2) {
            std::cerr << "Usage: server <port>\n";
            return 1;
        }

        boost::asio::io_context io_context;
        server s(io_context, atoi(argv[1]));

        io_context.run();
    }
    catch (std::exception& e) {
        std::cout << "exception: " << e.what() << std::endl;
    }
    return 0;
}
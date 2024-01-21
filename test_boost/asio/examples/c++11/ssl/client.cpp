//  g++ client.cpp -lboost_system  -lssl -lcrypto -o client

#include <boost/asio/connect.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/context.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <boost/asio/ssl/stream_base.hpp>
#include <boost/asio/ssl/verify_context.hpp>
#include <boost/asio/ssl/verify_mode.hpp>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <openssl/x509.h>
#include <openssl/x509_vfy.h>
#include <unistd.h>

using boost::asio::ip::tcp;
using std::placeholders::_1;
using std::placeholders::_2;

enum
{
    max_length = 1024
};

class client
{
public:
    client(boost::asio::io_context& io_context,
           boost::asio::ssl::context& context,
           const boost::asio::ip::tcp::resolver::results_type& endpoints)
        : socket_(io_context, context)
    {
        socket_.set_verify_mode(boost::asio::ssl::verify_peer);
        socket_.set_verify_callback(std::bind(&client::verify_certificate, this, _1, _2));
        connect(endpoints);
    }

private:
    bool verify_certificate(bool preverified, boost::asio::ssl::verify_context& ctx)
    {
        // In this example we will simply print the certificate's subject name.
        char subject_name[256];
        X509* cert = X509_STORE_CTX_get_current_cert(ctx.native_handle());
        X509_NAME_oneline(X509_get_subject_name(cert), subject_name, 256);
        std::cout << "Verifying " << subject_name << "\n";

        return preverified;
    }
    void connect(const boost::asio::ip::tcp::resolver::results_type& endpoints)
    {
        // socket_.lowest_layer().async_connect(const endpoint_type &peer_endpoint)
        boost::asio::async_connect(socket_.lowest_layer(),
                                   endpoints,
                                   [this](const boost::system::error_code& error, const tcp::endpoint& /*endpoint*/) {
                                       if (!error) {
                                           handshake();
                                       }
                                       else {
                                           std::cout << "Connect failed: " << error.message() << "\n";
                                       }
                                   });
    }
    void handshake()
    {
        socket_.async_handshake(boost::asio::ssl::stream_base::client, [this](const boost::system::error_code& error) {
            if (!error) {
                send_request();
            }
            else {
                std::cout << "Handshake failed: " << error.message() << "\n";
            }
        });
    }

    void send_request()
    {
        std::cout << "Enter message: ";
        std::cin.getline(request_, max_length);
        size_t request_length = std::strlen(request_);

        boost::asio::async_write(socket_,
                                 boost::asio::buffer(request_, request_length),
                                 [this](const boost::system::error_code& error, std::size_t length) {
                                     if (!error) {
                                         receive_response(length);
                                     }
                                     else {
                                         std::cout << "Write failed: " << error.message() << "\n";
                                     }
                                 });
    }

    void receive_response(std::size_t length)
    {
        boost::asio::async_read(socket_,
                                boost::asio::buffer(reply_, length),
                                [this](const boost::system::error_code& error, std::size_t length) {
                                    if (!error) {
                                        std::cout << "Reply: ";
                                        std::cout.write(reply_, length);
                                        std::cout << "\n";
                                    }
                                    else {
                                        std::cout << "Read failed: " << error.message() << "\n";
                                    }
                                });
    }

    boost::asio::ssl::stream<boost::asio::ip::tcp::socket> socket_;
    char request_[max_length];
    char reply_[max_length];
};

int main(int argc, char* argv[])
{
    try {
        if (argc != 3) {
            std::cerr << "Usage: client <host> <port>\n";
            return 1;
        }

        boost::asio::io_context io_context;

        tcp::resolver resolver(io_context);
        auto endpoints = resolver.resolve(argv[1], argv[2]);

        boost::asio::ssl::context ctx(boost::asio::ssl::context::sslv23);
        // ctx.load_verify_file("server_cert_chain.pem");
        ctx.load_verify_file("./boostssl/ca.pem");

        client c(io_context, ctx, endpoints);
        io_context.run();
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
}
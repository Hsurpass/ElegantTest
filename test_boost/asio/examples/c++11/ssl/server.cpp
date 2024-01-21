// g++ server.cpp -lboost_system -L/lib/x86_64-linux-gnu -lssl -lcrypto -o server

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ip/udp.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <iostream>
#include <exception>
#include <cstdlib>
#include <functional>

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <memory>

using namespace std;

class session : public std::enable_shared_from_this<session>
{
public:
    session(boost::asio::ssl::stream<boost::asio::ip::tcp::socket> sslsocket /*只能接收一个右值，但是它本身是个左值*/)
        : sslsocket_(std::move(sslsocket))
    // session(boost::asio::ssl::stream<boost::asio::ip::tcp::socket>&& sslsocket/*只能接收一个右值，但是它本身是个左值*/) : sslsocket_(std::move(sslsocket))
    {}
    void start()
    {
        do_handshake();
    }
private:
    void do_handshake()
    {
        auto self(shared_from_this());
        sslsocket_.async_handshake(boost::asio::ssl::stream_base::server,
                                   [this, self](const boost::system::error_code& error) {
                                       if (!error) {
                                           do_read();
                                       }
                                   });
    }

    void do_read()
    {
        auto self(shared_from_this());
        sslsocket_.async_read_some(boost::asio::buffer(data_),
                                   [this, self](const boost::system::error_code& ec, std::size_t length) {
                                       if (!ec) {
                                           do_write(length);
                                       }
                                   });
    }

    void do_write(std::size_t length)
    {
        auto self(shared_from_this());
        boost::asio::async_write(sslsocket_,
                                 boost::asio::buffer(data_, length),
                                 [this, self](const boost::system::error_code& ec, std::size_t /*length*/) {
                                     if (!ec) {
                                         do_read();
                                     }
                                 });
    }
    boost::asio::ssl::stream<boost::asio::ip::tcp::socket> sslsocket_;
    // boost::asio::ssl::stream<boost::asio::ip::udp::socket> udpsocket_;
    char data_[1024];
};

class server
{
public:
    server(boost::asio::io_context& io_context, unsigned short port)
        : acceptor_(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
          context_(boost::asio::ssl::context::sslv23)
    {
        // default_workarounds: 这是一个预定义的常量，用于启用针对已知问题的工作绕过方案
        // no_sslv2: 禁用SSLv2协议
        // single_dh_use: 指示应该只为每个新的连接创建一个新的临时Diffie-Hellman（DH）参数集，并且这些参数只应用于那个特定的连接。这有助于防止攻击者通过重复使用相同的DH参数来推断密钥材料。
        context_.set_options(boost::asio::ssl::context::default_workarounds | boost::asio::ssl::context::no_sslv2 |
                             boost::asio::ssl::context::single_dh_use);

        // 这是为SSL证书文件设置密码回调函数。当需要访问加密的私钥时，这个回调函数会被调用来获取密码。
        context_.set_password_callback(std::bind(&server::get_password, this));

        // 这是加载服务器的公钥证书链。这个文件通常包含了服务器的公共证书和所有中间证书。
        // context_.use_certificate_chain_file("server_cert_chain.pem");
        context_.use_certificate_chain_file("./boostssl/server.pem");

        // 这是加载服务器的私钥。在这个例子中，私钥也被包含在同一个"sself_sign/erver.pem"文件中，并且使用PEM格式编码。
        // context_.use_private_key_file("server.key", boost::asio::ssl::context::pem);
        context_.use_private_key_file("./boostssl/server.pem", boost::asio::ssl::context::pem);

        // 这是加载Diffie-Hellman参数文件。这些参数用于支持 ephemeral Diffie-Hellman key exchange，这是一种常见的安全协议，可以提供前向安全性。
        context_.use_tmp_dh_file("dh4096.pem");

        do_accept();
    }
private:
    std::string get_password() const
    {
        std::cout << "get passwd" << std::endl;
        // return "1111";
        return "test";
    }

    void do_accept()
    {
        acceptor_.async_accept([this](const boost::system::error_code& error, boost::asio::ip::tcp::socket socket) {
            if (!error) {
                // auto sslsocket = boost::asio::ssl::stream<boost::asio::ip::tcp::socket>(std::move(socket), context_);
                // std::make_shared<session>(std::move(sslsocket));
                auto&& r_sslsocket = // 左值
                    boost::asio::ssl::stream<boost::asio::ip::tcp::socket>(std::move(socket), context_);
                std::make_shared<session>(std::move(r_sslsocket));

                // std::make_shared<session>(
                //     boost::asio::ssl::stream<boost::asio::ip::tcp::socket>(std::move(socket), context_));
            }

            do_accept();
        });
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
// g++ main.cpp -lboost_system -std=c++11 -lpthread

#include <iostream>
#include <boost/asio.hpp>
#include <boost/format.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/log/trivial.hpp>
using namespace std;
//using namespace boost;
#define BF boost::format
#define BLOG BOOST_LOG_TRIVIAL(debug)
//#define BLOG(f) (BOOST_LOG_TRIVIAL(debug) << (f))
void callback1(const boost::system::error_code&)
{
    cout << "hello" << endl;
}
void callback2(const boost::system::error_code&)
{
    cout << "world" << endl;
}
int main()
{
    boost::asio::io_service io;
    //boost::asio::deadline_timer t(io, boost::posix_time::seconds(5));
    boost::asio::deadline_timer t(io);
    t.expires_from_now(boost::posix_time::seconds(5));
    t.async_wait(callback1);
    boost::asio::deadline_timer t2(io);
    t2.expires_from_now(boost::posix_time::seconds(3));
    t2.async_wait(callback2);

    cout << "run start" << endl;
    size_t n = io.run();
    cout << "runing n:" << n << endl;;
    cout << "run end" << endl;
    while (true);
    
    return 0;
}
int main01()
{
    boost::asio::io_service io;
    boost::asio::deadline_timer t(io,boost::posix_time::seconds(3));
    cout << t.expires_at() << endl;
    cout << t.expires_from_now() << endl;
    t.wait();
    std::cout << "hello " << std::endl;
    //BLOG << BF("hello");



    /*char a = 64;
    char b = a << 1;
    char c = b >> 1;
    BLOG << BF("%d") % a;
    printf("%X\n", a);
    printf("%X\n", b);
    printf("%X\n", c);*/


    while (true);
    
    return 0;
}
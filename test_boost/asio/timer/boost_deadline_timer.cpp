// g++ boost_deadline_timer.cpp -lboost_system -std=c++11 -lpthread

#include <iostream>
#include <boost/asio.hpp>
#include <boost/format.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/log/trivial.hpp>
#include <boost/thread.hpp>

using namespace std;
//using namespace boost;
// #define BF boost::format
// #define BLOG BOOST_LOG_TRIVIAL(debug)
//#define BLOG(f) (BOOST_LOG_TRIVIAL(debug) << (f))

void callback1(const boost::system::error_code&)
{
    cout << "Timer1 thread: " << boost::this_thread::get_id() << endl;

    cout << "hello" << endl;
}

void callback2(const boost::system::error_code&)
{
    cout << "Timer2 thread: " << boost::this_thread::get_id() << endl;

    cout << "world" << endl;
}

void test_deadline_timer_async()
{
    cout << "main thread: " << boost::this_thread::get_id() << endl;

    boost::asio::io_service io;
    boost::asio::deadline_timer t(io, boost::posix_time::seconds(5));
    // boost::asio::deadline_timer t(io);
    // t.expires_from_now(boost::posix_time::seconds(5));
    t.async_wait(callback1);

    boost::asio::deadline_timer t2(io);
    cout << t2.expires_at() << endl;
    cout << t2.expires_from_now(boost::posix_time::seconds(3)) << endl;
    t2.async_wait(callback2);

    cout << "run start" << endl;
    size_t n = io.run();
    cout << "runing n:" << n << endl;
    cout << "run end" << endl;
}

void test_deadline_timer_sync()
{
    boost::asio::io_service io;
    boost::asio::deadline_timer t(io, boost::posix_time::seconds(3));
    cout << t.expires_at() << endl;
    cout << t.expires_from_now() << endl;
    t.wait();
    std::cout << "hello" << std::endl;
    // BLOG << BF("hello");

    /*char a = 64;
    char b = a << 1;
    char c = b >> 1;
    BLOG << BF("%d") % a;
    printf("%X\n", a);
    printf("%X\n", b);
    printf("%X\n", c);*/
}

int main()
{
    // test_deadline_timer_sync();
    test_deadline_timer_async();

    return 0;
}
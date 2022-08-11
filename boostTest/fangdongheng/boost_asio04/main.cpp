#include <iostream>
#include <boost/asio.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread.hpp>

using namespace std;

class printer{
public:
    printer(boost::asio::io_service &io) :m_strand(io), m_timer1(io), m_timer2(io), m_count(0)
    { 
        cout << "printer()" << endl; 
        m_timer1.expires_from_now(boost::posix_time::seconds(2));
        m_timer1.async_wait(m_strand.wrap(boost::bind(&printer::print1, this, boost::asio::placeholders::error)));
        //m_timer1.async_wait((boost::bind(&printer::print1, this,boost::asio::placeholders::error)));
        m_timer2.expires_from_now(boost::posix_time::seconds(2));
        m_timer2.async_wait(m_strand.wrap(boost::bind(&printer::print2, this, boost::asio::placeholders::error)));
        //m_timer2.async_wait((boost::bind(&printer::print2, this,boost::asio::placeholders::error)));

    }
    ~printer(){ cout << "~printer()" << endl; }
    void print1(const boost::system::error_code &ec)
    {
        if (m_count < 10)
        {
            cout << "timer1:" << m_count << endl;
            ++m_count;

            m_timer1.expires_from_now(boost::posix_time::seconds(1));
            m_timer1.async_wait(m_strand.wrap(boost::bind(&printer::print1, this, boost::asio::placeholders::error)));
            //m_timer1.async_wait((boost::bind(&printer::print1, this, boost::asio::placeholders::error)));
        }

    }
    void print2(const boost::system::error_code &ec)
    {
        if (m_count < 10)
        {
            cout << "timer2:" << m_count << endl;
            ++m_count;

            m_timer2.expires_from_now(boost::posix_time::seconds(1));
            m_timer2.async_wait(m_strand.wrap(boost::bind(&printer::print2, this, boost::asio::placeholders::error)));
            //m_timer2.async_wait((boost::bind(&printer::print2, this, boost::asio::placeholders::error)));
        }
    }
private:
    boost::asio::io_service::strand m_strand;
    boost::asio::deadline_timer m_timer1;
    boost::asio::deadline_timer m_timer2;
    int m_count;
};
int main()
{
    boost::asio::io_service io;
    //boost::thread t(boost::bind(&boost::asio::io_service::run,&io));
    printer po(io);
    boost::thread t([&io](){
        cout << "thread io run start" << endl;
        io.run();
        cout << "thread io run end" << endl;
    });
    /*if (io.stopped())
    {
        io.reset();
    }*/
    io.run();
    t.join();
    boost::this_thread::sleep_for(boost::chrono::seconds(100));
    return 0;
}
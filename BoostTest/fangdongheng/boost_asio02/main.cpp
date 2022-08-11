#include <iostream>
#include <boost/asio.hpp>
#include <boost/format.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/log/trivial.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <boost/bind.hpp>
using namespace std;
//using namespace boost;
#define BF boost::format
#define BLOG BOOST_LOG_TRIVIAL(debug)

#if 0
void print(const boost::system::error_code & /* e*/,
    std::shared_ptr<boost::asio::deadline_timer> t/*boost::asio::deadline_timer *t*/, int *count) {
    cout << "t.use_count: "<< t.use_count() << endl;
    if (*count < 5) {
        std::cout << *count << std::endl;
        ++(*count);

        t->expires_at(t->expires_at() + boost::posix_time::seconds(1));
        t->async_wait([t, count](const boost::system::error_code &error) { print(error, t, count); });
    }
}

void callback(const boost::system::error_code& e) {
    std::cout << "hello world\n";
}

std::shared_ptr<boost::asio::deadline_timer>
registerPrint(boost::asio::io_service &io, int *count) {
    auto t = std::make_shared<boost::asio::deadline_timer>(
        io, boost::posix_time::seconds(1));
    //auto p = t.get();
    t->async_wait([t, count](const boost::system::error_code &error) { print(error, t, count); });
    return t;
}

int main() {
    boost::asio::io_service io;

    std::vector<int> v;
    for (int i = 0; i < 5; ++i) v.push_back(i);
    for (int i = 0; i < 5; ++i) {
        auto t = registerPrint(io, &v[i]);
        std::cout << "pointer address is: " << t.get() << std::endl;
    }
    io.run();
    for (int i = 0; i < 5; ++i)
        std::cout << "Final count is " << v[i] << std::endl;

    return 0;
}
#endif


#if 0
class timer_with_func : public boost::enable_shared_from_this<timer_with_func>
{
public:
    template<typename F>
    timer_with_func(boost::asio::io_service &io, int max, F func)
        :m_count(0), m_count_max(max), m_f(func),
        /*m_t(io, std::chrono::seconds(3))*/m_t(boost::make_shared<boost::asio::steady_timer>(io))
    { 
        std::cout << "timer_with_func()" << std::endl; 
        //m_t = boost::shared_ptr<boost::asio::steady_timer>(new boost::asio::steady_timer(io,std::chrono::seconds(3)));//true
        //m_t = boost::make_shared<boost::asio::steady_timer>(io);//true
        
        //m_t.expires_from_now(std::chrono::seconds(3));
        //m_t->expires_from_now(std::chrono::seconds(3));//true
        //m_t.reset(new boost::asio::steady_timer(io,std::chrono::seconds(3))); //true
        std::cout << "m_t.use_count: " << m_t.use_count() << std::endl;
        //init();
    }
    ~timer_with_func(){ std::cout << "~timer_with_func()" << std::endl; }
    

    void init()
    {
        //m_t.expires_from_now(std::chrono::seconds(3));
        //m_t.async_wait(boost::bind(&timer_with_func::handle, this, boost::asio::placeholders::error));
        m_t->expires_from_now(std::chrono::seconds(3));
        m_t->async_wait(boost::bind(&timer_with_func::handle, shared_from_this(),boost::asio::placeholders::error));
        //auto tmp = shared_from_this();
        //cout << tmp.use_count() << endl;

        //m_t->async_wait(boost::bind(&timer_with_func::handle, this, boost::asio::placeholders::error));
    }
private:
    void handle(const boost::system::error_code&)
    {
        if (++m_count >= m_count_max)
        {
            return;
        }
        std::cout << "m_count: " << m_count << std::endl;
        m_f();
        m_t->expires_from_now(std::chrono::seconds(3));
        //m_t->async_wait(boost::bind(&timer_with_func::handle, this, boost::asio::placeholders::error));
        m_t->async_wait(boost::bind(&timer_with_func::handle, shared_from_this(), boost::asio::placeholders::error));
        //cout << shared_from_this().use_count() << endl;
        //m_t.expires_from_now(std::chrono::seconds(2));
        //m_t.async_wait(boost::bind(&timer_with_func::handle, this, boost::asio::placeholders::error));
    }
    int m_count;
    int m_count_max;
    std::function<void()> m_f;
    boost::shared_ptr<boost::asio::steady_timer> m_t;
    //boost::asio::steady_timer m_t;
};
int main()
{
    boost::asio::io_service io;
    //boost::shared_ptr<boost::asio::io_service> spio = boost::make_shared<boost::asio::io_service>();
    /*{
    timer_with_func t1(io, 5, [](){std::cout << "timer1" << std::endl; });
    t1.init();
    }*/
    {
        //timer_with_func t1(io, 5, [](){std::cout << "timer1" << std::endl; });
        boost::shared_ptr<timer_with_func> t1(new timer_with_func(io, 5, [](){std::cout << "timer1" << std::endl; }));
        t1->init();
        //std::cout << "t1.use_count:: " << t1.use_count() << std::endl;
        boost::shared_ptr<timer_with_func> t2(new timer_with_func(io, 5, [](){std::cout << "timer2" << std::endl; }));
        t2->init();

    }
    std::cout << "-----------------" << std::endl;

    io.run();
    boost::this_thread::sleep_for(boost::chrono::seconds(10));
    //while (1);
    return 0;
}

#endif
#if 1
class timer_with_func : public boost::enable_shared_from_this<timer_with_func>
{
public:
    template<typename F>
    timer_with_func(int max, F func)
        :m_count(0), m_count_max(max), m_f(func), io(new boost::asio::io_service),
        /*m_t(io, std::chrono::seconds(3))*/m_t(boost::make_shared<boost::asio::steady_timer>(*io))
    {
        std::cout << "timer_with_func()" << std::endl;
       
        std::cout << "m_t.use_count: " << m_t.use_count() << std::endl;
        //init();
    }
    ~timer_with_func(){ std::cout << "~timer_with_func()" << std::endl; }


    void init()
    {
        //m_t.expires_from_now(std::chrono::seconds(3));
        //m_t.async_wait(boost::bind(&timer_with_func::handle, this, boost::asio::placeholders::error));
        m_t->expires_from_now(std::chrono::seconds(3));
        m_t->async_wait(boost::bind(&timer_with_func::handle, shared_from_this(), boost::asio::placeholders::error));
        //auto tmp = shared_from_this();
        //cout << tmp.use_count() << endl;

        //m_t->async_wait(boost::bind(&timer_with_func::handle, this, boost::asio::placeholders::error));
    }
    void run()
    {
        io->run();
    }
private:
    void handle(const boost::system::error_code&)
    {
        if (++m_count >= m_count_max)
        {
            return;
        }
        std::cout << "m_count: " << m_count << std::endl;
        m_f();
        m_t->expires_from_now(std::chrono::seconds(1));
        //m_t->async_wait(boost::bind(&timer_with_func::handle, this, boost::asio::placeholders::error));
        m_t->async_wait(boost::bind(&timer_with_func::handle, shared_from_this(), boost::asio::placeholders::error));
        //cout << shared_from_this().use_count() << endl;
        //m_t.expires_from_now(std::chrono::seconds(2));
        //m_t.async_wait(boost::bind(&timer_with_func::handle, this, boost::asio::placeholders::error));
    }

    boost::shared_ptr<boost::asio::io_service> io;
    int m_count;
    int m_count_max;
    std::function<void()> m_f;
    boost::shared_ptr<boost::asio::steady_timer> m_t;
    //boost::asio::steady_timer m_t;

};


int main()
{
    //boost::asio::io_service io;
    //boost::shared_ptr<boost::asio::io_service> spio = boost::make_shared<boost::asio::io_service>();
    /*{
        timer_with_func t1(io, 5, [](){std::cout << "timer1" << std::endl; });
        t1.init();
    }*/
    {
        //timer_with_func t1(io, 5, [](){std::cout << "timer1" << std::endl; });
        boost::shared_ptr<timer_with_func> t1(new timer_with_func(5, [](){std::cout << "timer1" << std::endl; }));
        t1->init();
        t1->run();

        //std::cout << "t1.use_count:: " << t1.use_count() << std::endl;
        boost::shared_ptr<timer_with_func> t2(new timer_with_func(5, [](){std::cout << "timer2" << std::endl; }));
        t2->init();

        t2->run();
    }
    std::cout << "-----------------" << std::endl;

    //io.run();
    boost::this_thread::sleep_for(boost::chrono::seconds(10));
    //while (1);
    return 0;
}

#endif
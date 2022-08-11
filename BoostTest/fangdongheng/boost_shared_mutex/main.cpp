#include <iostream>
#include <boost/thread.hpp>
#include <boost/ref.hpp>
//#include <boost/thread/mutex.hpp>
#include <boost/log/trivial.hpp>
//#include <boost/thread/lock_factories.hpp>
using namespace std;
using namespace boost;

//boost::shared_mutex gs_mutex;
/*boost::lock_guard<boost::shared_mutex> w1lock(gs_mutex);
boost::unique_lock<boost::shared_mutex> wlock(gs_mutex);
boost::shared_lock<boost::shared_mutex> rlock(gs_mutex);*/
//boost::shared_lock<boost::shared_mutex> rlock1 = make_shared_lock();
class rw_data
{
public:
    rw_data() :m_rwdata(0){};
    ~rw_data(){};
    void write()
    {
        boost::unique_lock<boost::shared_mutex> wlock(m_smutex);
        ++m_rwdata;
    }
    void read(int *x)
    {
        boost::shared_lock<boost::shared_mutex> rlock(m_smutex);
        *x = m_rwdata;
    }
private:
    int m_rwdata;
    boost::shared_mutex m_smutex;
};

void reader(rw_data &rw)
{
    int x = 0;
    for (int i = 0; i < 12;++i)
    {
        rw.read(&x);
        //std::cout << "id: "<< this_thread::get_id() << " read x: " << x << std::endl;
        BOOST_LOG_TRIVIAL(debug) << "id: " << this_thread::get_id() << " read x: " << x ;
        this_thread::sleep_for(boost::chrono::seconds(1));

    }
}

void writer(rw_data &rw)
{
    for (int i = 0; i < 10;++i)
    {
        //std::cout << "write" << std::endl;
        BOOST_LOG_TRIVIAL(debug) << "id: " << this_thread::get_id() << " write";
        rw.write();
        this_thread::sleep_for(boost::chrono::seconds(1));
    }
}
int main()
{
    rw_data rwdata;
    thread_group pool;
    pool.create_thread(boost::bind(&writer,boost::ref(rwdata)));
    //pool.create_thread(boost::bind(&writer,boost::ref(rwdata)));
    //pool.create_thread(boost::bind(&writer, rwdata));

    pool.create_thread(boost::bind(&reader, boost::ref(rwdata)));
    pool.create_thread(boost::bind(&reader, boost::ref(rwdata)));
    pool.create_thread(boost::bind(&reader, boost::ref(rwdata)));

    pool.join_all();
    this_thread::sleep_for(boost::chrono::minutes(10));
    return 0;
}
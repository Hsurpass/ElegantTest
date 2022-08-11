#include <iostream>
#include <boost/thread.hpp>
#include <condition_variable>
//#include <boost/thread/lock_types.hpp>
//#include <boost/thread/locks.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/lock_factories.hpp>
#include <stack>
#include <boost/chrono.hpp>
using namespace std;
using namespace boost;


#if 0
boost::mutex g_mutex;
boost::condition_variable cv;
bool ready = false;
void func(int id)
{
    boost::unique_lock<boost::mutex> lck(g_mutex);
    while (!ready) {
        cv.wait(lck);
    }
    cout << "thread id: " << this_thread::get_id() << "id: " << id << endl;

}
int main()
{
    boost::thread th[10];
    for (int i = 0; i < 10; ++i)
    {
        th[i] = boost::thread(&func, i);
    }

    this_thread::sleep_for(boost::chrono::seconds(3));
    ready = true;
    cv.notify_all();

    for (auto &v : th)
    {
        v.join();
    }
    this_thread::sleep_for(boost::chrono::minutes(10));
    return 0;
}
#endif

class buffer
{
public:
    buffer(int n) :m_count(0), m_capacity(n)
    {
    }

    ~buffer()
    {
    }
    bool isfull()
    {
        return m_count == m_capacity;
    }
    bool isempty()
    {
        return m_count == 0;
    }
    void get(int *x)
    {
        {
            auto lockget = boost::make_unique_lock(m_mutex);
            //cond_get.wait(lockget, !boost::bind(&buffer::isempty,this));
            while (isempty())
            {
                cond_get.wait(lockget);
            }
            *x = stk.top();
            stk.pop();
            --m_count;
        }
        cond_put.notify_one();
    }
    void put(int i)
    {
        {
            //boost::lock_guard<boost::mutex> lock1(m_mutex);
            //boost::unique_lock<boost::mutex> lockput(m_mutex);
            //boost::unique_lock<boost::mutex> lockput = boost::make_unique_lock(m_mutex);
            auto lockput = boost::make_unique_lock(m_mutex);
            //cond_put.wait(lockput,!isfull());       //error
            //cond_put.wait(lockput, !boost::bind(&buffer::isfull,this));
            while (isfull())
            {
                cond_put.wait(lockput);
            }
            stk.push(i);
            ++m_count;
        }
        cond_get.notify_one();
    }

private:
    stack<int> stk;
    int m_count; 
    int m_capacity;
    boost::mutex m_mutex;
    boost::condition_variable cond_put;
    boost::condition_variable cond_get;
};
void producer(buffer& buf,int n)
{
    for (int i = 0; i < n;++i)
    {
        cout << "thread id: " <<boost::this_thread::get_id()<< " put i: " << i << endl;
        buf.put(i);
        boost::this_thread::sleep_for(boost::chrono::seconds(1));
    }
}
void consumer(buffer &buf,int n)
{
    int x = 0;
    for (int i = 0; i < n;++i)
    {
        buf.get(&x);
        cout << "thread id: " << boost::this_thread::get_id() << " get x: " << x << endl;
        boost::this_thread::sleep_for(boost::chrono::seconds(1));
    }
}

void func1()
{

}
int main02()
{
    boost::thread_group g;
    g.create_thread(&func1);
    g.create_thread(&func1);
    g.create_thread(&func1);
    g.create_thread(&func1);

    g.join_all();
    return 0;
}
int main()
{
    buffer buff(5);
    boost::thread_group group;
    group.create_thread(boost::bind(&producer, boost::ref(buff), 10));
    group.create_thread(boost::bind(&consumer, boost::ref(buff), 5));
    group.create_thread(boost::bind(&consumer, boost::ref(buff), 5));

    //boost::thread product(&producer,boost::ref(buff),10);
    //boost::thread consume1(&consumer, boost::ref(buff), 5);
    //boost::thread consume2(&consumer, boost::ref(buff), 5);

    group.join_all();
    boost::this_thread::sleep_for(boost::chrono::minutes(1));
    return 0;
}
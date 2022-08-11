#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
using namespace std;
std::mutex g_mutex;
std::condition_variable cv;
bool ready = false;
void func(int id)
{
    unique_lock<mutex> lck(g_mutex);
    while (!ready) {
        cv.wait(lck);
    }
    cout << "thread id: " << this_thread::get_id() << "id: " << id << endl;

}
int main()
{
    thread th[10];
    for(int i = 0;i < 10;++i)
    {
        th[i] = thread(&func,i);
    }

    this_thread::sleep_for(chrono::seconds(3));
    ready = true;
    cv.notify_all();

    for(auto &v:th)
    {
        v.join();
    }

    return 0;
}

#if 0
std::mutex g_mutex;
std::condition_variable cv_pro,cv_cons;
int cargo = 0;
void producer(int n)
{
    unique_lock<mutex> lockpro(g_mutex);
    while (cargo != 0) {
        cv_pro.wait(lockpro);
    }
    cargo = n;
    cv_cons.notify_one();
}
void consumer()
{
    unique_lock<mutex> lockcon(g_mutex);
    while (cargo == 0) {
        cv_cons.wait(lockcon);
    }
    cout << cargo << endl;
    cargo = 0;
    cv_pro.notify_one();
}
int main()
{
    thread produc[10],consu[10];
    for(int i = 0;i < 10;++i)
    {
        produc[i] = thread(&producer,i+1);
        consu[i] = thread(&consumer);
    }
    for(int i = 0;i < 10;++i)
    {
        produc[i].join();
        consu[i].join();
    }

    return 0;
}
#endif

#if 0
int cargo = 0;
bool shipment_available(){return cargo != 0;}
void consumer(int n)
{
    for(int i = 0;i < n;++i)
    {
        std::unique_lock<std::mutex> lck(g_mutex);
        cv.wait(lck,shipment_available);
        cout << cargo << endl;
        cargo = 0;
    }
}
int main()
{
    thread consumer_th(&consumer,10);

    for(int i = 0;i < 10;++i)
    {
        while(shipment_available()) this_thread::yield();
        std::unique_lock<std::mutex> lck(g_mutex);
        cargo = i+1;
        cv.notify_one();
    }

    consumer_th.join();
    return 0;
}
#endif

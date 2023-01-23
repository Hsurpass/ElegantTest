#include <iostream>
#include <sys/timeb.h>
#include <thread>
#include <mutex>

std::mutex mtx;
using namespace std;
#define TIME 10000000
volatile int counter(0);

void threadAddUseMutexTryLock()
{
#if 1
    while (!mtx.try_lock())
    {
        // cout << this_thread::get_id() << "xxxxxxxxxx" << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));

    }
    cout << this_thread::get_id() << " get mutex" << endl;
#endif
    
    // mtx.try_lock();
    for (int i = 0; i < 100000; ++i)
    {
        // mtx.try_lock();
        counter++;
        // mtx.unlock();
    }

    //    throw 10;
    mtx.unlock();
}

void threadAddUseMutexLock()
{
    cout << this_thread::get_id() << "xxxxxxxxxx" << endl;

    for (int i = 0; i < 100000; ++i)
    {
        mtx.lock();     // 如果把unlock()放在循环外面 死锁
        counter++;
        // mtx.unlock();
    }
    // throw 10;
    mtx.unlock();
}

void test_multiThread_add()
{
    thread t[10];

    for (int i = 0; i < 10; i++)
    {
        // t[i] = thread(threadAddUseMutexLock);
        t[i] = thread(threadAddUseMutexTryLock);
    }

    for (auto &k : t)
    {
        k.join();
    }
    cout << "counter: " << counter << endl;
}

int main()
{
    test_multiThread_add();

    return 0;
}

#if 0
long long getsystemtime()
{
    struct timeb t;
    ftime(&t);
    return 1000*t.time + t.millitm;
}

int main()
{
    long long start,end;
    start = getsystemtime();
    for(int i = 0;i < TIME;i++);
    end = getsystemtime();
//    cout << "一般变量用时: " << end - start << endl;
    printf("yiban变量用时: %lld ms\n", end - start);

    long long start1,end1;
    start1 = getsystemtime();
    for(volatile int i = 0;i < TIME;i++);
    end1 = getsystemtime();
    printf("volatitle变量用时: %lld ms\n", end1 - start1);

    return 0;
}
#endif

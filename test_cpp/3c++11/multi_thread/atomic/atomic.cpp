#include <iostream>
#include <atomic>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

#if 0
std::mutex mtx;
int count = 0;
#endif

#if 0
int count = 0;
#endif

#if 1
std::atomic<int> count(0);
#endif

void add()
{
    for (int i = 0;i < 5000000; i++)
    {
        #if 0
        std::lock_guard<mutex> lock(mtx);
        count += 1;
        #endif

        #if 0   // int count = 0;
        // __sync_add_and_fetch(&count, 1);
        __sync_fetch_and_add(&count, 1);
        #endif

        #if 1   //std::atomic<int> count(0);
        // std::atomic_fetch_add(&count, 1);
        ++count;
        #endif
    }
}

void test_atomic_and_mutex_performance()
{
    std::chrono::steady_clock::time_point time1 = chrono::steady_clock::now();
    std::thread t1(&add);
    std::thread t2(&add);

    t1.join();
    t2.join();

    cout << "count: " << count << endl;
    std::chrono::steady_clock::time_point time2 = chrono::steady_clock::now();
    chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(time2 - time1);
    cout << time_span.count() << " seconds" << endl;
}

void test_atomic_direct_assignment()
{
    // std::atomic<int> val = 99;
    // printf("%d\n", (int)value);
}

int main()
{
    test_atomic_and_mutex_performance();
    // test_atomic_direct_assignment();

    return 0;
}
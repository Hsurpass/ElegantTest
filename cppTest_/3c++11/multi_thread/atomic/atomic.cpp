#include <iostream>
#include <atomic>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;
std::mutex mtx;
int count = 0;
// std::atomic<int> count(0);

void add()
{
    for (int i = 0;i < 500000; i++)
    {
        std::lock_guard<mutex> lock(mtx);
        count += 1;

        // __sync_add_and_fetch(&count, 1);
        // __sync_fetch_and_add(&count, 1);
        // std::atomic_fetch_add(&count, 1);
    }
}

int main()
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

    return 0;
}
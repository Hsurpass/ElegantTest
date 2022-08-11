#include <iostream>
#include <mutex>
#include <thread>

using namespace std;
std::mutex mutex1, mutex2;

void task1()
{
#if 0
    // solve dead lock
    std::lock(mutex1, mutex2);
    cout << "task1 lock mutex1 mutex2" << endl;
    std::lock_guard<std::mutex> lock1(mutex1, adopt_lock);
    std::this_thread::sleep_for(std::chrono::seconds(1));    
    std::lock_guard<std::mutex> lock2(mutex2, adopt_lock);
#endif

// simulate dead lock
#if 1
    std::lock_guard<std::mutex> lock1(mutex1);
    std::this_thread::sleep_for(std::chrono::seconds(1));    
    std::lock_guard<std::mutex> lock2(mutex2);
#endif

    cout << "task1" << endl;

}

void task2()
{
#if 0
    // solve dead lock
    std::lock(mutex1, mutex2);
    cout << "task2 lock mutex1 mutex2" << endl;

    std::lock_guard<std::mutex> lock1(mutex1, adopt_lock);
    std::lock_guard<std::mutex> lock2(mutex2, adopt_lock);
#endif

// simulate dead lock
#if 1
    std::lock_guard<std::mutex> lock2(mutex2);
    std::lock_guard<std::mutex> lock1(mutex1);
#endif

    cout << "task2" << endl;

}

void deadLock_multithread()
{
    std::thread t1(task1);
    std::thread t2(task2);

    t1.join();
    t2.join();
}

int main()
{
    deadLock_multithread();

    return 0;
}
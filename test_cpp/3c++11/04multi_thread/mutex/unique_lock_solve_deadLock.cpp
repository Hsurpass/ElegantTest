#include <iostream>
#include <mutex>
#include <thread>

using namespace std;
std::mutex mutex1, mutex2;


void task1()
{
#if 1
    std::unique_lock<std::mutex> lock1(mutex1, std::defer_lock);
    std::unique_lock<std::mutex> lock2(mutex2, std::defer_lock);
    std::lock(lock1, lock2);
#endif
#if 0
    std::lock(mutex1, mutex2);
    std::unique_lock<std::mutex> lock1(mutex1, std::adopt_lock);
    std::unique_lock<std::mutex> lock2(mutex2, std::adopt_lock);
#endif

    cout << "task1 lock mutex1 mutex2" << endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));    

// simulate dead lock
#if 0
    std::lock_guard<std::mutex> lock1(mutex1);
    // std::this_thread::sleep_for(std::chrono::seconds(1));    
    std::lock_guard<std::mutex> lock2(mutex2);
#endif

    cout << "task1" << endl;

}

void task2()
{
#if 0
    std::unique_lock<std::mutex> lock1(mutex1, std::defer_lock);
    std::unique_lock<std::mutex> lock2(mutex2, std::defer_lock);
    std::lock(lock1, lock2);
#endif
#if 1
    std::lock(mutex1, mutex2);
    std::lock_guard<std::mutex> lock1(mutex1, std::adopt_lock);
    std::unique_lock<std::mutex> lock2(mutex2, std::adopt_lock);
#endif
    cout << "task2 lock mutex1 mutex2" << endl;

// simulate dead lock
#if 0
    std::lock_guard<std::mutex> lock2(mutex2);
    std::lock_guard<std::mutex> lock1(mutex1);
#endif

    cout << "task2" << endl;

}

void deadLock_multithread()
{
    std::thread t2(task2);
    std::thread t1(task1);

    t1.join();
    t2.join();
}

int main()
{
    deadLock_multithread();

    return 0;
}
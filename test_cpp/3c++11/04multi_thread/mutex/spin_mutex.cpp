#include <iostream>
#include <thread>
#include <chrono>
#include <pthread.h>
#include "spin_mutex.h"

using namespace std;

SpinMutex mtx;
void func()
{
    SpinLockGuard lock(mtx);
    std::cout << "thread[" << std::this_thread::get_id() << "] [" << pthread_self() << "]get lock" << endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));
}

void test_spin_mutex()
{
    std::thread t1(func);
    std::thread t2(func);

    t1.join();
    t2.join();
}

int main()
{
    test_spin_mutex();
    return 0;
}
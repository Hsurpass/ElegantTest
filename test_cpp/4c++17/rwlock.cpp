#include <cstdio>
#include <iostream>
#include <shared_mutex>
#include <thread>
#include <functional>
#include <chrono>
#include <stdio.h>

using namespace std;

int g_count = 0;
std::shared_mutex rwlock;

void set_count()
{
    {
        std::shared_lock<std::shared_mutex> lock(rwlock);
        g_count++;
        printf("set_count thread id: %ld, count: %d\n", std::this_thread::get_id(), g_count);
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

void get_count()
{
    {
        std::shared_lock<std::shared_mutex> lock(rwlock);
        printf("get_count thread id: %ld, count: %d\n", std::this_thread::get_id(), g_count);
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    {
        std::shared_lock<std::shared_mutex> lock(rwlock);
        printf("get_count thread id: %ld, count: %d\n", std::this_thread::get_id(), g_count);
    }
}

void test_shared_mutex()
{
    std::thread t1(get_count);
    thread t2(get_count);

    thread t3(set_count);

    t1.join();
    t2.join();
    t3.join();
}

int main()
{
    test_shared_mutex();

    return 0;
}
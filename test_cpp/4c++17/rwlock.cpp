#include <cstdio>
#include <iostream>
#include <mutex>
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
        // printf("set_count thread id: %lu, count: %d\n", std::this_thread::get_id(), g_count);
        // std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

void get_count()
{
    {
        std::shared_lock<std::shared_mutex> lock(rwlock);
        printf("get_count thread id: %lu, count: %d\n", std::this_thread::get_id(), g_count);
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    {
        std::shared_lock<std::shared_mutex> lock(rwlock);
        printf("get_count thread id: %lu, count: %d\n", std::this_thread::get_id(), g_count);
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

void add()
{
    // std::shared_lock不能保证多线程写入导致的资源竞争。要使用std::lock_guard
    // std::shared_lock<std::shared_mutex> lock(rwlock);

    // 使用lock_guard或unique_lock管理写锁，使用shared_lock管理读锁
    // std::lock_guard<std::shared_mutex> lock(rwlock);
    std::unique_lock<std::shared_mutex> lock(rwlock);

    for (int i = 0; i < 100000; i++) {
        g_count++;
    }
}

void test_multithread_set()
{
    const int n = 100;
    std::thread t[n];
    for (int i = 0; i < n; i++) {
        t[i] = std::thread(std::bind(add));
    }

    for (auto& x : t) {
        x.join();
    }

    cout << g_count << endl;
}

int main()
{
    // test_shared_mutex();
    test_multithread_set();

    return 0;
}
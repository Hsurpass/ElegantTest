#include <iostream>
#include <thread>
#include <memory>
#include <functional>
#include <stdio.h>
#include <unistd.h>
#include <atomic>

// std::atomic<std::ostream> mycout;

using namespace std;
using namespace placeholders;

class Thread
{
public:
    Thread()
    {
    }

    ~Thread()
    {
    }

    void Start()
    {
        m_stopped = false;
        //threadFunc 是类的非静态方法，因此作为线程函数，第一个参数必须传递类实例地址，即 this 指针
        m_spThread.reset(new std::thread(&Thread::threadFunc, this, 8888, 9999));
    }

    void Stop()
    {
        m_stopped = true;
        if (m_spThread)
        {
            if (m_spThread->joinable())
                m_spThread->join();
        }
    }

    void *stopThreadMemFunc(void *arg)
    {
        cout << "stop thread id:" << std::this_thread::get_id() << endl;
        // Thread *mythread = (Thread *)arg;
        int count = 0;
        while (count < 10)
        {
            sleep(1);
            count++;
        }

        this->Stop();
        // mythread->Stop();
    }

private:
    void threadFunc(int arg1, int arg2)
    {
        while (!m_stopped)
        {
            sleep(1);
            printf("Thread function use instance method, arg1:%d, arg2:%d, counter:%d.\n", arg1, arg2, m_counter++);
        }
    }

private:
    std::shared_ptr<std::thread> m_spThread;
    bool m_stopped;
    int m_counter = 0;
};

void test_thread_sharedPtr()
{
    Thread mythread;
    mythread.Start();

    int count = 0;
    while (count < 10)
    {
        sleep(1);
        count++;
    }
    mythread.Stop();
}

void *stopThreadFunc(void *arg)
{
    cout << "stop thread id:" << std::this_thread::get_id() << endl;
    Thread *mythread = (Thread *)arg;
    int count = 0;
    while (count < 10)
    {
        sleep(1);
        count++;
    }

    mythread->Stop();
}

void test_thread_sharedPtr_with_two_thread_global_func()
{
    Thread mythread;
    mythread.Start();

    std::thread stopThread(stopThreadFunc, &mythread);

    if (stopThread.joinable())
    {
        stopThread.join();
    }
}

void test_thread_sharedPtr_with_two_thread_mem_func()
{
    Thread mythread;
    mythread.Start();

    // auto f = bind(&Thread::stopThreadMemFunc, &mythread, &mythread);
    // auto f = bind(&Thread::stopThreadMemFunc, &mythread, nullptr);
    // std::thread stopThread(f);
    // std::thread stopThread(&Thread::stopThreadMemFunc, &mythread, nullptr);
    std::thread stopThread([&mythread](){ mythread.stopThreadMemFunc(nullptr);} );

    if (stopThread.joinable())
    {
        stopThread.join();
    }
}

int main()
{
    // test_thread_sharedPtr();
    // test_thread_sharedPtr_with_two_thread_global_func();
    test_thread_sharedPtr_with_two_thread_mem_func();

    return 0;
}
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <thread>
#include <vector>

// std::condition_variable之所以使用unique_lock，是因为 cv.wait内部要进行lock/unlock的操作
// lock_guard只有简单地构造析构接口，unique_lock是lock_guard的超集


using namespace std;
std::mutex mutex1;
std::condition_variable cv;
bool ready = false;
int condition = 0;

void printThreadId()
{
    std::unique_lock<mutex> lock(mutex1);
#if 0
    while (!ready)
    {
        cv.wait(lock);
    }
#endif
#if 1
    cv.wait(lock, []()
            { return ready; });
#endif

    cout << "thread id:" << this_thread::get_id() << ", awakened and get lock" << endl;
    this_thread::sleep_for(chrono::seconds(1));
}

void test_condition_variable01()
{
    std::vector<std::thread> tg;
    int N = 1;
    tg.reserve(N);
    for (size_t i = 0; i < N; i++)
    {
        tg.emplace_back(printThreadId);
    }

    for(auto &i:tg)
    {
        i.detach(); // cv是全局变量，即使detach后还是能接收到信号的。
    }

    this_thread::sleep_for(chrono::seconds(3));
    {
        unique_lock<mutex> lock(mutex1);
        ready = true;
    }
    cv.notify_all();

    cout << "----------join----------" << endl;
    for (auto &p : tg)
    {
        if (p.joinable())
        {
            cout << "joinable" << endl;
            p.join();
        }
        else
        {
            cout << "not joinable" << endl;
        }
    }
    this_thread::sleep_for(chrono::seconds(2));
}

void printId()
{
    while (1)
    {
        {
            std::unique_lock<mutex> lock(mutex1);
#if 0
    while (condition <= 0)
    {
        cv.wait(lock);
    }
#endif
#if 1
            cv.wait(lock, []()
                    { return condition > 0; });
#endif
            condition--;
        }
        cout << "thread id:" << this_thread::get_id() << ", awakened and get lock, condition:" << condition << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }
}

void test_condition_variable_spuriousWakeUp()
{
    std::vector<std::thread> tg;
    tg.reserve(5);
    for (size_t i = 0; i < 5; i++)
    {
        tg.emplace_back(printId);
    }

    this_thread::sleep_for(chrono::seconds(3));
    while (1)
    {
        cout << "main thread ++" << endl;
        {
            unique_lock<mutex> lock(mutex1);
            condition++;
        }
        // cv.notify_all();
        cv.notify_one();
        this_thread::sleep_for(chrono::seconds(2));
    }

    cout << "----------join----------" << endl;
    for (auto &p : tg)
    {
        if (p.joinable())
        {
            p.join();
        }
    }
}

int main()
{
    test_condition_variable01();
    // test_condition_variable_spuriousWakeUp();

    return 0;
}
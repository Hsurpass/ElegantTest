#include <chrono>
#include <iostream>
#include <future>
#include <thread>
#include <string>

using namespace std;

string task()
{
    // std::this_thread::sleep_for(std::chrono::seconds(5));
    cout << "threadid[" << std::this_thread::get_id() << "] quary data" << endl;
    return "dbdata";
}

void test_async_future()
{
    std::future<string> result = std::async(std::launch::async, task);  // 另外一个线程执行
    // std::future<string> result = std::async(std::launch::deferred, task);    // 直到get函数调用的时候才执行(在同一个线程执行)
    // std::future<string> result = std::async(std::launch::deferred | std::launch::async, task);  // 默认

    cout << "main thread[" << std::this_thread::get_id() << "] run task" << endl;

    // std::shared_future<int> r1;
    // r1.get();

    // std::this_thread::sleep_for(std::chrono::seconds(5));

    string r = result.get();
    cout << "db result" << r << endl;
    
    // while (1) {
    //     std::future_status futurestatus = result.wait_for(std::chrono::seconds(0));
    //     cout << "futurestatus: " << (int)futurestatus << endl;
    //     if (!(bool)futurestatus) {
    //         cout << "futurestatus: " << (int)futurestatus << ", result: " << result.get() << endl;
    //         break;
    //     }
    //     std::this_thread::sleep_for(std::chrono::seconds(1));
    // }
}

int main()
{
    test_async_future();

    return 0;
}
#include <chrono>
#include <iostream>
#include <future>
#include <thread>
#include <string>

using namespace std;

string task()
{
    cout << "threadid[" << std::this_thread::get_id() << "] quary data" << endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));
    return "dbdata";
}

void test_async_future()
{
    // std::future<string> result = std::async(std::launch::async, task);
    // std::future<string> result = std::async(std::launch::deferred, task);
    std::future<string> result = std::async(std::launch::deferred | std::launch::async, task);  // 默认

    cout << "main thread[" << std::this_thread::get_id() << "] run task" << endl;

    // string r = result.get();
    // cout << "db result" << r << endl;
    while (1) {
        std::future_status futurestatus = result.wait_for(std::chrono::seconds(0));
        cout << "futurestatus:" << (int)futurestatus << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main()
{
    test_async_future();

    return 0;
}
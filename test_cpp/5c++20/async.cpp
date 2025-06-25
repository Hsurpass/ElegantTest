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
    // 启动异步任务
    std::future<string> result = std::async(std::launch::async, task);  // 另外一个线程执行
    // 函数不会立即执行，而是等你调用 future.get() 或 future.wait() 时才在当前线程中执行。这种策略适合不确定是否需要执行任务的场景。
    // std::future<string> result = std::async(std::launch::deferred, task);    // 直到get函数调用的时候才执行(在同一个线程执行)
    // - 默认策略是 std::launch::async | std::launch::deferred，实现可以选择立即执行或延迟执行。
    // - 如果你不指定策略，行为是实现定义的（不同编译器可能不同）。
    // - 异常会自动从子线程传播到主线程，通过 future.get() 抛出。
    // std::future<string> result = std::async(std::launch::deferred | std::launch::async, task);  // 默认

    cout << "main thread[" << std::this_thread::get_id() << "] run task" << endl;

    // std::shared_future<int> r1;
    // r1.get();

    // std::this_thread::sleep_for(std::chrono::seconds(5));

    // 阻塞当前线程，直到异步任务完成并返回结果
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
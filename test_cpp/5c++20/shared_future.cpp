#include <chrono>
#include <cstdio>
#include <future>
#include <iostream>
#include <ratio>

using namespace std;

void test_shared_future()
{
    std::promise<void> ready_promise, t1_ready_promise, t2_ready_promise;
    std::shared_future<void> ready_future(ready_promise.get_future());

    std::chrono::time_point<chrono::high_resolution_clock> start;

    auto fun1 = [&, ready_future]() -> chrono::duration<double, std::milli> {
        t1_ready_promise.set_value();
        printf("fun1 wait ready_future\n");
        ready_future.wait(); // 等待来自main()的信号
        printf("fun1 finish wait ready_future\n");
        return std::chrono::high_resolution_clock::now() - start;
    };

    auto fun2 = [&, ready_future]() -> chrono::duration<double, std::milli> {
        t2_ready_promise.set_value();
        printf("fun2 wait ready_future\n");
        ready_future.wait(); // 等待来自main()的信号
        printf("fun2 finish wait ready_future\n");
        return std::chrono::high_resolution_clock::now() - start;
    };

    auto fut1 = t1_ready_promise.get_future();
    auto fut2 = t2_ready_promise.get_future();

    auto result1 = std::async(std::launch::async, fun1);
    auto result2 = std::async(std::launch::async, fun2);

    // 等待线程变为就绪
    printf("wait fut1 fut2\n");
    fut1.wait();
    fut2.wait();
    printf("finish wait fut1 fut2\n");

    // 线程已就绪，开始时钟
    start = chrono::high_resolution_clock::now();

    // 向线程发送信号使之运行
    ready_promise.set_value();
    printf("ready_promise.set_value\n");

    printf("线程 1 启动 %lfms 后接到信号\n", result1.get().count());
    printf("线程 2 启动 %lfms 后接到信号\n", result2.get().count());
}

int main()
{
    test_shared_future();

    return 0;
}
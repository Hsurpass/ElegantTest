#include <thread>
#include <future>
#include <functional>
#include <iostream>

using namespace std;

int f(int x, int y)
{
    return x + y;
}

void test_normal_func()
{
    std::packaged_task<int(int, int)> task(f);
    std::future<int> result = task.get_future();

    std::thread t(std::move(task), 2, 10);
    t.join();

    cout << "result: " << result.get() << endl;
}

void test_lambda()
{
    std::packaged_task<int(int, int)> task([](int a, int b) {
        return a + b;
    });
    std::future<int> result = task.get_future();

    // std::packaged_task 是 non-copyable 的，不能直接传递给线程
    // std::packaged_task 可以通过 std::move 转移所有权
    // std::thread t(std::move(task), 2, 10);
    // std::thread t(task, 2, 10); // error
    // t.join();

    // std::packaged_task::operator() 的返回类型是 void，它不会直接返回任务结果。
    // 那么这个值去哪儿了？它被 设置到了内部的共享状态中，你要通过 std::future 去取它：
    task(1, 2);

    cout << "result: " << result.get() << endl;
}

void test_bind()
{
    std::packaged_task<int(int, int)> task(std::bind(f, 2, 10));
    std::future<int> result = task.get_future();

    std::thread t(std::move(task), 2, 10);
    t.join();

    cout << "result: " << result.get() << endl;
}

// std::promise 存储一个值
// std::packaged_task 封装一个函数
// std::packaged_task 是 non-copyable 的，不能直接传递给线程
// std::packaged_task 可以通过 std::move 转移所有权
int main()
{
    // test_normal_func();
    // test_lambda();
    // test_bind();

    // std::packaged_task::operator() 的返回类型是 void，它不会直接返回任务结果。
    // 那么这个值去哪儿了？它被 设置到了内部的共享状态中，你要通过 std::future 去取它
    std::packaged_task<int()> t([] {
        return 42;
    });
    t();
    auto f = t.get_future();
    std::cout << "packaged_task result: " << f.get() << std::endl;

    return 0;
}
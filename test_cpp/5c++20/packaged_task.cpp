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

    std::thread t(std::move(task), 2, 10);
    t.join();

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

int main()
{
    // test_normal_func();
    // test_lambda();
    test_bind();

    return 0;
}
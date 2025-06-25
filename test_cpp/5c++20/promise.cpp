#include <chrono>
#include <iostream>
#include <future>
#include <thread>
#include <string>
#include <memory>
#include <utility>

using namespace std;

void set_value(std::promise<int> prom)
{
    cout << "threadid[" << std::this_thread::get_id() << "] set data" << endl;
    prom.set_value(100);

    std::this_thread::sleep_for(std::chrono::seconds(3));

    cout << "threadid[" << std::this_thread::get_id() << "] end" << endl;
}

void set_val(std::shared_ptr<std::promise<int>> prom)
{
    cout << "threadid[" << std::this_thread::get_id() << "] set data" << endl;
    prom->set_value(100);

    std::this_thread::sleep_for(std::chrono::seconds(3));

    cout << "threadid[" << std::this_thread::get_id() << "] end" << endl;
}

void test_promise1()
{
    std::promise<int> prom; // 存储一个值
    std::future<int> r = prom.get_future();

    std::thread t(set_value, std::move(prom));
    // std::thread t(set_value, prom); // promise 没有copy构造, copy赋值

    int i = r.get();
    cout << "main thread[" << std::this_thread::get_id() << "] i:" << i << endl;

    t.join();
}

void test_promise2()
{
    std::shared_ptr<std::promise<int>> prom(new std::promise<int>());
    std::future<int> r = prom->get_future();

    std::thread t(set_val, prom);

    int i = r.get();
    cout << "main thread[" << std::this_thread::get_id() << "] i:" << i << endl;

    t.join();
}

struct A
{
    int a;
};

void set_value_struct(std::promise<A> prom)
{
    cout << "threadid[" << std::this_thread::get_id() << "] set data" << endl;
    prom.set_value(A{1000});

    std::this_thread::sleep_for(std::chrono::seconds(3));

    cout << "threadid[" << std::this_thread::get_id() << "] end" << endl;
}

void test_promise_struct()
{
    std::promise<A> prom; // 存储一个值
    std::future<A> r = prom.get_future();

    std::thread t(set_value_struct, std::move(prom));

    A i = r.get();
    cout << "main thread[" << std::this_thread::get_id() << "] i.a:" << i.a << endl;

    t.join();
}

// std::promise 存储一个值
// std::packaged_task 封装一个函数
int main()
{
    // test_promise1();
    // test_promise2();
    test_promise_struct();

    return 0;
}
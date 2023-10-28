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
    std::promise<int> prom;
    std::future<int> r = prom.get_future();

    std::thread t(set_value, std::move(prom));

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

int main()
{
    // test_promise1();
    test_promise2();

    return 0;
}
#include <iostream>
#include <thread>
#include <mutex>

using namespace std;
std::mutex mtx;

void printEven(int i)
{
    if (i % 2 == 0)
    {
        cout << i << "is even" << endl;
    }
    else
    {
        throw logic_error("not even");
    }
}

void printfThreadId(int id)
{
#if 0
    try
    {
        mtx.lock();
        printEven(id);
        mtx.unlock();
    }
#endif
    try
    {
        lock_guard<mutex> lck(mtx);
        printEven(id);
    }
    catch (logic_error &)
    {
        cout << "thread:" << this_thread::get_id() << " caught exception" << endl;
    }
}

void test_mutex_lock_guard()
{
    std::thread t[10];
    for (int i = 0; i < 10; ++i)
    {
        t[i] = thread(printfThreadId, i);
    }

    for (auto &k : t)
    {
        k.join();
    }
}

int main()
{
    test_mutex_lock_guard();

    return 0;
}
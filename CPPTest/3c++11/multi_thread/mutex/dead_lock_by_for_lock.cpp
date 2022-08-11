#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <atomic>

using namespace std;

template <typename T>
class container
{
public:
    void add(T element)
    {
        // lock_guard<mutex> lock(mtx);    // 死锁
        mtx.lock();
        _elements.push_back(element);
        mtx.unlock();
    }

    void addrange(int num, ...)
    {
        va_list arguments;
        va_start(arguments, num);
        for (int i = 0; i < num; i++)
        {
            // lock_guard<mutex> lock(mtx);    // 死锁
            mtx.lock();
            add(va_arg(arguments, T));
            mtx.unlock();
        }
        va_end(arguments);
    }

    void dump()
    {
        // lock_guard<mutex> lock(mtx);
        mtx.lock();
        for (auto e : _elements)
        {
            cout << e << endl;
        }
        mtx.unlock();
    }

private:
    std::mutex mtx;
    vector<T> _elements;
};
void func(container<int> &cont)
{
    cout << this_thread::get_id() << endl;
    this_thread::sleep_for(chrono::seconds(1));

    cont.addrange(3, rand(), rand(), rand());
}

void test_deadLock_ByForLock()
{
    srand((unsigned int)time(0));

    container<int> cont;
    thread t1(func, ref(cont));
    thread t2(func, ref(cont));
    thread t3(func, ref(cont));
    
    t1.join();
    t2.join();
    t3.join();
    cont.dump();
    
}

int main()
{
    test_deadLock_ByForLock();

    return 0;
}

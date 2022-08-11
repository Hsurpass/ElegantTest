#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

using namespace std;
volatile int counter(0);

template <typename T>
class container
{
public:
    void add(T element)
    {
        // lock_guard<recursive_mutex> reclock(recmtx);
        recmtx.lock();
        _elements.push_back(element);
        recmtx.unlock();
    }

    void addrange(int num, ...)
    {
        va_list arguments;
        va_start(arguments, num);
        for (int i = 0; i < num; i++)
        {
            // lock_guard<recursive_mutex> reclock(recmtx);
            recmtx.lock();
            add(va_arg(arguments, T));
            recmtx.unlock();
        }
        va_end(arguments);
    }

    void dump()
    {
        // lock_guard<recursive_mutex> reclock(recmtx);
        recmtx.lock();
        for (auto e : _elements)
        {
            cout << e << endl;
        }
        recmtx.unlock();
    }

private:
    recursive_mutex recmtx;
    vector<T> _elements;
};
void func(container<int> &cont)
{
    cont.addrange(3, rand(), rand(), rand());
}

void test_recursive_mutex_reEnter()
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

std::recursive_mutex recurMutex;
void threadAddUseRecursiveMutexLock()
{
    cout << this_thread::get_id() << "xxxxxxxxxx" << endl;

    for (int i = 0; i < 100000; ++i)
    {
        recurMutex.lock();     // 如果把unlock()放在循环外面 死锁
        counter++;
        recurMutex.unlock();
    }
    // throw 10;
    // recurMutex.unlock();
}

void test_recursive_mutex_add()
{
    std::thread t[10];

    for (int i = 0; i < 10; i++)
    {
        t[i] = thread(threadAddUseRecursiveMutexLock);
    }

    for (auto &k : t)
    {
        k.join();
    }
    cout << "counter: " << counter << endl;
}

int main()
{
    // test_recursive_mutex_add();
    test_recursive_mutex_reEnter();

    return 0;
}
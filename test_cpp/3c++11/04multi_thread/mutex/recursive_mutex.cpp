#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

using namespace std;
volatile int counter(0);

template<typename T>
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
        for (int i = 0; i < num; i++) {
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
        for (auto e : _elements) {
            cout << e << endl;
        }
        recmtx.unlock();
    }

private:
    recursive_mutex recmtx;
    vector<T> _elements;
};
void func(container<int>& cont)
{
    // cont.addrange(3, rand(), rand(), rand());
    cont.addrange(3, 1, 1, 1);
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
// 递归锁只针对单线程是可重入的。
void test_singalthread_RecursiveMutex_reEnter()
{
    for (int i = 0; i < 5; ++i) {
        recurMutex.lock();     // 如果把unlock()放在循环外面 死锁
        cout << "thread id:" << this_thread::get_id() << "count:" << counter << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        counter++;
        recurMutex.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

// 如果一个线程没完全释放锁，另一个线程是不能获得锁的，造成了死锁。
void test_recursiveMutex_not_full_release()
{
    for (int i = 0; i < 5; ++i) {
        recurMutex.lock();     // 如果把unlock()放在循环外面 死锁
        cout << "thread id:" << this_thread::get_id() << "count:" << counter << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        counter++;
    }
    // 如果加锁了5次，释放了4次，那么另一个线程就会获取不到互斥锁，一直阻塞等待。
    // for (int i = 0; i < 4; ++i) {
    for (int i = 0; i < 5; ++i) {
        recurMutex.unlock();
    }
}
void test_recursive_mutex()
{
    std::thread t[2];

    for (int i = 0; i < 2; i++) {
        // t[i] = thread(test_singalthread_RecursiveMutex_reEnter);
        t[i] = thread(test_recursiveMutex_not_full_release);
    }

    for (auto& k : t) {
        k.join();
    }
    cout << "counter: " << counter << endl;
}

int main()
{
    test_recursive_mutex();
    // test_recursive_mutex_reEnter();

    return 0;
}
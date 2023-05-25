#include <iostream>
#include <thread>
#include <memory>
#include <mutex>
#include <stdio.h>

using namespace std;

class A{
public:
    A()
    {
        cout << "start A::A()" << endl;
        cout << "A::A(): " << this_thread::get_id() << endl;
        std::this_thread::sleep_for(std::chrono::seconds(5));
        cout << "end A::A()" << endl;
    }

    void test(int i)
    {
        printf("thread[%d] id:%ld\n", i, std::this_thread::get_id());
    }
};


/*局部静态实例虽然被定义在函数内部，但是它的生命周期是整个程序的生命周期，所以即使离开了作用域，也不会被销毁。
局部静态实例在第一次调用其所属函数时被初始化，之后一直存在于程序的静态存储区中，直到程序结束时才被销毁。
这意味着，局部静态实例在程序运行期间一直存在，可以被多次使用，不需要每次调用函数时都重新创建实例，从而提高了程序的性能和效率。*/

// 1.在c++11标准中，多个线程同时初始化一个局部静态实例是线程安全的，不会出现竞态条件，也不再需要加锁。
// 需要注意的是，如果局部静态变量的构造函数抛出异常，那么该变量的状态将是未定义的，需要开发人员自行处理异常情况。
// 2.在c++11标准中，多个线程同时访问(只读)同一个局部静态实例是线程安全的；如果同时修改不是线程安全的，需要加锁。

// *** 多个线程在等待局部静态实例初始化时被detach会发生什么？
// 如果多个线程等待局部静态实例初始化时被detach，那么这些线程将继续运行，但是这些线程不再与主线程同步，也就是说，这些线程会成为守护线程（Daemon Thread），独立于主线程运行。
// 在这种情况下，如果局部静态实例的初始化完成，那么这些守护线程仍然可以访问该实例。但是，如果这些线程在局部静态实例初始化之前就开始运行，并且需要访问该实例，那么它们可能会因为找不到该实例而出现错误。
// 因此，在多线程程序中，通常不建议使用detach将等待局部静态实例的线程分离出来。相反，建议使用join等待线程完成任务，或者使用条件变量（Condition Variable）等同步机制等待局部静态实例初始化完成。这样可以保证线程之间的同步，避免出现意外的错误。
void func(int i)
{

    static A a;
    a.test(i);
}

int main()
{
    cout << "main: " << this_thread::get_id() << endl;
    thread t[5];

    for(int i = 0; i < 5; i++)
    {
        t[i] = std::thread(func, i); 
        // t[i].detach();
    }

    std::this_thread::sleep_for(std::chrono::seconds(8));

#if 0
    for(int i = 0; i < 5; i++)
    {
        t[i].detach();
    }
#endif

    for(auto &i: t)
    {
        printf("%p, %s\n", &i, (i.joinable() ? " joinable" : " no-joinable"));
        i.join();
        // cout << &i << (i.joinable() ? " joinable" : " no-joinable") << endl;
    }

    return 0;
}
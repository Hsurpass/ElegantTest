#include <iostream>
#include <thread>
#include <string>
#include <unistd.h>

using namespace std;

void thread_getid()
{
    cout << "thread id: " << std::this_thread::get_id() << endl;
    this_thread::sleep_for(chrono::seconds(4));
    cout << "thread end" << endl;
}

void threadFunc()
{
    while (1)
    {
        sleep(1);
        cout << "child thread" << endl;
    }
}

void test_thread_crash()
{
    std::thread t(threadFunc);

    // while (1)
    // {
    //     sleep(1);
    // }
}

void test_thread_get_id()
{
    cout << "main thread id: " << this_thread::get_id() << endl;
    // thread t(thread_getid);
    thread* t = new thread(thread_getid);

    //    thread t = thread1;
    //    t = thread1;
    cout << "main run ..." << endl;

    // t.join();
    t->join();

    delete t;
}

int main()
{
    cout << "main thread id: " << this_thread::get_id() << endl;

    // thread对象在线程函数运行期间必须是有效的，否则栈推出的时候会崩溃
    // test_thread_crash();     // core dump

    test_thread_get_id();


    

    while (1)
    {
        sleep(1);
    }

    return 0;
}
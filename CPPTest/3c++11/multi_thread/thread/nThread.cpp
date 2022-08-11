#include <iostream>
#include <thread>

using namespace std;
#define N 3

void thread1()
{
    cout << "thread id: " << this_thread::get_id() << " start " << endl;
    this_thread::sleep_for(chrono::seconds(2));
    cout << "thread id: " << this_thread::get_id() << " end " << endl;
}

void test_nThread()
{
    cout << "main: " << this_thread::get_id() << endl;
    thread t[N];

    for (int i = 0; i < N; i++)
    {
        t[i] = thread(thread1);
        // t[i].join();
        // t[i].detach();
    }

    // 多次 join 会core dump, detach之后不要试图去join(core dump)
    for (auto &i : t)
    {
        cout << &i << (i.joinable() ? " joinable" : " no-joinable") << endl;
        i.join();
        cout << &i << (i.joinable() ? " joinable" : " no-joinable") << endl;
    }

}

int main()
{
    test_nThread();

    return 0;
}

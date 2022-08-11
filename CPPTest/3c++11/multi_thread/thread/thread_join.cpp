#include <iostream>
#include <thread>

using namespace std;

void thread1()
{
    cout << "thread1 start.." << endl;
    this_thread::sleep_for(chrono::seconds(5));
    cout << "thread1 end.." << endl;
}

void thread2()
{
    cout << "thread2 start.." << endl;
    this_thread::sleep_for(chrono::seconds(3));
    cout << "thread2 end.." << endl;
}

void test_thread_join()
{
    std::thread t1(thread1);
    std::thread t2(thread2);

    t1.join();
    cout << "t1 is over" << endl;
    t2.join();
    cout << "t2 is over" << endl;

}

int main()
{
    test_thread_join();

    return 0;
}

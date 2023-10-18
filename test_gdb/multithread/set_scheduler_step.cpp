#include <iostream>
#include <thread>
#include <chrono>

using namespace std;
// b 11 12 20
// r
// n
void print1()
{
    cout << "print1, start threadid:[" << std::this_thread::get_id() << "]" << endl;
    for (int i = 0; i < 10; i++) {
        cout << "print1, threadid:[" << std::this_thread::get_id() << "], i:" << i << endl;
        // this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void print2()
{
    cout << "print2, start threadid:[" << std::this_thread::get_id() << "]" << endl;

    for (int i = 0; i < 5; i++) {
        cout << "print2, threadid:[" << std::this_thread::get_id() << "], i:" << i << endl;
    }
}

void test_scheduler_step()
{
    thread t1(print1);
    thread t2(print2);

    t1.join();
    t2.join();
}

int main()
{
    test_scheduler_step();

    return 0;
}
#include "priority_thread_pool.h"
#include <iostream>

using namespace std;

void test_priority_thread_pool()
{
    ThreadPool pool(1);

    // Submit tasks with different priorities
    pool.addTask(1, []() {
        cout << "Task with priority 1 executed." << endl;
        cout << "Task with priority 1 execute finished." << endl;
    });
    
    std::this_thread::sleep_for(std::chrono::seconds(3));
    
    pool.addTask(2, []() {
        cout << "Task with priority 2 executed." << endl;
    });
    pool.addTask(3, []() {
        cout << "Task with priority 3 executed." << endl;
    });
    pool.addTask(4, []() {
        cout << "Task with priority 4 executed." << endl;
    });
    pool.addTask(5, []() {
        cout << "Task with priority 5 executed." << endl;
    });
}

int main()
{
    test_priority_thread_pool();

    return 0;
}

#include "thread_pool.h"
#include <cstdio>
#include <functional>
#include <iostream>

double add(double a, double b)
{
    return a + b;
}

void test_thread_pool()
{
    printf("main thread id: %ld\n", std::this_thread::get_id());

    ThreadPool pool(4);

    auto task1 = pool.addTask(
        [](int a, int b) {
            return a + b;
        },
        1,
        2);
    printf("Result of task1: %d\n", task1.get());

    auto task2 = pool.addTask(
        [](const std::string& str) {
            return "Hello, " + str;
        },
        "World");
    printf("Result of task2: %s\n", task2.get().c_str());

    auto task3 = pool.addTask(add, 3.5, 4.5);
    printf("Result of task3: %f\n", task3.get());

    auto task4 = pool.addTask(std::bind(add, 3.2, 4.2));
    printf("Result of task4: %f\n", task4.get());
}

int main()
{
    test_thread_pool();

    return 0;
}

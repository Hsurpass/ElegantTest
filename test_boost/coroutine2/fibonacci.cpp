// g++ fibonacci.cpp -lboost_coroutine -lboost_context

#include <boost/coroutine2/coroutine.hpp>
#include <cstdlib>
#include <iostream>

#include <boost/coroutine2/all.hpp>

void fibonacci(boost::coroutines2::coroutine< int >::push_type& push)
{
    std::cout << "coroutine function" << std::endl;

    int first = 1, second = 1;
    push(first);    // 让出cpu
    push(second);
    for (int i = 0; i < 8; ++i) {
        int third = first + second;
        first = second;
        second = third;
        push(third);
    }
}

void test_fibonacci_2()
{

    boost::coroutines2::coroutine<int>::pull_type pull(fibonacci);
    std::cout << "main func" << std::endl;

    // for (auto i : pull) {
    //     std::cout << i << "\n";
    // }

    while (pull) {
        std::cout << "i: " << pull.get() << ", !pull: " << !pull << "\n";
        pull(); // 让出cpu
    }
    std::cout << "\nDone" << std::endl;
}

void test_fibonacci_1()
{
    boost::coroutines2::coroutine< int >::pull_type source([](boost::coroutines2::coroutine< int >::push_type& sink) {
        std::cout << "coroutine function" << std::endl;

        int first = 1, second = 1;
        sink(first);
        sink(second);
        for (int i = 0; i < 8; ++i) {
            int third = first + second;
            first = second;
            second = third;
            sink(third);
        }
    });

    std::cout << "main func" << std::endl;

    for (auto i : source) {
        std::cout << i << " ";
    }
    std::cout << "\nDone" << std::endl;
}

int main()
{
    // test_fibonacci_1();
    test_fibonacci_2();

    return EXIT_SUCCESS;
}

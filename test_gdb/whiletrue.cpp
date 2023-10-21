#include <iostream>
#include <thread>

using namespace std;

void test()
{
    std::thread t([]() {
        while (1) {}
    });

    t.join();
}

int main()
{
    test();

    return 0;
}
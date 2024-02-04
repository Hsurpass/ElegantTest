#include <iostream>
#include <limits>

using namespace std;

void test_numeric_limits()
{
    std::cout << std::numeric_limits<double>::digits10 << std::endl;      // 15
    std::cout << std::numeric_limits<double>::max_digits10 << std::endl;  // 15

    std::cout << std::numeric_limits<long double>::digits10 << std::endl;  // 33
    std::cout << std::numeric_limits<long double>::max_digits10 << std::endl;  // 33

    std::cout << std::numeric_limits<long>::digits10 << std::endl;
    std::cout << std::numeric_limits<long>::max_digits10 << std::endl;

    std::cout << std::numeric_limits<long long>::digits10 << std::endl;
    std::cout << std::numeric_limits<long long>::max_digits10 << std::endl;
}

int main()
{
    test_numeric_limits();

    return 0;
}
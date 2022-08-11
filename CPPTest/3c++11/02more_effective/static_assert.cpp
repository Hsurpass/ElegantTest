#include <iostream>

using namespace std;

void test_static_assert_platform()
{
    static_assert(sizeof(void*) != 4, "64-bit code generation is not supported.");
}

template<typename T, typename U>
void test_static_assert_bit_wide(T&a, U& b)
{
    static_assert(sizeof(a) == sizeof(b), "parameters not have same width.");
}

int main()
{
    // test_static_assert_platform();

    int a; float b;
    test_static_assert_bit_wide(a, b);
    
    cout << "--------------------" << endl;
    
    char b;
    test_static_assert_bit_wide(a, b);

    return 0;
}
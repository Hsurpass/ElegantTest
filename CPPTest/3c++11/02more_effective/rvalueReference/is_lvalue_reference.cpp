#include <iostream>
#include <type_traits>

using namespace std;

template <typename T>
class Widget
{
    typedef T &LvalueRefType;
    typedef T &&RvalueRefType;

public:
    void judge()
    {
        static_assert(std::is_lvalue_reference<LvalueRefType>::value, "LvalueRefType & is lvalue reference");
        static_assert(std::is_lvalue_reference<RvalueRefType>::value, "RvalueRefType & is lvalue reference");
        cout << "LvalueRefType and RvalueRefType is lvalue reference" << endl;
    }
};

void test_is_lvalue_reference_with_template()
{
    Widget<int &> w;
    w.judge();
}

void test_is_lvalue_reference()
{
    std::cout << std::boolalpha;
    std::cout << "int: " << std::is_lvalue_reference<int>::value << std::endl;
    std::cout << "int: " << std::is_rvalue_reference<int>::value << std::endl;
    std::cout << "int: " << std::is_reference<int>::value << std::endl;

    std::cout << "int&: " << std::is_lvalue_reference<int &>::value << std::endl;
    std::cout << "int&: " << std::is_rvalue_reference<int &>::value << std::endl;
    std::cout << "int&: " << std::is_reference<int &>::value << std::endl;

    std::cout << "int&&: " << std::is_lvalue_reference<int &&>::value << std::endl;
    std::cout << "int&&: " << std::is_rvalue_reference<int &&>::value << std::endl;
    std::cout << "int&&: " << std::is_reference<int &&>::value << std::endl;

}

int main()
{
    test_is_lvalue_reference();
    // test_is_lvalue_reference_with_template();

    return 0;
}
#include <iostream>
#include <typeinfo>
using namespace std;

void test_decltype01()
{
    // c++ primer 4.1.1 左值和右值
    int a = 1;
    int *p = NULL;
    decltype(*p) b = a;   // int&
    cout << b << endl;
    cout << typeid(b).name() << endl;

    decltype(&p) c; // int**
    cout << c << endl;
    cout << typeid(c).name() << endl;
}

int main()
{
    test_decltype01();

    
    return 0;
}
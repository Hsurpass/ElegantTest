#include <iostream>

using namespace std;

struct A {
    char a:1;
    char b:2;
    char :5;
    char d:1;
    // int c;
    // char d:4;
    // unsigned int e:7;
};

class B {
public:
    unsigned int a:3;
    int b:2;
    char d:4;
    int c;
};

int main()
{
    cout << sizeof(A) << endl;
    cout << sizeof(B) << endl;

    B b;
    b.a = 8;    // 溢出了，a只占3位，只能表示0~7
    b.b = 3;    // 二进制位：0x11，对于无符号数来说就是-1
    cout << b.a << endl;    // 0
    cout << b.b << endl;    // -1
    cout << b.c << endl;

    // cout << &b.a << endl;    // error 不能对位域进行取地址。

    return 0;
}
#pragma pack(4)
// #pragma pack(8)
// #pragma pack(16)

#include <iostream>

using namespace std;

class A
{
    char c;
    double a;
    char b;
};

class B
{
    char c;
    int a;
    char b;
};

class C
{
    char c;
    A a;
};

void test_memory_alignment()
{                  // 对齐    // 8字节 4字节 16字节
    cout << sizeof(A) << endl; // 24    16    16
    cout << sizeof(B) << endl; // 12    12    12
    cout << sizeof(C) << endl; // 32    20    20
}

int main()
{
    test_memory_alignment();

    return 0;
}
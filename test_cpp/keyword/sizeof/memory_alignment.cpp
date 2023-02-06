// #pragma pack(4)
// #pragma pack(8)
// #pragma pack(16)

#include <iostream>

using namespace std;


struct Base
{
	int a;
	// double b;
	char* p;
};

class alignas(2) A  // alignas指定按照几字节对齐, 不能比结构体中最大的字节小？否则不生效？
// class A
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
{
    cout << alignof(Base) << endl;  // 8
    cout << alignof(A) << endl;		// 内存是按照几字节对齐的：8
    cout << alignof(B) << endl;	    // 4
    cout << alignof(C) << endl;	    // 8
	cout << "sizeof(A):" << sizeof(A) << endl;	// 24

                    // 对齐    // 8字节 4字节 16字节
    cout << sizeof(A) << endl; // 24    16    16
    cout << sizeof(B) << endl; // 12    12    12
    cout << sizeof(C) << endl; // 32    20    20
}

int main()
{
    test_memory_alignment();

    return 0;
}
#include <iostream>

using namespace std;

/* 非类型模板参数是有限制的。他们只能是:
    整数(包括枚举)，
    对象/函数/成员的指针，
    对象或函数的左值引用，
    nullptr
*/

// 浮点数,类对象, 字符串常量是不允许作为非类型模板参数的
class A
{};

// template<double val>
// template<A val>
// template<const char* val>
template<int I, bool B>
void func()
{
    cout << "func(), I:" << I << ", B:" << B << endl;
}

void test_expression()
{
    // func<sizeof(int) + sizeof(true), sizeof(int) == 4>();
    func<42, (sizeof(int) > 4)>();
}

//数组传参需要传长度，我们可以用非类型参数来省略
template<typename T, int N>
void myswap(T (&a)[N], T (&b)[N])
{
    cout << "N:" << N << endl;
    T tmp;
    for (int i = 0; i < N; i++)
    {
        tmp = a[i];
        a[i] = b[i];
        b[i] = tmp;
    }
}

template<typename T, int N>
void print(T (&a)[N])
{
    for (size_t i = 0; i < N; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
}

void test_nonType_template_param()
{
    int a[3] = {1,2,3};
    int b[3] = {4,5,6};

    myswap(a, b);
    print(a);
    print(b);

    cout << "-----------------------" << endl;
    // int len = 5;
    // int c[len] = {1,2,3, 4,5};
    // int d[len] = {10,20,30,40,50};

    // //c,d必须是常量表达式，否则推导出来的N就是len
    // myswap(c, d);
    // print(c);
    // print(d);

}

template<int N>
void stringLen(const char (&arr)[N])
{
    cout << "N:" << N << endl;
}

void test_stringLen()
{
    stringLen("abc");   //4
    stringLen("123456");//7
}


int main()
{
    // test_nonType_template_param();
    // test_stringLen();

    // func<"abc">();

    test_expression();

    return 0;
}
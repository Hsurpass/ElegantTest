#include <iostream>

using namespace std;

//对于 const static 类型的成员变量，无论是拷贝构造函数还是拷贝赋值函数，都无法直接对其进行赋值操作。这是因为 const 类型的成员变量在初始化后不能再次被修改。
//当类中存在 const static 成员变量时，在拷贝构造/拷贝赋值函数中，它们会被复制到正在创建的新对象中。这意味着在拷贝构造/拷贝赋值函数中，const static 成员变量的值将与原始对象相同。
class A
{
public:
    A(int& a, int b, int c) : ra(a), cb(b)
    {
        cout << "A() a:" << a << endl;
        cout << "A() ra:" << ra << endl;
    }

    A(const A& other) : ra(other.ra), cb(other.cb)
    {
        // ra = other.ra;   // 引用类型必须在初始化列表中初始化
        // cb = other.cb;   // const类型必须在初始化列表中初始化
        // sci = other.sci; // const static 类型不能被再次赋值
    }

    A& operator=(const A& other)
    {
        // ra = other.ra; // 这个只是改变类内引用所指向对象的值，而不是改变引用的指向。
        // cb = other.cb;   // const类型必须在初始化列表中初始化
        // sci = other.sci; // const static 类型不能被再次赋值

        return *this;
    }

public:
    int& ra;
    const int cb;
    static const int sci = 40;
    const static int csi;
    constexpr static int arr[5] = {0, 1, 2, 3, 4};
    const static int array[5];
};

const int A::csi = 50;
const int A::array[5] = {0, 1, 2, 3, 4};
constexpr int A::arr[5];

void test_A()
{
    int a = 10;
    A a1(a, 20, 30);
    cout << a1.ra << "," << a1.cb << "," << a1.sci << endl; // 10, 20, 40
    cout << "----------------------" << endl;

    A a2 = a1;
    cout << a2.ra << "," << a2.cb << "," << a2.sci << endl; // 10 20 40
    for (auto& i : a2.arr) {
        cout << i << " ";
    }
    cout << endl;
    for (auto& i : a2.array) {
        cout << i << " ";
    }
    cout << endl;
    cout << "----------------------" << endl;

    int b = 100;
    A a3(b, 200, 300);
    cout << a3.ra << "," << a3.cb << "," << a3.sci << endl; // 100 200 40
    a3 = a1;
    cout << a << "," << a3.ra << "," << b << "," << a3.cb << "," << a3.sci << endl; // 10 100 100 200 40
    for (auto& i : a2.arr) {
        cout << i << " ";
    }
    cout << endl;
    for (auto& i : a2.array) {
        cout << i << " ";
    }
    cout << endl;
    cout << "----------------------" << endl;
}

void test_reference()
{
    int a = 10;
    int& ra = a;
    int b = 200;
    ra = b;
    cout << a << b << ra << endl; // 200 200 200
}

int main()
{
    test_A();
    // test_reference();

    return 0;
}
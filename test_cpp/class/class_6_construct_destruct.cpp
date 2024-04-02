#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

class A
{
private:
    int* m_p;
    char* m_str;
    std::string* m_str1;
    std::vector<int> m_v;
    std::map<int, string> m_map;

public:
    A(int a, char* str, const string& str1, std::vector<int>& vi, std::map<int, string>& mis)
        : m_p(new int(a)), m_str(str), m_str1(new string(str1)), m_v(vi), m_map(mis)
    {}

    A() : m_p(nullptr), m_str(nullptr), m_str1(nullptr)
    {}

    ~A()
    {}

    A(const A& other) : m_v(other.m_v), m_map(other.m_map)
    {
        cout << "A(const A& other)" << endl;
        m_p = new int(*other.m_p);
        // cout << "*other.m_str:" << *other.m_str << endl;
        // m_str = new char(*other.m_str); // error m_str = 'h'
        int len = strlen(other.m_str) + 1;
        m_str = new char[len];
        // strcpy(m_str, other.m_str); //right
        memcpy(m_str, other.m_str, len);
        m_str1 = new string(*other.m_str1);
        // m_v = other.m_v;
        // m_map = other.m_map;
    }

    A& operator=(const A& other)
    {
        cout << "A& operator=(const A& other)" << endl;
        if (this == &other) {
            return *this;
        }

        delete m_p;
        delete[] m_str;
        delete m_str1;
        m_p = new int(*other.m_p);
        m_str = new char[strlen(other.m_str) + 1];
        strcpy(m_str, other.m_str);
        m_str1 = new string(*other.m_str1);

        m_v = other.m_v;
        m_map = other.m_map;

        return *this;
    }

    A(A&& other)
    {
        cout << "A(A&& other)" << endl;

        m_p = other.m_p;
        m_str = other.m_str;
        m_str1 = other.m_str1;
        m_v.swap(other.m_v);
        m_map.swap(other.m_map);

        other.m_p = nullptr;
        other.m_str = nullptr;
        other.m_str1 = nullptr;
    }
    A& operator=(A&& other)
    {
        cout << "A& operator=(A&& other)" << endl;
        if (&other == this) {
            return *this;
        }
        delete m_p;
        delete[] m_str;
        delete m_str1;

        m_p = other.m_p;
        m_str = other.m_str;
        m_str1 = other.m_str1;
        other.m_p = nullptr;
        other.m_str = nullptr;
        other.m_str1 = nullptr;
        m_v = std::move(other.m_v);
        m_map = std::move(other.m_map);

        // m_v.swap(other.m_v);
        // vector<int> v;
        // other.m_v.swap(v);

        return *this;
    }

    void print()
    {
        cout << "m_p: " << *m_p << ", m_str: " << m_str << ", m_str1:" << *m_str1 << endl;
        cout << "m_v: " << endl;
        for (auto i : m_v) {
            cout << i << " ";
        }
        cout << endl;
        cout << "m_map: " << endl;
        for (auto i : m_map) {
            cout << "(" << i.first << ", " << i.second << ")";
        }
        cout << endl;
    }
};

/*
可以使用sizeof操作符来计算存储二进制数据的char数组的长度。sizeof操作符返回对象或类型的大小（以字节为单位），因此可以用来计算数组所占的总字节数。
例如，如果有一个char类型的数组data存储了二进制数据，可以通过以下方式计算数组的长度：
char data[] = {0x12, 0x34, 0xAB, 0xCD}; // 例子，data数组存储了四个字节的二进制数据
size_t dataSize = sizeof(data) / sizeof(data[0]);
*/

int main()
{
    char p[6] = "hello";
    string str("world");
    vector<int> v{5, 4, 3, 2, 1};
    map<int, string> m{{1, "a"}, {2, "b"}, {3, "c"}, {4, "d"}};
    A a(3, p, str, v, m);

    a.print();

    A a1(a);
    a1.print();

    A a2;
    a2 = a;
    a2.print();

    cout << "--------------move-------------" << endl;
    A b = std::move(a);
    b.print();
    // a.print(); //Segmentation fault

    cout << "#$############" << endl;
    A b1;
    b1 = std::move(b); // 没有移动赋值会调用拷贝赋值
    b1.print();

    return 0;
}
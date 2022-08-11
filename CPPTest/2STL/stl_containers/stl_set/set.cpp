#include <iostream>
#include <set>
#include <algorithm>
#include <functional>
#include <string>

using namespace std;
using namespace placeholders;

template <typename T>
struct cmpInt
{
    bool operator()(const T &x, const T &y)
    {
        return x.m_a < y.m_a;
    }
};

struct _cmpInt
{
    template <typename T>
    bool operator()(const T &x, const T &y)
    {
        return x.m_a < y.m_a;
    }
};

template <typename T>
struct cmpString
{
    bool operator()(const T &x, const T &y)
    {
        return x.m_b < y.m_b;
    }
};

struct _cmpString
{
    template <typename T>
    bool operator()(const T &x, const T &y)
    {
        return x.m_b < y.m_b;
    }
};

class A
{
public:
    int m_a;
    string m_b;

public:
    A(int a, string b) : m_a(a), m_b(b) {}
    ~A(){}
    bool operator==(const A& another) const
    {
        return (this->m_a == another.m_a) && (this->m_b == another.m_b);
    }
};

void test_set_find_and_stdfind()
{
    // auto f = [](const A& x, const A& y) -> bool{
    //     return x.m_a < y.m_a;
    // };
    // auto f1 = bind(f, _1, _2);
    
    // std::set<A, cmpInt<A> > sa;
    // std::set<A, _cmpInt > sa;
    std::set<A, _cmpString > sa;
    
    sa.insert(A(1, "cc"));
    sa.insert(A(2, "bb"));
    sa.insert(A(3, "aa"));

    for(auto &p:sa)
    {
        cout << p.m_a << "," << p.m_b << endl;
    }
    cout << "-----------------------------" << endl;
    // std::find 和 set::find比较规则不一样
    A aa(4, "bb");
    auto itr = sa.find(aa); // set::find 使用_cmpString这个比较
    if(itr != sa.end())
    {
        cout << "set::find found." << itr->m_a << "," << itr->m_b << endl;  // find
    }
    else
    {
        cout << "set::find NOT FOUND." << itr->m_a << "," << itr->m_b << endl;
    }

    auto itr1 = std::find(sa.begin(), sa.end(), aa);    // std::find 使用类内的operator()==来比较
    if(itr1 != sa.end())
    {
        cout << "std::find found." << itr1->m_a << "," << itr1->m_b << endl;
    }
    else
    {
        cout << "std::find NOT FOUND." << itr1->m_a << "," << itr1->m_b << endl;    // not found
    }
}

void test_sizeof_set()
{
    std::set<int, std::less<int>> s;
    cout << sizeof(s) << endl;              // 48
    cout << sizeof(std::set<char>) << endl; // 48
}

void test_set_iteratorTraverse()
{
    set<int> s;
    for (size_t i = 0; i < 10; i++)
    {
        s.insert(i);
    }

    for (set<int>::iterator itr = s.begin(); itr != s.end(); ++itr)
    {
        cout << *itr << " ";
    }
    cout << endl;
}

int main()
{
    // test_sizeof_set();
    // test_set_iteratorTraverse();
    test_set_find_and_stdfind();

    return 0;
}
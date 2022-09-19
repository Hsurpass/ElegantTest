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

#if 0
    bool operator==(const A& another) const
    {
        return (this->m_a == another.m_a) && (this->m_b == another.m_b);
    }
#endif
#if 1
    bool operator==(const A& another) const
    {
        return (this->m_a == another.m_a);
    }
#endif
};

void test_set_find_and_stdfind()
{
    // auto f = [](const A& x, const A& y) -> bool{
    //     return x.m_a < y.m_a;
    // };
    // auto f1 = bind(f, _1, _2);
    
    // std::set<A, cmpInt<A> > sa;
    // std::set<A, _cmpInt > sa;
    // std::set<A, cmpString<A> > sa;
    std::set<A, _cmpString > sa;
    
    sa.insert(A(3, "bb"));
    sa.insert(A(2, "cc"));
    sa.insert(A(1, "dd"));
    sa.insert(A(4, "aa"));

    for(auto &p:sa)
    {
        cout << p.m_a << "," << p.m_b << endl;
    }
    cout << "-----------------------------" << endl;
    // std::find 和 set::find比较规则不一样
    A aa(5, "bb");
    auto itr = sa.find(aa); // set::find 使用_cmpString这个比较（set::find使用比较函数判断）
    if(itr != sa.end())
    {
        cout << "set::find found." << itr->m_a << "," << itr->m_b << endl;  // if _cmpString find 3,bb, if _cmpInt find 4,aa
    }
    else
    {
        cout << "set::find NOT FOUND." << itr->m_a << "," << itr->m_b << endl;
    }

    // cout << "aa:" << aa.m_a << "," << aa.m_b << endl;
    A a1(4, "ff");
    auto itr1 = std::find(sa.begin(), sa.end(), a1);    // std::find 使用类内的operator()==来比较
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
    for (int i = 10; i >= 0; i--)
    {
        s.insert(i);
    }

    for (set<int>::iterator itr = s.begin(); itr != s.end(); ++itr)
    {
        cout << *itr << " ";
    }
    cout << endl;
}

void test_set_insert_pair()
{
    typedef std::pair<int, string> PAIRIS;  // pair中定义了 operator<

    std::set<PAIRIS> s;
    s.insert(PAIRIS(3, "bb"));
    s.insert(PAIRIS(2, "cc"));
    s.insert(PAIRIS(1, "dd"));
    s.insert(PAIRIS(4, "aa"));

    for (auto &x:s)
    {
        cout << "x:" << x.first << ", " << x.second << endl;
    }

    PAIRIS aa(4, "aa");
    auto itr = s.find(aa); // set::find 使用_cmpString这个比较（set::find使用比较函数判断）
    if(itr != s.end())
    {
        cout << "set::find found." << itr->first << "," << itr->second << endl;  // if _cmpString find 3,bb, if _cmpInt find 4,aa
    }
    else
    {
        cout << "set::find NOT FOUND." /*<< itr->first << "," << itr->second*/ << endl;
    }

    PAIRIS a1(4, "ff");
    auto itr1 = std::find(s.begin(), s.end(), a1);    // std::find 使用类内的operator()==来比较
    if(itr1 != s.end())
    {
        cout << "std::find found." << itr1->first << "," << itr1->second << endl;
    }
    else
    {
        cout << "std::find NOT FOUND." /*<< itr1->second << "," << itr1->second*/ << endl;    // not found
    }
    
}

void test_set_insert_pair_lowerBound()
{
    typedef std::pair<int, string> PAIRIS;  // pair中定义了 operator<

    std::set<PAIRIS> s;
    s.insert(PAIRIS(3, "bb"));
    s.insert(PAIRIS(2, "cc"));
    s.insert(PAIRIS(1, "dd"));
    s.insert(PAIRIS(4, "aa"));

    for (auto &x:s)
    {
        cout << "x:" << x.first << ", " << x.second << endl;
    }

    PAIRIS p1(3, "ee");
    auto itr = s.lower_bound(p1);
    cout << itr->first << ", " << itr->second << endl;  // 4,aa

    PAIRIS p2(4, "ee");
    itr = s.lower_bound(p2);
    if (itr == s.end())
    {
        cout << "itr == s.end()" << endl;
    }
    else
    {
        cout << itr->first << ", " << itr->second << endl;  // 4,aa
    }
}

int main()
{
    // test_sizeof_set();
    // test_set_iteratorTraverse();
    // test_set_find_and_stdfind();
    // test_set_insert_pair();
    test_set_insert_pair_lowerBound();

    return 0;
}
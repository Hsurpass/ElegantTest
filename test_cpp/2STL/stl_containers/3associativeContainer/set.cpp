#include <iostream>
#include <set>
#include <algorithm>
#include <functional>
#include <string>
#include <vector>
#include "../../../basicClass/A.h"

using namespace std;
using namespace placeholders;

template <typename T>
void print(T &container)
{
    cout << "container.size:" << container.size() << endl;

    for (auto &x : container)
    {
        cout << x.geta() << " ";
    }
    cout << endl;
}


void test_set_find_and_stdfind()
{
    std::set<A> sa;
    // std::set<A, Comp<A, false>> sa;
    // std::set<A ,greater<A> > sa;
    // std::set<A, Comp<A, true>> sa;

    sa.emplace(3);
    sa.emplace(2);
    sa.emplace(1);
    sa.emplace(4);

    print(sa);
    cout << "-----------------------------" << endl;
    // std::find 和 set::find比较规则不一样
    A aa(3);
    auto itr = sa.find(aa); // set::find使用Comp这个比较, 也就是less<A>, less使用使用operator<判断）
    if (itr != sa.end())
    {
        cout << "set::find found." << itr->geta() << endl; // if _cmpString find 3,bb, if _cmpInt find 4,aa
    }
    else
    {
        cout << "set::find NOT FOUND." << endl;
    }

    cout << "---------------------------" << endl;
    A a1(3);
    auto itr1 = std::find(sa.begin(), sa.end(), a1); // std::find 使用类内的operator()==来比较
    if (itr1 != sa.end())
    {
        cout << "std::find found." << itr1->geta() << endl;
    }
    else
    {
        cout << "std::find NOT FOUND." << itr1->geta() << endl; // not found
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
    typedef std::pair<int, string> PAIRIS; // pair中定义了 operator<

    std::set<PAIRIS> s;
    s.insert(PAIRIS(3, "bb"));
    s.insert(PAIRIS(2, "cc"));
    s.insert(PAIRIS(1, "dd"));
    s.emplace(4, "aa");
    s.emplace(2, "ff");

    for (auto &x : s)
    {
        cout << "x:" << x.first << ", " << x.second << endl;
    }

    // PAIRIS aa(4, "aa");
    PAIRIS aa(2, "cc");
    auto itr = s.find(aa); // set::find使用operator<比较
    if (itr != s.end())
    {
        cout << "set::find found." << itr->first << "," << itr->second << endl; // if _cmpString find 3,bb, if _cmpInt find 4,aa
    }
    else
    {
        cout << "set::find NOT FOUND." /*<< itr->first << "," << itr->second*/ << endl;
    }

    PAIRIS a1(4, "ff");
    auto itr1 = std::find(s.begin(), s.end(), a1); // std::find 使用类内的operator()==来比较
    if (itr1 != s.end())
    {
        cout << "std::find found." << itr1->first << "," << itr1->second << endl;
    }
    else
    {
        cout << "std::find NOT FOUND." /*<< itr1->second << "," << itr1->second*/ << endl; // not found
    }
}

void test_set_insert_pair_lowerBound()
{
    typedef std::pair<int, string> PAIRIS; // pair中定义了 operator<

    std::set<PAIRIS> s;
    s.insert(PAIRIS(3, "bb"));
    s.insert(PAIRIS(2, "cc"));
    s.insert(PAIRIS(1, "dd"));
    s.insert(PAIRIS(4, "aa"));

    for (auto &x : s)
    {
        cout << "x:" << x.first << ", " << x.second << endl;
    }

    // PAIRIS p1(3, "ee");
    PAIRIS p1(3, "aa");
    auto itr = s.lower_bound(p1);
    cout << itr->first << ", " << itr->second << endl; // 4,aa 3,bb

    PAIRIS p2(4, "ee");
    itr = s.lower_bound(p2);
    if (itr == s.end())
    {
        cout << "itr == s.end()" << endl;
    }
    else
    {
        cout << itr->first << ", " << itr->second << endl; // 4,aa
    }
}

void test_set_insert_pair_upperBound()
{
    typedef std::pair<int, string> PAIRIS; // pair中定义了 operator<

    std::set<PAIRIS> s;
    s.insert(PAIRIS(3, "bb"));
    s.insert(PAIRIS(2, "cc"));
    s.insert(PAIRIS(1, "dd"));
    s.insert(PAIRIS(4, "aa"));

    for (auto &x : s)
    {
        cout << "x:" << x.first << ", " << x.second << endl;
    }

    PAIRIS p1(3, "ee");
    auto itr = s.upper_bound(p1);
    cout << itr->first << ", " << itr->second << endl; // 4,aa

    PAIRIS p2(4, "ee");
    itr = s.upper_bound(p2);
    if (itr == s.end())
    {
        cout << "itr == s.end()" << endl; // itr == s.end()
    }
    else
    {
        cout << itr->first << ", " << itr->second << endl;
    }
}

void test_set_insert_pair_equalRange()
{
    typedef std::pair<int, string> PAIRIS; // pair中定义了 operator<

    std::set<PAIRIS> s;
    s.insert(PAIRIS(3, "bb"));
    s.insert(PAIRIS(2, "cc"));
    s.insert(PAIRIS(1, "dd"));
    s.insert(PAIRIS(4, "aa"));

    for (auto &x : s)
    {
        cout << "x:" << x.first << ", " << x.second << endl;
    }

    // PAIRIS p1(3, "ee");
    // PAIRIS p1(3, "aa");
    PAIRIS p1(3, "bb");
    auto itr = s.equal_range(p1);
    cout << itr.first->first << ", " << itr.first->second << endl; //  3,bb 3,bb
    cout << itr.second->first << ", " << itr.second->second << endl;

    PAIRIS p2(4, "ee");
    itr = s.equal_range(p2);
    if (itr.first == s.end())
    {
        if (itr.second == s.end())
        {
            cout << "itr == s.end()" << endl;
        }
        else
        {
            cout << "itr.first == s.end()" << itr.second->second << endl;
        }
    }
    else
    {
        if (itr.second == s.end())
        {
            cout << itr.first->first << ", itr.secone == s.end()" << endl; // 4,aa itr == s.end()
        }
        else
        {
            cout << itr.first->first << ", " << itr.second->second << endl;
        }
    }
}

// 测试是否迭代器失效
void test_insert()
{
    set<A> sa;
    sa.emplace(1);
    sa.emplace(3);
    sa.emplace(5);
    sa.emplace(7);
    sa.emplace(9);

    cout << sa.size() << endl;
    cout << "---------------------" << endl;

    for (set<A>::iterator itr = sa.begin(); itr != sa.end(); ++itr)
    {
#if 0
        // auto r = sa.emplace(3);
        // auto r = sa.insert(3);
        auto r = sa.insert(4);  // pair<iterator,bool> insert (const value_type& val); 如果插入成功，第一个值返回插入新元素的迭代器，第二个值返回true。
        cout << r.first->geta() << ", " << r.second << endl;                       // 如果插入失败，第一个值返回已插入元素的迭代器，第二个值返回false。
#endif
#if 0
        cout << "---------------------" << endl;
        int a = 3;
        auto it = sa.lower_bound(a);
        sa.insert(it, a);   // 无论插入成功与否，迭代器不会失效
        // itr = sa.insert(it, a);  // 不能接收返回值了，否则itr总是指向3，就不会无限循环了
#endif

#if 1
        sa.insert(itr++, 3); // 无论插入成功与否，迭代器不会失效，不过写itr++会跳着访问元素, 跳出end后产生未定义行为。
#endif

        cout << itr->print() << " ";
        cout << "sa.size:" << sa.size() << endl;
    }
    cout << endl;
}

void test_erase()
{
    set<A> v;
    v.emplace(1);
    v.emplace(2);
    v.emplace(3);
    v.emplace(4);
    v.emplace(5); 

    for (auto itr = v.begin(); itr != v.end(); ++itr)
    {
        if (itr->print() == 2)
        {
            itr = v.erase(itr); //correct
            // v.erase(itr++); // correct
        }
        cout << itr->print() << " ";
    }
    cout << endl;

    cout << "==================" << endl;
    cout << v.size() << endl; // 4

}

void test_erase_the_last_one()
{
    set<A> v;
    v.emplace(1);
    v.emplace(2);
    v.emplace(3);
    v.emplace(4);
    v.emplace(5); 

#if 0
    for (auto itr = v.begin(); itr != v.end(); ++itr)
    {
        if (itr->print() == 5)  
        {
            cout << "start erase" << endl;
            itr = v.erase(itr); //correct
            if(itr == v.end())
            {
                cout << "itr == end" << endl;
                break;
            }
        }
        cout << itr->print() << " ";
    }
    cout << endl;
#endif
#if 1
    auto itr = v.begin();
    while(itr != v.end())
    {
        if (itr->print() == 5)  
        {
            cout << "start erase" << endl;
            itr = v.erase(itr); //correct
            if(itr == v.end())
            {
                cout << "itr == end" << endl;
            }
        }
        else
        {
            cout << itr->print() << " ";
            ++itr;
        }
    }
    cout << endl;
#endif

#if 0
    for (auto itr = v.begin(); itr != v.end(); )
    {
        if (itr->print() == 5)  
        {
            cout << "start erase" << endl;
            itr = v.erase(itr); //correct
            if(itr == v.end())
            {
                cout << "itr == end" << endl;
            }
        }
        else
        {
            cout << itr->print() << " ";
            ++itr;
        }
    }
    cout << endl;
#endif

    cout << "==================" << endl;
    cout << v.size() << endl; // 4

}

void test_set_vector_vector()
{
    vector<int> v1 = {1, 2, 3};
    vector<int> v2 = {1, 2, 3, 4};
    vector<int> v3 = {1, 2, 3, 4, 5};
    vector<int> v4 = {1, 2, 3};
    vector<int> v5 = {1, 2, 3};
    vector<vector<int>> v = {v1, v2, v3, v4, v5};

    set<vector<int>> s(v.begin(), v.end());
    cout << s.size() << endl;

    for (auto &i : s) {
        for (auto j : i) {
            cout << j << " ";
        }
        cout << endl;
    }


}

int main()
{
    // test_sizeof_set();
    // test_set_iteratorTraverse();
    // test_set_find_and_stdfind();
    // test_set_insert_pair();
    // test_set_insert_pair_lowerBound();
    // test_set_insert_pair_upperBound();
    // test_set_insert_pair_equalRange();
    // test_insert();
    // test_erase();
    // test_erase_the_last_one();
    test_set_vector_vector();


    return 0;
}
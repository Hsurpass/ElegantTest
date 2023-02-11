#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>
#include <string>
#include <memory>

#include "../../../../basicClass/A.h"

using namespace std;

// compare only integral part:
class Comp{
public:
bool operator()(const A& first, const A& second)
{
    return first.print() < second.print();
}
};

void test_merge_unodered_list()
{
    std::list<A> l1, l2;

    l1.emplace_back(5);
    l1.emplace_back(3);
    l1.emplace_back(1);

    l2.emplace_back(2);
    l2.emplace_back(4);
    l2.emplace_back(6);

    l1.merge(l2, Comp());
    cout << "l1.size:" << l1.size() << endl;  // 6
    cout << "l2.size:" << l2.size() << endl;  // 0
    for(auto & x:l1)
    {
        cout << x.print() << " ";
    }
    cout << endl;   // 2 4 5 3 1 6 error
}

void test_merge()
{
    std::list<A> first, second;

    first.emplace_back(3);
    first.emplace_back(2);
    first.emplace_back(2);

    second.emplace_back(3);
    second.emplace_back(7);
    second.emplace_back(1);

    first.sort();
    second.sort();

    first.merge(second);
    // (second is now empty)
    cout << "first.size:" << first.size() << endl;   // 6
    cout << "second.size:" << second.size() << endl; // 0

    second.emplace_back(5);
    cout << "first.size:" << first.size() << endl;  // 6
    cout << "second.size:" << second.size() << endl;// 1

    first.merge(second, Comp());
    cout << "first.size:" << first.size() << endl;  // 7
    cout << "second.size:" << second.size() << endl;// 0


    //1 2 2 3 3 5 7 
    std::cout << "first contains:";
    for (std::list<A>::iterator it = first.begin(); it != first.end(); ++it)
        std::cout << it->print() << " ";
    std::cout << '\n';
}

void test_list_assign_vector()
{
    list<A> l;
    l.emplace_back(1);
    l.emplace_back(2);
    l.emplace_back(3);
    l.emplace_back(4);
    l.emplace_back(5);

    cout << "------------------" << endl;
    vector<A> v;
    v.assign(l.begin(), l.end());
    for(auto &x:v)
    {
        cout << x.print() << " ";
    }
    cout << endl;
    cout << "------------------" << endl;
    
    list<A> l1;
    l1.assign(v.begin(), v.end());
    for(auto &x:l1)
    {
        cout << x.print() << " ";
    }
    cout << endl;

}

void test_assign()
{
    // initializer list constructor
    list<A> v;
    v.emplace_back(1);
    v.emplace_back(2);
    v.emplace_back(3);
    v.emplace_back(4);
    v.emplace_back(5);
    cout << "------------------------" << endl;

    list<A> v1;
    list<A> v2;
    v2.emplace_back(6);
    v2.emplace_back(7);
    v2.emplace_back(8);
    cout << "------------------------" << endl;

    list<A> v3;
    v3.emplace_back(6);
    v3.emplace_back(7);
    v3.emplace_back(8);
    v3.emplace_back(9);
    v3.emplace_back(10);
    v3.emplace_back(11);
    v3.emplace_back(12);
    cout << "------------------------" << endl;

#if 0
    // range assign
    cout << "v1.assign:" << endl;
    v1.assign(v.begin(), v.end()); // call copy constructor
    cout << v.size() <<   endl;
    cout << v1.size() <<  endl;     // 5 容量的大小也会变成右边操作值的大小
    cout << "--------------------------------" << endl;
#endif

#if 0
    cout << "v2.assign:" << endl;
    v2.assign(v.begin(), v.end()); // call operator=() copy constructor
    cout << v.size() <<   endl;
    cout << v2.size() <<  endl;     // 5 容量的大小也会变成右边操作值的大小
    cout << "--------------------------------" << endl;
#endif

#if 0
    cout << "v3.assign:" << endl;
    v3.assign(v.begin(), v.end()); // call operator=()
    cout << v.size() <<  endl;   // 5 5
    cout << v3.size() << endl;     // 5 6 容量的大小也会变成右边操作值的大小, 多余元素会被析构
    
    cout << "--------------------------------" << endl;
#endif
#if 0

    list<const char *> v4{"a", "b", "c", "d"};
    vector<string> v5;
    v5.assign(v4.begin(), v4.end()); // call operator=() 容器可以不同，容器中的元素要相同。
    cout << "print v5:" << endl;
    print(v5);
    cout << "--------------------------------" << endl;

    // fill assign
    vector<A> v6;
    v6.assign(3, A(100)); // call copy-constructor
#endif

}

void test_splice02()
{
    std::list<A> mylist1, mylist2;
    std::list<A>::iterator it;

    // set some initial values:
    for (int i = 1; i <= 4; ++i)
        mylist1.emplace_back(i); // mylist1: 1 2 3 4

    for (int i = 1; i <= 3; ++i)
        mylist2.emplace_back(i * 10); // mylist2: 10 20 30

    it = mylist1.begin();
    ++it; // points to 2

    mylist1.splice(it, mylist2);                       // mylist1: 1 10 20 30 2 3 4
                                                       // mylist2 (empty)
                                                       // "it" still points to 2 (the 5th element)
    cout << "mylist1.size:" << mylist1.size() << endl; // 7
    cout << "mylist2.size:" << mylist2.size() << endl; // 0
    cout << "--------------------------------" << endl;

    mylist2.splice(mylist2.begin(), mylist1, it);
    cout << "mylist1.size:" << mylist1.size() << endl; // 6
    cout << "mylist2.size:" << mylist2.size() << endl; // 1
    cout << it->print() << endl;
    // mylist1: 1 10 20 30 3 4
    // mylist2: 2
    // "it" is now invalid.
    cout << "--------------------------------" << endl;

    it = mylist1.begin();
    std::advance(it, 3); // "it" points now to 30
    // 把30 3 4拼接到最前面
    mylist1.splice(mylist1.begin(), mylist1, it, mylist1.end());
    // mylist1: 30 3 4 1 10 20

    std::cout << "mylist1 contains:";
    for (it = mylist1.begin(); it != mylist1.end(); ++it)
        std::cout << it->print() << " ";
    std::cout << '\n';

    std::cout << "mylist2 contains:";
    for (it = mylist2.begin(); it != mylist2.end(); ++it)
        std::cout << it->print() << " ";
    std::cout << '\n';
}

// splicing lists
void test_splice01()
{
    std::list<int> mylist1, mylist2;
    std::list<int>::iterator it;

    // set some initial values:
    for (int i = 1; i <= 4; ++i)
        mylist1.push_back(i); // mylist1: 1 2 3 4

    for (int i = 1; i <= 3; ++i)
        mylist2.push_back(i * 10); // mylist2: 10 20 30

    it = mylist1.begin();
    ++it; // points to 2

    mylist1.splice(it, mylist2); // mylist1: 1 10 20 30 2 3 4
                                 // mylist2 (empty)
                                 // "it" still points to 2 (the 5th element)

    mylist2.splice(mylist2.begin(), mylist1, it);
    // mylist1: 1 10 20 30 3 4
    // mylist2: 2
    // "it" is now invalid.
    it = mylist1.begin();
    std::advance(it, 3); // "it" points now to 30

    mylist1.splice(mylist1.begin(), mylist1, it, mylist1.end());
    // mylist1: 30 3 4 1 10 20

    std::cout << "mylist1 contains:";
    for (it = mylist1.begin(); it != mylist1.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';

    std::cout << "mylist2 contains:";
    for (it = mylist2.begin(); it != mylist2.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';
}

void test_unique()
{
    list<A> va;

    va.emplace_back(1);
    va.emplace_back(2);
    va.emplace_back(2);
    va.emplace_back(4);
    va.emplace_back(2);
    va.emplace_back(2);
    va.emplace_back(6);
    va.emplace_back(2);
    cout << "size:" << va.size() << endl; // 8
    cout << "=================================" << endl;

    // 删除连续相等元素组中的除第一个意外的其他元素。
    va.unique();
    cout << "size:" << va.size() << endl; // 6
    for (auto &x : va)
    {
        cout << x.print() << " ";
    }
    cout << endl;
    cout << "=================================" << endl;

    va.sort();
    va.unique();
    cout << "size:" << va.size() << endl; // 4
    for (auto &x : va)
    {
        cout << x.print() << " ";
    }
    cout << endl;
}

void test_sort()
{
    list<A> va;

    va.emplace_back(1);
    va.emplace_back(2);
    va.emplace_back(3);
    va.emplace_back(4);
    va.emplace_back(2);
    va.emplace_back(5);
    va.emplace_back(6);
    va.emplace_back(2);
    cout << "size:" << va.size() << endl; // 8
    cout << "=================================" << endl;

    va.sort();
    for (auto &x : va)
    {
        cout << x.print() << " ";
    }
    cout << endl;
}

void test_remove()
{
    list<A> va;

    va.emplace_back(1);
    va.emplace_back(2);
    va.emplace_back(3);
    va.emplace_back(4);
    va.emplace_back(2);
    va.emplace_back(5);
    va.emplace_back(6);
    va.emplace_back(2);
    cout << "size:" << va.size() << endl; // 8

    cout << "----------------------" << endl;
    va.remove(A(2));                      // 应该传个临时对象
    cout << "size:" << va.size() << endl; // 5

    for (auto &x : va)
    {
        cout << x.print() << " ";
    }
    cout << endl;
}

void test_clear()
{
    list<A> v = {A(1), A(2), A(3), A(4), A(5)};

    cout << v.size() << endl; // 5
    cout << "=================================" << endl;

    v.clear();                // 0    Removes all elements from the vector (which are destroyed), leaving the container with a size of 0. 清空所有元素，size变为0，capacity不会变
    cout << v.size() << endl; // 0
    cout << "==================" << endl;
}

void test_swap()
{
    list<A> v{1, 2, 3, 4, 5};
    list<A> v1;

    // swap调用之后size为0
    v1.swap(v);
    cout << "v.size:" << v.size() << endl;   // 0
    cout << "v1.size:" << v1.size() << endl; // 5

    cout << "----------------------------" << endl;
}

void test_insert()
{
    list<A> v;
    v.emplace_back(1);
    v.emplace_back(2);
    v.emplace_back(3);
    v.emplace_back(2);
    v.emplace_back(5);
    cout << v.size() << endl;
    cout << "---------------------" << endl;
    auto itr = v.emplace(v.begin(), 0);       // 返回新插入元素的迭代器
    cout << itr->print() << v.size() << endl; // 0 6

    for (list<A>::iterator itr = v.begin(); itr != v.end(); ++itr)
    {
        if (itr->print() == 2)
        {
            // itr = v.insert(itr, 10); //不能接受返值，否则无限循环下去。
            // v.insert(itr, 10);
            v.emplace(itr, 10); // 插入不会迭代器失效
        }
        cout << itr->print() << " ";
    }
    cout << endl;

    cout << "---------------------" << endl;
    for (auto &x : v)
    {
        cout << x.print() << " ";
    }
    cout << endl;
}

void test_erase_the_last_one()
{
    list<A> v;
    v.emplace_back(1);
    v.emplace_back(2);
    v.emplace_back(3);
    v.emplace_back(4);
    v.emplace_back(5); 

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
#if 0
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

#if 1
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

// test erase && 涉及到迭代器失效的问题
void test_erase()
{
    list<A> v;
    // A a1(1);
    // A a2(2);
    // A a3(3);
    // A a4(4);
    // A a5(5);
    v.emplace_back(1);
    v.emplace_back(2);
    v.emplace_back(3);
    v.emplace_back(4);
    v.emplace_back(5); // size:5, capacity:8

    // A &tmp = a2;
    cout << v.size() << endl;
    cout << "==================" << endl;

    list<A>::iterator itr;
    // itr = std::find(v.begin(),v.end(),tmp); // 自定义类使用std::find 需要自定义 operator==()
    itr = std::find(v.begin(), v.end(), A(2)); // 自定义类使用std::find 需要自定义 operator==()
    // itr = std::find(v.begin(),v.end(), 2); // 自定义类使用std::find 需要自定义 operator==()
    if (itr != v.end())
    {
        cout << itr->print() << endl;
        // v.erase(itr);
        itr = v.erase(itr); // erase 会造成迭代器失效，要把返回值接收
        cout << itr->print() << endl;
        cout << "find" << endl;
    }
    else
    {
        cout << "find none" << endl;
    }

    cout << "================================" << endl;
    for (auto itr = v.begin(); itr != v.end(); ++itr)
    {
        if (itr->print() == 2)
        {
            // itr = v.erase(itr); //correct
            v.erase(itr++); // correct
        }
        cout << itr->print() << " ";
    }
    cout << endl;

    cout << "==================" << endl;
    cout << v.size() << endl; // 4
}

void test_resize()
{
    list<A> v;
    v.resize(3);                           // resize会调用构造函数
    cout << "v.size:" << v.size() << endl; // 3
    cout << "-----------------" << endl;

    v.push_back(A(1));                     // push_back会调用移动构造
    cout << "v.size:" << v.size() << endl; // 4
    A a(2);
    v.emplace_back(a);            // 左值，拷贝构造
    v.emplace_back(3);            // 直接构造
    v.emplace_back(std::move(a)); // 移动构造

    cout << "v.size:" << v.size() << endl; // 7
    cout << "--------------------------" << endl;

    v.resize(3);                           // 缩小调用析构函数，size为3
    cout << "v.size:" << v.size() << endl; // 3
    cout << "--------------------------" << endl;
}

int main()
{
    // test_resize();
    // test_erase();
    test_erase_the_last_one();
    // test_insert();
    // test_swap();
    // test_clear();
    // test_remove();
    // test_sort();
    // test_unique();
    // test_splice01();
    // test_splice02();
    // test_merge();
    // test_merge_unodered_list();
    // test_assign();
    // test_list_assign_vector();

    return 0;
}
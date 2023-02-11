#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include <functional>
#include <typeinfo>
#include <memory>

#include "../../../../basicClass/A.h"

using namespace std;

class A;

template <typename K, typename V>
static void printMap(std::map<K, V> &m)
{
    for (auto itr = m.begin(); itr != m.end(); ++itr)
    {
        cout << itr->first << ":" << itr->second << endl;
    }
}

template <typename K, typename V>
static void printPos(std::map<K, V> &m, typename std::map<K, V>::iterator &posItr)
{
    if (posItr != m.end())
    {
        if (typeid(posItr->second).name() == typeid(A).name())
        {
            // cout << posItr->first << ":" << posItr->second.dis() << endl;
        }
        else
        {
            cout << posItr->first << ":" << posItr->second << endl;
        }
    }
    else
    {
        cout << "posItr == end"
             << ", upper_bound at position " << endl;
    }
}

// class A
// {
// public:
//     A() { cout << "A()" << endl; }
//     ~A() { cout << "~A()" << endl; }
//     A(int a) : m_a(a) {}

//     void dis()
//     {
//         cout << m_a << endl;
//     }

//     int m_a;
// };

void test_plusplus_map_value()
{
    std::map<int, int> map;
    map[0] = 1;
    cout << map[0] << endl;
    ++map[0];
    cout << map[0] << endl;
}

// map使用operator[]插入的value元素如果是类，则需要有default constructor
void test_map_key_class()
{
    std::map<int, A> mia;
    // mia[0]; //A()0x559057701ed4 使用operator[]插入元素，要有默认constructor
    mia[0] = A(1); // A(1)是右值，调用移动构造
    auto r = mia.emplace(1, 2);
    mia.emplace_hint(r.first, 2, 3);

    cout << mia[0].geta() << endl;
    cout << mia[1].geta() << endl;
    cout << mia[2].geta() << endl;

    cout << typeid(A).name() << endl;
    cout << typeid(A(10)).name() << endl;
}

/*
    0 1 2 3 4 5 6 7 8 9

                5
            3       8
          1   4   7   9
         0 2     6
*/
void test_map_iteratorTraverse_and_operatorTraverse()
{
    map<int, int> m;
    for (size_t i = 0; i < 10; i++)
    {
        m.insert(make_pair<int, int>(i, i));
    }

    // operator[] traverse
    // 0 1 2 3 4 5 6 7 8 9
    for (size_t i = 0; i < 10; i++)
    {
        cout << m[i] << " ";
    }
    cout << endl;
    cout << "-----------------------" << endl;
    // 0 1 2 3 4 5 6 7 8 9
    for (map<int, int>::iterator itr = m.begin(); itr != m.end(); ++itr)
    {
        cout << itr->second << " ";
    }
    cout << endl;
}

void test_map_lower_bound_and_upper_bound()
{
    //  0  1  2  3  4  5  6  7
    // 10 10 10 20 20 20 30 30

    // 10 20 30 30 20 10 10 20
    // 10 20 30 50
    map<int, int> m;
    m.insert(make_pair<int, int>(10, 10));
    m.insert(pair<int, int>(20, 20));
    m[50] = 50;
    m.emplace(30, 30);

    printMap(m);
    // 使用lower_bound 和 upper_bound 的序列必须是有序的

    cout << "--------------------------" << endl;
    std::map<int, int>::iterator low, up;
    low = m.lower_bound(30); //  30 2
    up = m.upper_bound(30);  //  50 3

    printPos(m, low);
    printPos(m, up);

    // 如果lower_bound == upper_bound，则说明容器中没有这个key
    pair<map<int, int>::const_iterator, map<int, int>::const_iterator> range = m.equal_range(40); // 50 50
    cout << range.first->first << ":" << range.first->second << endl;   // 50, 50
    cout << range.second->first << ":" << range.second->second << endl; // 50, 50
}

void testMapSharedPtr()
{
    map<string, shared_ptr<A>> mssp;
    mssp.insert(make_pair("a", make_shared<A>()));
    mssp.insert(make_pair("b", make_shared<A>()));
    mssp.insert(make_pair("c", make_shared<A>()));
    cout << mssp.size() << endl;
    auto itr = mssp.find("b");
    auto itr1 = mssp.erase(itr);
    cout << "------------------" << endl;
    cout << itr1->first << ", " << mssp.size() << endl;
}

void test_map_erase()
{
    std::map<int, int> mii;
    for (size_t i = 0; i < 10; i++)
    {
        mii.insert(make_pair<int, int>(i, i));
    }

    int n = mii.erase(3);
    cout << "n:" << n << endl;

    for (auto &i : mii)
    {
        cout << i.first << ", " << i.second << endl;
    }
}

void test_insert_key_of_user_defined()
{
    {
        map<A, int> mai;
        auto itr = mai.emplace(1, 1);       // 直接构造
        mai.emplace_hint(itr.first, 2, 2);  // 直接构造
    }
    cout << "********************************" << endl;
    {
        map<A, int> mai;
        auto itr = mai.insert(pair<A, int>(1, 1));  // 构造+移动
    }
    cout << "--------------------------------" << endl;
    {
        map<A, int> mai;
        auto itr = mai.insert(pair<A, int>(A(1), 1));  // 构造+移动+移动
    }
    cout << "********************************" << endl;
    {
        map<A, int> mai;
        mai.insert(make_pair(2, 2)); // 构造
    }
    cout << "--------------------------------" << endl;
    {
        map<A, int> mai;
        mai.insert(make_pair(A(2), 2)); // 构造+移动+移动
    }
    cout << "********************************" << endl;
    {
        map<A, int> mai;
        mai.insert(map<A, int>::value_type(2, 2));  // 构造+拷贝

    }
    cout << "--------------------------------" << endl;
    {
        map<A, int> mai;
        mai.insert(map<A, int>::value_type(A(2), 2));// 构造+移动+拷贝
    }
    cout << "********************************" << endl;
    {
        map<A, int> mai;
        mai[0] = 2; // 构造+移动
    }
}

void test_insert_value_of_user_defined()
{
    cout << "****************emplace:****************" << endl;
    {
        map<int, A> mai;
        auto itr = mai.emplace(1, 1);       // 直接构造
        mai.emplace_hint(itr.first, 2, 2);  // 直接构造
    }
    cout << "***************pair<k, v>():*****************" << endl;
    {
        map<int, A> mai;
        auto itr = mai.insert(pair<int, A>(1, 1));  // 构造+移动
    }
    cout << "--------------------------------" << endl;
    {
        map<int, A> mai;
        auto itr = mai.insert(pair<int, A>(1, A(1)));  // 构造+移动+移动
    }
    cout << "*************make_pair():*******************" << endl;
    {
        map<int, A> mai;
        mai.insert(make_pair(2, 2)); // 构造
    }
    cout << "--------------------------------" << endl;
    {
        map<int, A> mai;
        mai.insert(make_pair(2, A(2))); // 构造+移动+移动
    }
    cout << "*************map<int, A>::value_type*******************" << endl;
    {
        map<int, A> mai;
        mai.insert(map<int, A>::value_type(2, 2));  // 构造+移动

    }
    cout << "--------------------------------" << endl;
    {
        map<int, A> mai;
        mai.insert(map<int, A>::value_type(2, A(2)));// 构造+移动+移动
    }
    cout << "***************mai[0]:*****************" << endl;
    {
        map<int, A> mai;
        mai[0] = 2; // 构造+构造+移动赋值
    }
}

void test_erase_the_last_one()
{
    map<int, A> mia;
    mia.emplace(1, 1);  // 直接构造
    mia.emplace(2, 2);  // 直接构造
    mia.emplace(3, 3);  // 直接构造
    mia.emplace(4, 4);  // 直接构造
    mia.emplace(5, 5);  // 直接构造


#if 1
    for (auto itr = mia.begin(); itr != mia.end(); ++itr)
    {
        if (itr->second.geta() == 5)  
        {
            cout << "start erase" << endl;
            itr = mia.erase(itr); //correct
            if(itr == mia.end())
            {
                cout << "itr == end" << endl;
                break;
            }
        }
        cout << itr->second.geta() << " ";
    }
    cout << endl;
#endif
#if 0
    auto itr = mia.begin();
    while(itr != mia.end())
    {
        if (itr->second.geta() == 5)  
        {
            cout << "start erase" << endl;
            itr = mia.erase(itr); //correct
            if(itr == mia.end())
            {
                cout << "itr == end" << endl;
            }
        }
        else
        {
            cout << itr->second.geta() << " ";
            ++itr;
        }
    }
    cout << endl;
#endif

#if 0
    for (auto itr = mia.begin(); itr != mia.end(); )
    {
        if (itr->second.geta() == 5)  
        {
            cout << "start erase" << endl;
            itr = mia.erase(itr); //correct
            if(itr == mia.end())
            {
                cout << "itr == end" << endl;
            }
        }
        else
        {
            cout << itr->second.geta() << " ";
            ++itr;
        }
    }
    cout << endl;
#endif

    cout << "==================" << endl;
    cout << mia.size() << endl; // 4

}

int main()
{
    // test_map_key_class();
    // test_map_iteratorTraverse_and_operatorTraverse();
    // test_map_lower_bound_and_upper_bound();
    // testMapSharedPtr();
    // test_plusplus_map_value();
    // test_map_erase();
    // test_insert_key_of_user_defined();
    // test_insert_value_of_user_defined();
    test_erase_the_last_one();

    return 0;
}
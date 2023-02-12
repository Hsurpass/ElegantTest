#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>
#include <string>
#include <memory>

#include "../../../../basicClass/A.h"

using namespace std;

template <typename T>
void print(vector<T> &tmpVec)
{
    cout << "vector.size:" << tmpVec.size() << endl;

    for (auto &value : tmpVec)
    {
        cout << value << ", ";
    }
    cout << endl;
}

void test_vector_remove_erase()
{
    vector<A> va;
    va.reserve(10);

    va.emplace_back(1);
    va.emplace_back(2);
    va.emplace_back(3);
    va.emplace_back(4);
    va.emplace_back(2);
    va.emplace_back(5);
    va.emplace_back(6);
    va.emplace_back(2);

    cout << "----------------------" << endl;
    auto itr = std::remove(va.begin(), va.end(), A(2)); // 应该传个临时对象
    va.erase(itr, va.end());
    for (auto &x : va)
    {
        cout << x.print() << " ";
    }
    cout << endl;
}

void test_vector_remove()
{
    vector<A> va;
    va.reserve(10);

    va.emplace_back(1);
    va.emplace_back(2);
    va.emplace_back(3);
    va.emplace_back(4);
    va.emplace_back(2);
    va.emplace_back(5);
    va.emplace_back(6);
    va.emplace_back(2);
    cout << "size:" << va.size() << ", capacity:" << va.capacity() << endl;

    cout << "----------------------" << endl;
    auto itr = std::remove(va.begin(), va.end(), A(2)); // 应该传个临时对象
    for (auto i = va.begin(); i != itr; ++i)
    {
        cout << i->print() << " ";
    }
    cout << endl;
    cout << "----------------------" << endl;
    for (auto &x : va)
    {
        cout << x.print() << " ";
    }
    cout << endl;
}

void test_emplace_copy()
{
    vector<A> va;

    // va.emplace_back(A(100));
    // va.emplace_back(A(200));
    // va.emplace_back(A(200));

    va.emplace_back(100);
    va.emplace_back(200);
    va.emplace_back(200);

    cout << "size:" << va.size() << ", capacity:" << va.capacity() << endl;
}

// shared_ptr放vector，利用其引用计数
int test_shared_ptr_save_vector()
{
    //    vector<A> *pvsp = new vector<A>;
    shared_ptr<vector<A>> pvsp(new vector<A>);
    return 0;
}

// vector 里面放智能指针
void test_push_shared_ptr()
{
    vector<shared_ptr<A>> vsp;
    vsp.reserve(10);
    cout << "---------------------" << endl;
    cout << vsp.size() << endl;     // 0
    cout << vsp.capacity() << endl; // 10
    cout << "---------------------" << endl;
    for (int i = 0; i < 10; ++i)
    {
        // vsp.emplace_back(new A(i));
        vsp.emplace_back(make_shared<A>(i));
        // vsp.push_back(make_shared<A>(i));
    }
    for (vector<shared_ptr<A>>::iterator itr = vsp.begin(); itr != vsp.end(); ++itr)
    {
        cout << (*itr)->print() << " ";
    }
    cout << endl;
    cout << "---------------------" << endl;
    cout << vsp.size() << endl;     // 10
    cout << vsp.capacity() << endl; // 10
    cout << "---------------------" << endl;
}

void test_reserve02()
{
    vector<A> v1;

    v1.push_back(A(1));
    cout << v1.capacity() << endl; // 1

    // 看会不会发生内存copy? 会发生，只不过之后的capacity都变成4了
    v1.reserve(4); // 重新开辟空间，并发生拷贝。
    cout << v1.capacity() << endl;

    cout << "------------------------" << endl;
    v1.push_back(A(2));
    cout << v1.capacity() << endl;

    v1.push_back(A(3));
    cout << v1.capacity() << endl;

    v1.push_back(4);
    cout << v1.capacity() << endl;

    v1.push_back(5); // 超过reserve 的容量就会发生元素拷贝了
    cout << v1.capacity() << endl;
}

// c++ primer 练习9.24
// test operator[] at() front() begin()
void test_core_dump()
{
    vector<string> svec;
    // cout << svec[0];    // Segmentation fault (core dumped)
    // cout << svec.at(0);    // 抛出 std::out_of_range 异常
    // cout << svec.front();   // Segmentation fault (core dumped)
    auto itr = svec.begin();
    cout << *itr; // Segmentation fault (core dumped)
}

// vector嵌套 二维数组
void test_two_dimensional_array()
{
    vector<vector<int>> arr(5, vector<int>(5, 10));
    cout << arr.size() << endl;
    cout << arr[0].size() << endl;
    cout << arr[1].size() << endl;
    cout << arr[2].size() << endl;
    cout << arr[3].size() << endl;
    cout << arr[4].size() << endl;

    for (vector<vector<int>>::iterator itr = arr.begin(); itr != arr.end(); ++itr)
    {
        for (vector<int>::iterator jtr = itr->begin(); jtr != itr->end(); ++jtr)
        {
            cout << *jtr << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// integration test
int integration_test()
{
    vector<int> vi;
    int data[10] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
    vi.assign(data, data + 10);
    vector<int>::iterator itr = vi.begin();
    vi.erase(vi.begin(), vi.end());
    cout << vi.size() << endl;
    cout << vi.capacity() << endl;
    cout << "---------------------" << endl;

    //    itr = vi.insert(itr,100);
    //    cout << *++itr << endl;
    //    itr = vi.erase(itr);
    //    cout << *++itr << endl;
    //    vi.shrink_to_fit();
    //    cout << vi.size() << endl;
    //    cout << vi.capacity() << endl;
    cout << "---------------------" << endl;
    //    for(;itr != vi.end();)
    //    {
    //        if(*itr%2==0)
    //            itr = vi.erase(itr);
    //        else
    //        {
    //            cout<<*itr<<endl;
    //            ++itr;
    //        }
    //    }
    /*
    for(;itr != vi.end();)
    {
        if(*itr % 2)
        {
            itr = vi.insert(itr,100);
            itr += 2;
        }
        else {
            ++itr;
        }
    }
    for(auto &v:vi)
    {
        cout << v << " ";
    }
    cout << endl; */
    cout << "---------------------" << endl;
    cout << vi.size() << endl;
    cout << vi.capacity() << endl;
    cout << "---------------------" << endl;
    return 0;
}

// vector 放指针
void test_push_pointer()
{
    A *p1 = new A(1);
    A *p2 = new A(2);
    A *p3 = new A(3);
    A *p4 = new A(4);
    A *p5 = new A(5);
    cout << "===============" << endl;

    vector<A *> vp;
    vp.push_back(p1);
    vp.push_back(p2);
    vp.push_back(p3);
    vp.push_back(p4);
    vp.push_back(p5);

    A *ptmp = vp.front();
    cout << ptmp->print() << endl; // 1
}

// emplace 会直接调用构造而不是拷贝, 传入的参数必须和构造函数的类型相匹配。 当容器超过capacity后还是会发生拷贝
void test_emplace_back()
{
    vector<A> va;
    va.reserve(10);

    // va.emplace(va.begin(),1);   // emplace 类似于insert 还是会发生元素后移
    // va.emplace(va.begin(),2);
    // va.emplace(va.begin(),3);
    // cout << va.size() << endl;
    // cout << va.capacity() << endl;
    // cout << "---------------------"<<endl;

    va.emplace_back(4);
    va.emplace_back(5);
    va.emplace_back(6);
    cout << va.size() << endl;     // 3
    cout << va.capacity() << endl; // 10
    cout << "---------------------" << endl;

    A a4(7);
    va.emplace_back(a4);           // 因为传入的是A类型的左值参数，所以会调用copy constructor
    cout << va.size() << endl;     // 4
    cout << va.capacity() << endl; // 10
    cout << "---------------------" << endl;

    va.emplace_back(std::move(a4)); // 因为传入的是A类型的右值参数，所以会调用move constructor
    cout << va.size() << endl;      // 5
    cout << va.capacity() << endl;  // 10
    cout << "---------------------" << endl;

    va.emplace_back(A(8));         // 因为传入的是A类型的右值参数，所以会调用move constructor
    cout << va.size() << endl;     // 6
    cout << va.capacity() << endl; // 10
    cout << "---------------------" << endl;

    // va.emplace(va.begin(),8);
    // cout << va.size() << endl;
    // cout << va.capacity() << endl;
    // cout << "---------------------"<<endl;
}

// test vector insert
void test_insert()
{
    vector<A> va;
    va.reserve(2);
    va.emplace_back(2);
    va.emplace_back(10);

    cout << va.size() << endl;
    cout << va.capacity() << endl;
    cout << "---------------------" << endl;

    int flag = 1;
    for (vector<A>::iterator itr = va.begin(); itr != va.end(); ++itr)
    {
#if 0
        if (itr->print() == 2 && flag == 1)
        {
            itr = va.emplace(itr, 3);// itr point to 3
            // va.emplace(itr, 3); // 迭代器失效
            flag = 0;
        }
#endif

#if 1
        if (itr->print() == 2)
        {
            #if 1
            itr = va.emplace(itr, 3); // itr point to 3
            ++itr;  // itr point to 2 //避免了陷入无限循环
            #endif
            #if 0
            va.emplace(itr++, 3); // 迭代器失效 // itr point to 2
            #endif
        }
#endif

        cout << itr->print() << " ";
    }
    cout << endl;
}

// test size capacity 内存成倍增长
void test_memory_increase()
{
    vector<int> vi;
    vi.push_back(1);
    cout << vi.size() << endl;     // 1
    cout << vi.capacity() << endl; // 1
    vi.push_back(2);
    cout << vi.size() << endl;     // 2
    cout << vi.capacity() << endl; // 2
    vi.push_back(3);
    cout << vi.size() << endl;     // 3
    cout << vi.capacity() << endl; // 4
    vi.push_back(4);
    cout << vi.size() << endl;     // 4
    cout << vi.capacity() << endl; // 4
    vi.push_back(5);
    cout << vi.size() << endl;     // 5
    cout << vi.capacity() << endl; // 8
}

void test_erase_the_last_one()
{
    vector<A> v;
    v.emplace_back(1);
    v.emplace_back(2);
    v.emplace_back(3);
    v.emplace_back(4);
    v.emplace_back(5); 

#if 1
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

void test_erase_post_plus_plus()
{
    vector<A> va;
    va.reserve(5);
    va.emplace_back(1);
    va.emplace_back(2);
    va.emplace_back(3);
    va.emplace_back(4);
    va.emplace_back(5);

    cout << va.size() << endl;
    cout << va.capacity() << endl;
    cout << "---------------------" << endl;
    
    for (vector<A>::iterator itr = va.begin(); itr != va.end(); ++itr)
    {
        if (itr->print() == 5)
        {
            itr = va.erase(itr); // itr point to 3
            // va.erase(itr++); // 迭代器失效(不是期望的元素) // itr point to 4
        }

        if (itr != va.end()) {
            cout << itr->print() << " ";
        }
        else {
            cout << "itr is end" << endl;   // 还要考虑erase的是最后一个元素的情况。erase完最后一个元素返回的itr指向end()，再++就变成野指针了。
            break;
        }
    }
    cout << endl;

}

// test erase && 涉及到迭代器失效的问题
void test_erase_string()
{
    vector<string> v;
    string a1("1");
    string a2("2");
    string a3("3");
    string a4("4");
    string a5("5");
    v.push_back(a1);
    v.push_back(a2);
    v.push_back(a3);
    v.push_back(a4);
    v.push_back(a5);

    cout << v.capacity() << endl;
    cout << v.size() << endl;
    cout << "==================" << endl;

    vector<string>::iterator itr;
    // itr = std::find(v.begin(),v.end(),"2");
    itr = std::find(v.begin(), v.end(), string("2")); // 应该传个对象。
    if (itr != v.end())
    {
        cout << *itr << endl;
        itr = v.erase(itr);
        cout << *itr << endl;
    }
    else
    {
        cout << "find none" << endl;
    }
}

// test erase && 涉及到迭代器失效的问题
void test_erase()
{
    vector<A> v;
    A a1(1);
    A a2(2);
    A a3(3);
    A a4(4);
    A a5(5);
    v.push_back(a1);
    v.push_back(a2);
    v.push_back(a3);
    v.push_back(a4);
    v.push_back(a5); // size:5, capacity:8

    // vector<A> v = {A(1),A(2),A(3),A(4),A(5)}; // size:5, capacity:5
    // A &tmp = a2;
    cout << v.size() << endl;
    cout << v.capacity() << endl;
    cout << "==================" << endl;

    vector<A>::iterator itr;
    // itr = std::find(v.begin(),v.end(),tmp); // 自定义类使用std::find 需要自定义 operator==()
    itr = std::find(v.begin(), v.end(), A(2)); // 自定义类使用std::find 需要自定义 operator==()
    // itr = std::find(v.begin(),v.end(), 2); // 自定义类使用std::find 需要自定义 operator==()
    if (itr != v.end())
    {
        cout << itr->print() << endl;
        itr = v.erase(itr); // erase 会造成迭代器失效，元素会前移, 前移会造成元素copy(call operator=())
        cout << itr->print() << endl;
    }
    else
    {
        cout << "find none" << endl;
    }

    cout << "==================" << endl;
    cout << v.size() << endl;     // 4
    cout << v.capacity() << endl; // 8
}

// clear+shrink_to_fit：彻底清空容器，
void test_vector_clear_shrink_to_fit()
{
    vector<A> vi = {A(1), A(2), A(3), A(4), A(5)};
    cout << vi.size() << endl;     // 5
    cout << vi.capacity() << endl; // 5
    cout << "---------------------" << endl;

    vi.resize(10);
    cout << vi.size() << endl;     // 10
    cout << vi.capacity() << endl; // 10
    cout << "---------------------" << endl;

    vi.resize(8);
    cout << vi.size() << endl;     // 8
    cout << vi.capacity() << endl; // 10
    cout << "---------------------" << endl;

    vi.shrink_to_fit();
    cout << vi.size() << endl;     // 8
    cout << vi.capacity() << endl; // 8
    cout << "---------------------" << endl;

    vi.clear();
    cout << vi.size() << endl;     // 0
    cout << vi.capacity() << endl; // 8
    cout << "---------------------" << endl;

    vi.shrink_to_fit();
    cout << vi.size() << endl;     // 0
    cout << vi.capacity() << endl; // 0
}

void test_vector_clear()
{
    vector<A> v = {A(1), A(2), A(3), A(4), A(5)};

    cout << v.size() << endl;     // 5
    cout << v.capacity() << endl; // 5
    cout << "=================================" << endl;

    v.clear();                    // 0    Removes all elements from the vector (which are destroyed), leaving the container with a size of 0. 清空所有元素，size变为0，capacity不会变
    cout << v.size() << endl;     // 0
    cout << v.capacity() << endl; // 5
    cout << "==================" << endl;
}

// test shrink_to_fit
int test_vector_shrink_to_fit01()
{
    vector<int> vi = {1, 2, 3, 4, 5};
    cout << vi.size() << endl;     // 5
    cout << vi.capacity() << endl; // 5
    cout << "----------------------------------" << endl;

    vi.resize(10);
    cout << vi.size() << endl;     // 10
    cout << vi.capacity() << endl; // 10
    cout << "----------------------------------" << endl;

    vi.shrink_to_fit();
    cout << vi.size() << endl;     // 10
    cout << vi.capacity() << endl; // 10

    cout << "----------------------------------" << endl;
    vi.resize(8);                  // 缩小会调用析构函数，size变小， capacity不变
    cout << vi.size() << endl;     // 8
    cout << vi.capacity() << endl; // 10

    cout << "----------------------------------" << endl;
    vi.shrink_to_fit();
    cout << vi.size() << endl;     // 8
    cout << vi.capacity() << endl; // 8

    return 0;
}

// test shrink_to_fit
// https://cplusplus.com/reference/vector/vector/shrink_to_fit/
// "Requests the container to reduce its capacity to fit its size."
// 减小容器的capacity为size
void test_vector_shrink_to_fit()
{
    vector<A> v = {A(1), A(2), A(3), A(4), A(5)};

    cout << v.size() << endl;     // 5
    cout << v.capacity() << endl; // 5
    cout << "=================================" << endl;

    v.shrink_to_fit();            // 5
    cout << v.size() << endl;     // 5
    cout << v.capacity() << endl; // 5
    cout << "==================" << endl;

    for (auto &i : v)
    {
        cout << i.print() << endl;
    }
    cout << "==================" << endl;
}

// test resize,resize 缩小的时候size会变小，capacity不变
void test_vector_resize()
{
    vector<A> v;
    v.resize(3);                                    // resize会调用构造函数, 超过容量后还是会发生拷贝, 且内存成倍增长 3 * 2 = 6。
    cout << "v.size:" << v.size() << endl;          // 3
    cout << "v.capacity: " << v.capacity() << endl; // 3
    cout << "-----------------" << endl;

    v.push_back(A(1));                              // push_back会调用拷贝构造
    cout << "v.size:" << v.size() << endl;          // 4
    cout << "v.capacity: " << v.capacity() << endl; // 6
    v.push_back(A(2));
    v.push_back(A(3));
    v.push_back(A(4));

    cout << "v.size:" << v.size() << endl;          // 7
    cout << "v.capacity: " << v.capacity() << endl; // 12
    cout << "--------------------------" << endl;

    v.resize(3);                                    // 缩小调用析构函数，size为3，capacity不变。12
    cout << "v.size:" << v.size() << endl;          // 3
    cout << "v.capacity: " << v.capacity() << endl; // 12
    cout << "--------------------------" << endl;
}

// reverse扩充的是容量，不是追加空间，可以多次调用
void test_vector_reserve_01()
{
    vector<A> v = {A(1), A(2), A(3), A(4), A(5)};

    cout << v.size() << endl;     // 5
    cout << v.capacity() << endl; // 5
    cout << "-----------------" << endl;
    v.reserve(10);
    cout << v.size() << endl;     // 5
    cout << v.capacity() << endl; // 10
    v.reserve(20);
    cout << v.size() << endl;     // 5
    cout << v.capacity() << endl; // 20
}

// test reverse
void test_vector_reserve()
{
    cout << "test_vector_reverse:" << endl;

    vector<A> v;
    v.reserve(3);                                   // reserve 不会调用构造函数, 超过容量后还是会发生拷贝, 且内存成倍增长 3 * 2 = 6。
    cout << "v.size:" << v.size() << endl;          // 3
    cout << "v.capacity: " << v.capacity() << endl; // 3

    cout << "-----------------" << endl;
    v.push_back(A(1)); // push_back会调用拷贝构造
    cout << "v.size:" << v.size() << endl;
    cout << "v.capacity: " << v.capacity() << endl; // 3
    v.push_back(A(2));
    v.push_back(A(3));
    v.push_back(A(4));

    cout << "v.size:" << v.size() << endl;          // 4
    cout << "v.capacity: " << v.capacity() << endl; // 6
    cout << "-----------------" << endl;

    // v.reserve(3);    // size不变，capacity不变
    // v.reserve(10);   // size不变，capacity变大
    // v.resize(3);     // 缩小，resize会调用析构函数 size变小，capacity不变
    v.resize(10); // 变大，resize会调用构造函数 size变大，capacity变大

    for (vector<A>::iterator itr = v.begin(); itr != v.end(); ++itr)
    {
        cout << itr->print() << " ";
    }
    cout << endl;

    cout << "v.size:" << v.size() << endl;          // reserve: 4 resize: 3
    cout << "v.capacity: " << v.capacity() << endl; // reserve: 6 resize: 6

    // cout<< "-----------------" <<endl;
    //    vector<A> v1(v);
    //    v1 = v;
    //    v1.reserve(10);
    //    v1.resize(10);
    //    v1 = v;
    //    v1.assign(v.begin(),v.end());
    //    v1.emplace(v.begin(),v.end());
    //    v1.emplace_back(v.begin(),v.end());
    //    v.pop_back();
    //    v.erase(v.begin());
    //    v.erase(v.begin()+2,v.end() -1);

    cout << "-----------------" << endl;
}

// vector.swap
void test_vector_swap()
{
#if 1
    vector<A> v{A(1), A(2), A(3), A(4), A(5)};
    vector<A> v1;

    // swap调用之后size为0，capacity为0
    v1.swap(v);
    cout << "v.size:" << v.size() << ", v.capacity:" << v.capacity() << endl;     // 0  0
    cout << "v1.size:" << v1.size() << ", v1.capacity:" << v1.capacity() << endl; // 5  5

    cout << "----------------------------" << endl;
#endif
#if 0
    //验证swap之后迭代器是否还能正常使用    error
    vector<A> v{A(1), A(2), A(3), A(4), A(5)};
    vector<A> v2{A(7), A(8), A(9)};
    for (vector<A>::iterator itr = v2.begin(); itr != v2.end(); ++itr)
    {
        cout << itr->print() << endl;
        v.swap(v2);
        cout << v.size() << "," << v2.size() << endl;
        break;
        // cout << (itr + 1)->print() << endl;
    }
    cout << "----------------------------" << endl;
#endif
#if 0
    vector<string> vs{"a", "b", "c", "d"};
    vector<string> vs1{"e", "f", "g", "h", "i", "k"};
    for (vector<string>::iterator itr = vs.begin(); itr != vs.end(); ++itr) 
    {
        cout << *itr << endl;
        vs.swap(vs1);   // error
        cout << vs.size() << vs1.size() << endl;
        cout << *(itr + 1) << endl;
    }
    cout << "----------------------------" << endl;
#endif

    string s1 = "abcd";
    string s2 = "efgh";
    s1.swap(s2);
    cout << s1 << "," << s2 << endl;
}

// vector.assign
void test_vector_assign()
{
    // initializer list constructor
    vector<A> v;
    v.reserve(6);
    v.emplace_back(1);
    v.emplace_back(2);
    v.emplace_back(3);
    v.emplace_back(4);
    v.emplace_back(5);
    cout << "------------------------" << endl;

    vector<A> v1;
    vector<A> v2;
    v2.reserve(3);
    v2.emplace_back(6);
    v2.emplace_back(7);
    v2.emplace_back(8);
    cout << "------------------------" << endl;

    vector<A> v3;
    v3.reserve(7);
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
    cout << v.size() <<  v.capacity()  << endl;
    cout << v1.size() << v1.capacity() << endl;     // 5 容量的大小也会变成右边操作值的大小
    cout << "--------------------------------" << endl;
#endif

#if 1
    cout << "v2.assign:" << endl;
    v2.assign(v.begin(), v.end()); // call operator=() copy constructor
    cout << v.size() <<  v.capacity()  << endl;
    cout << v2.size() << v2.capacity() << endl;     // 5 容量的大小也会变成右边操作值的大小
    cout << "--------------------------------" << endl;
#endif

#if 0
    cout << "v3.assign:" << endl;
    v3.assign(v.begin(), v.end()); // call operator=()
    cout << v.size() << v.capacity() << endl;   // 5 5
    cout << v3.size() << v3.capacity() << endl;     // 5 6 容量的大小也会变成右边操作值的大小, 多余元素会被析构
    
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

// vector容器的直接赋值操作
void test_vector_init_assign()
{
    // initializer list constructor
    vector<A> v{A(1), A(2), A(3), A(4), A(5)};
    vector<A> v1;
    vector<A> v2{A(6), A(7), A(8)};
    vector<A> v3{A(6), A(7), A(8), A(9), A(10), A(11)};

    v1 = v;                    // 会调用 copy constructor
    cout << v1.size() << endl; // 5, 容量的大小也会变成右边操作值的大小

    cout << "--------------------------------" << endl;
    v2 = v;                    // 会调用 copy constructor
    cout << v1.size() << endl; // 5, 容量的大小也会变成右边操作值的大小

    cout << "--------------------------------" << endl;
    v3 = v;                    // 会调用 operator=()
    cout << v1.size() << endl; // 5, 容量的大小也会变成右边操作值的大小
}

// vector容器的定义与初始化
void test_vector_init()
{
    cout << "test001" << endl;
    // 1.default constructor
    vector<A> v1; // 空容器

    // 2.fill constructor
    vector<A> v2(5);        // 调用5次构造函数
    vector<A> v3(5, A(11)); // 调用5次拷贝构造

    // 3.range constructor
    cout << "range constructor:" << endl;
    vector<A> v4(v3.begin(), v3.begin() + 3); // 调用3次拷贝构造
    deque<A> deq(5, A(100));
    vector<A> v5(deq.begin(), deq.begin() + 2); // 调用2次拷贝构造，容器类型可以不相同，元素类型必须相同。

    // 4.copy constructor
    cout << "copy constructor:" << endl;
    vector<A> v6(v3);  // 调用5次拷贝构造函数
    vector<A> v7 = v3; // 调用5次拷贝构造函数

    // 5.initializer list constructor
    cout << "initializer list constructor: " << endl;
    vector<A> v8{A(1), A(2), A(3), A(4), A(5)};    // 调用5次拷贝构造函数
    vector<A> v9 = {A(1), A(2), A(3), A(4), A(5)}; // 调用5次拷贝构造函数
    vector<A> v10({A(1), A(2), A(3), A(4), A(5)}); // 调用5次拷贝构造函数
}

int main()
{
    // test_vector_init();
    // test_vector_init_assign();
    test_vector_assign();
    // test_vector_swap();

    // test_vector_reserve();
    // test_vector_reserve_01();
    // test_reserve02();
    // test_vector_resize();

    // test_vector_shrink_to_fit();
    // test_vector_shrink_to_fit01();
    // test_vector_clear();
    // test_vector_clear_shrink_to_fit();
   
    // test_erase();
    // test_erase_string();
    // test_erase_post_plus_plus();
    // test_erase_the_last_one();
    // test_memory_increase();
    
    // test_insert();
    // test_emplace_back();
    // test_emplace_copy();
   
    // test_push_pointer();
    // integration_test();
    // test_two_dimensional_array();
    // test_core_dump();
    // test_push_shared_ptr();
    // test_shared_ptr_save_vector();
    
    test_vector_remove();
    // test_vector_remove_erase();

    return 0;
}

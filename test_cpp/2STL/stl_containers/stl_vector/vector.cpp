#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <deque>

using namespace std;

template<typename T>
void print(vector<T>& tmpVec)
{
    cout << "vector.size:" << tmpVec.size() << endl;

    for(auto &value:tmpVec)
    {
        cout << value << ", ";  
    }
    cout << endl;
}

// 基础类型 在vector中的定义与初始化
int test01()
{
    // https://cplusplus.com/reference/vector/vector/vector/
    // 1. default constructor
    vector<int> v1;
    print(v1);
    // 2. fill constructor
    vector<int> v2(5);
    print(v2);
    vector<int> v3(5,100);
    print(v3);
    // 3. range constructor
    int myints[] = {16,2,77,29};
    vector<int> v4(myints, myints + 3);
    print(v4);
    // 4. copy constructor
    vector<int> vi5(v4);
    print(vi5);
    vector<int> vi6 = v4;
    print(vi6);
    // 5. initializer list constructor (c++11)
    vector<int> vi7{1,2,3,4,5,6,7};
    print(vi7);
    vector<int> vi8 = {1,2,3,4,5,6,7};
    print(vi8);
    vector<int> vi9({1,2,3,4,5,6,7,8});
    print(vi9);

    cout << "-------------------------------------------------------------" << endl;
    // c++ primer
    // c++11 初始化列表在vector中的应用
    vector<string> v5{"hi"};
    print(v5);

    // vector<string> v6("hi"); // error 不能使用字符串字面值构造vector对象

    // 对于v7, v8提供的值显然无法执行初始化列表, 编译器会尝试用默认值初始化vector对象
    vector<string> v7{10};  //10个空string对象
    print(v7);

    vector<string> v8{10,"hello"};  // 10个 “hello”
    print(v8);

    cout << "-------------------------------------------------------------" << endl;
    // c++ primer 9.2.4
    list<string> l({"a", "b", "c"});
    deque<const char*> deq{"d", "e", "f"};

    // vector<string> v9(l);    // error, 整个容器的拷贝必须容器类型相同，并且容器内元素类型相同
    vector<string> v10(l.begin(), l.end());   // true
    print(v10);
    vector<string> v11(deq.begin(), deq.end());   // true
    print(v11);

    vector<int> vec1{1,2,3,4,5,6,7,8,9};
    list<int> list1{1,2,3,4,5,6};
    vector<double> v12(list1.begin(), list1.end());
    print(v12);
    // vector<double> v13(vec1);    // copy constructor 容器类型和元素类型必须严格相同。

    return 0;
}

int test02()
{
    vector<int> v1 = {1,3,5,7,9,11,13,15};
    vector<int> v2 = {2,4,6,8,10};
    vector<int> v3 = {100,101};

    print(v1);
    print(v2);
    print(v3);
    cout << "-------------------" << endl;

    // v1 = v2;
    // v3 = v2;
    // print(v1);  // 完全被替换成v2, 多的元素会被去除
    // print(v2);  
    // print(v3);  // 完全被替换成v2

     cout << "-------------------" << endl;

    v1 = {2,4,6,8,10};
    v3 = {2,4,6,8,10};
    print(v1);  // 完全被替换成v2, 多的元素会被去除
    print(v2);  
    print(v3);  // 完全被替换成v2


    return 0;
}

template<typename T>
void func(T obj)
{
    print(obj);
    cout << "func(T obj)" << endl;
}

int test03()
{
    vector<int> vec;
    vec = vector<int>{1,2,3};
    print(vec);

    func(vector<int>{4,2,3});      // 初始化列表
    func(vector<string>{"abc", "def", "hig"});
    func(vector<float>{10.2,11.3,12.4});
    func(vector<double>(2.121211,21.22));
    // func(vector<bool>{true,false,true}); // vector<bool>并不是真正的vector容器

    return 0;
}

// vector<bool>里面不是一个字节一个字节存储的，而是一个bit一个bit存储。
// 因为没有直接去给一个bit来操作，所以用operator[]的时候，正常容器返回的应该是一个对应元素的引用，
// 但是对于vector< bool>实际上访问的是一个”proxy reference”而不是一个”true reference”，返回的是”std::vector< bool>:reference”类型的对象。
int test04()
{
    vector<bool> c{ false, true, false, true, false };
    bool b = c[0];  // 暗含了一个隐式的类型转换
    auto d = c[1];  // auto推断出来的并不是一个bool值，而是一个vector<bool>的内部类。

    cout << "b:" << b << endl;
    cout << "d:" << d << endl;

    b = true;
    d = false; 

    cout << "b:" << b << endl;
    cout << "d:" << d << endl;
    for (auto i:c)
    {
        cout << i << " ";
    }
    cout << endl;

    // c.clear();   // （未实现效果）如果c被销毁，d就会变成一个悬垂指针，再对d操作就属于未定义行为。
    // cout << "b:" << b << endl;
    // cout << "d:" << d << endl;

    // 对于容器一些基本的操作它并不能满足，诸如取地址给指针初始化操作
    //【因为没有办法给单一一个bit来取地址，或者搞引用】
    // bool &tmp = c[0];
    // bool *p = &c[0];

    return 0;
}

void test05()
{
    vector<int> v{0,1,2,3,4};
    print(v);
    cout << "&v:" << &v << endl;
    cout << "&v[0]:" << &v[0] << endl;
    cout << "v.data():" << v.data() << endl;
    vector<int>::iterator itr = v.begin();
    cout << "&v.begin():" << &itr << endl;
}

void test_vector_shrink_to_fit()
{
    vector<int> v;
    v.reserve(10);
    cout << "v.size:" << v.size() << ", v.capacity:" << v.capacity() << endl;   // 0, 10

    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    cout << "v.size:" << v.size() << ", v.capacity:" << v.capacity() << endl;   // 4, 10

    v.resize(2);
    cout << "v.size:" << v.size() << ", v.capacity:" << v.capacity() << endl;   // 2, 10

    // v.clear();   // clear之后只会把元素删除，空间并没有减小
    cout << "v.size:" << v.size() << ", v.capacity:" << v.capacity() << endl;   // 0, 10

    v.shrink_to_fit();
    cout << "v.size:" << v.size() << ", v.capacity:" << v.capacity() << endl;   // 0, 0

}

void test_vector_iterator()
{
    vector<int> vi{10, 20, 30};
    print(vi);

    const vector<int>::iterator iter = vi.begin();  // == T* const iter;
    *iter = 100;
    // ++iter;  // 不可修改
    print(vi);  // 100 20 30
    
    vector<int>::iterator const iter1 = vi.begin();  // == T* const iter;
    *iter1 = 1000;
    // ++iter;  // 不可修改
    print(vi);  // 1000 20 30

    vector<int>::const_iterator citr = vi.begin();  // == const T* citr
    // *citr = 30;  
    ++citr;
    cout << *citr << endl;  // 20

    const vector<int>::const_iterator ccitr = vi.begin(); // == const T* const ccitr
    // *citr = 40;  
    // ++ccitr;
    cout << *ccitr << endl; // 1000

    const int* p = &vi[0];
    cout << *p << endl;
    // *p = 10000;

}

int main()
{
    // test01();
    // test02();
    // test03();
    // test04();
    // test05();
    // test_vector_shrink_to_fit();
    test_vector_iterator();

    return 0;
}


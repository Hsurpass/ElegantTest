#include <iostream>
#include <memory>
#include <vector>
#include <functional>

using namespace std;
using namespace placeholders;

// class Copy : public enable_shared_from_this<Copy>
class Copy
{
public:
    Copy(int i = 10) : _i(new int(i))
    {
        cout << "Copy(int i)" << this << endl;
    }
    Copy(const Copy &another) : _i(new int(*another._i))
    {
        cout << " Copy(const Copy & another)" << this << endl;
    }
    void dis()
    {
        cout << *_i << endl;
    }
    ~Copy()
    {
        cout << "~Copy()" << this << endl;
    }

    int *_i;
};

class CopyEnableShared : public Copy, public enable_shared_from_this<CopyEnableShared>
{
public:
    CopyEnableShared(int i = 11) : Copy(i) 
    {
        // 不能在构造/析构函数中调用 shared_from_this(): 对象还没初始化完
        // shared_ptr<CopyEnableShared> tmp = shared_from_this();  // core dump
    }
};

class CopyNOEnableShared : public Copy
{
public:
    CopyNOEnableShared(int i = 11) : Copy(i)
    {
    }
};

void test_enable_shared_from_this_in_constructor()
{
    cout << "test_enable_shared_from_this_in_constructor" << endl;
    shared_ptr<CopyEnableShared> ptr = make_shared<CopyEnableShared>(123);
    cout << ptr.use_count() << endl;
}

void test_enable_shared_from_this_with_bind_placeholders()
{
    {
        CopyEnableShared *c = new CopyEnableShared(); // Copy(int i)0x7fffe9477e70

        shared_ptr<CopyEnableShared> s1;
        s1.reset(c);
        // s1 = shared_ptr<CopyEnableShared>(c);
        cout << s1.use_count() << endl; // 1

        {
            auto f = std::bind(&CopyEnableShared::dis, _1); // s1 传参是值类型 shared_ptr会在bind内部拷贝一个，placeholder传参是引用类型
            // s1.reset(); // 0
            cout << s1.use_count() << endl; // 1 | 0
            f(s1->shared_from_this());      // 11 current | crash dump
            cout << s1.use_count() << endl; // 1 | 0
        } 
        cout << s1.use_count() << endl; // 1 | 0
    }
}

void test_enable_shared_from_this_with_bind()
{
    {
        CopyEnableShared *c = new CopyEnableShared(); // Copy(int i)0x7fffe9477e70

        shared_ptr<CopyEnableShared> s1;
        s1.reset(c);
        // s1 = shared_ptr<CopyEnableShared>(c);
        cout << s1.use_count() << endl; // 1

        {
            auto f = std::bind(&CopyEnableShared::dis, s1->shared_from_this()); // s1 传参是值类型 shared_ptr会在bind内部拷贝一个，placeholder传参是引用类型
            // s1.reset(); // 0
            cout << s1.use_count() << endl; // 2 | 0
            f();                            // 11 current | crash dump
            cout << s1.use_count() << endl; // 2 | 0
        } 
        cout << s1.use_count() << endl; // 1 | 0
    }
}

void test_no_enable_shared_from_this_with_bind_placeholders_crash()
{
    {
        CopyEnableShared *c = new CopyEnableShared(); // Copy(int i)0x7fffe9477e70

        shared_ptr<CopyEnableShared> s1;
        s1.reset(c);
        // s1 = shared_ptr<CopyEnableShared>(c);
        cout << s1.use_count() << endl; // 1

        {
            auto f = std::bind(&CopyEnableShared::dis, _1); // s1 传参是值类型 shared_ptr会在bind内部拷贝一个，placeholder传参是引用类型
            // s1.reset(); // 0
            cout << s1.use_count() << endl; // 1 | 0
            f(s1);                            // 11 current | crash dump
            cout << s1.use_count() << endl; // 1
        } 
        cout << s1.use_count() << endl; // 1
    }
}

void test_no_enable_shared_from_this_with_bind_crash()
{
    {
        CopyEnableShared *c = new CopyEnableShared(); // Copy(int i)0x7fffe9477e70

#if 0
        auto f = std::bind(&CopyEnableShared::dis, c);
        delete c;
        f();    // core dumped

#endif
#if 1
        shared_ptr<CopyEnableShared> s1;
        s1.reset(c);
        // s1 = shared_ptr<CopyEnableShared>(c);
        cout << s1.use_count() << endl; // 1

        // {
            auto f = std::bind(&CopyEnableShared::dis, s1); // s1 传参是值类型 shared_ptr会在bind内部拷贝一个，placeholder传参是引用类型
            // s1.reset(); // 0
            cout << s1.use_count() << endl; // 0 2
            f();                            // 11 current
        // }   // 1(f 这个对象析构了所以是 1)
        cout << s1.use_count() << endl; // 0 2(f 这个对象还没析构所以还是 2)
#endif
    }
}

void test_no_enable_shared_from_this_sharedPtr_redestructor()
{
    {
        CopyNOEnableShared *c = new CopyNOEnableShared(); // Copy(int i)0x7fffe9477e70

        shared_ptr<CopyNOEnableShared> s1(c);
        shared_ptr<CopyNOEnableShared> s2(c);

        cout << s1.use_count() << endl; // 1
        cout << s2.use_count() << endl; // 1
    }                                   // ~Copy()0x7fffe9477e70 ~Copy()0x7fffe9477e70 ----> core dumped
}

void enable_shared_from_this_test01()
{
    std::shared_ptr<CopyEnableShared> ptr = make_shared<CopyEnableShared>(111);

    cout << ptr.use_count() << endl; // 1

    shared_ptr<CopyEnableShared> ptr1 = ptr->shared_from_this();
    cout << ptr.use_count() << endl;  // 2
    cout << ptr1.use_count() << endl; // 2

    if (!ptr.owner_before(ptr1) && !ptr1.owner_before(ptr))
    {
        cout << "ptr and ptr1 share ownership" << endl;
    }
}

int main()
{
    // enable_shared_from_this_test01();
    // test_no_enable_shared_from_this_sharedPtr_redestructor();
    // test_no_enable_shared_from_this_with_bind_crash();
    // test_no_enable_shared_from_this_with_bind_placeholders_crash();
    // test_enable_shared_from_this_with_bind();
    test_enable_shared_from_this_with_bind_placeholders();
    // test_enable_shared_from_this_in_constructor();

    return 0;
}
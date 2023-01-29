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

    shared_ptr<CopyEnableShared> getSharedPtr() 
    {
        return shared_from_this();
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
        }   // f对象释放，引用计数减1
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

        shared_ptr<CopyEnableShared> s1;
        s1.reset(c);
        // s1 = shared_ptr<CopyEnableShared>(c);
        cout << "s1.use_count:" << s1.use_count() << endl; // 1
#if 1

        
        auto f = std::bind(&CopyEnableShared::dis, s1); // s1 传参是值类型 shared_ptr会在bind内部拷贝一个，placeholder传参是引用类型
        // s1.reset(); // 0 引用计数减1，同时放弃托管。
        cout << "s1.use_count:" << s1.use_count() << endl; // 2
        f();   // 11                        
        
        cout << "s1.use_count:" << s1.use_count() << endl; // 2 f 这个对象还没析构所以还是 2）
#endif
#if 0
        {
            auto f = std::bind(&CopyEnableShared::dis, s1); // s1 传参是值类型 shared_ptr会在bind内部拷贝一个，placeholder传参是引用类型
            cout << s1.use_count() << endl; // 2
            f();  // 11 current
            cout << s1.use_count() << endl; // 2
        }   // 1(f 这个对象析构了所以是 1)
        cout << s1.use_count() << endl; // 1)
#endif
    }
}

// 两个shared_ptr托管同一个指针，会造成重析构而崩溃
void test_sharedPtr_redestructor()
{
#if 0
    {
        CopyNOEnableShared *c = new CopyNOEnableShared(); // Copy(int i)0x7fffe9477e70

        shared_ptr<CopyNOEnableShared> s1(c);
        shared_ptr<CopyNOEnableShared> s2(c);

        cout << s1.use_count() << endl; // 1
        cout << s2.use_count() << endl; // 1
    }                                   // ~Copy()0x7fffe9477e70 ~Copy()0x7fffe9477e70 ----> core dumped
#endif

#if 1
    {
        CopyEnableShared *c = new CopyEnableShared(); // Copy(int i)

        shared_ptr<CopyEnableShared> s1(c);
        shared_ptr<CopyEnableShared> s2(c);

        cout << s1.use_count() << endl; // 1
        cout << s2.use_count() << endl; // 1
    }
#endif   
}

void test_use_shared_from_this_slove_redestructor()
{
    {   
        // 必须先初始化一个shared_ptr把weak_this初始化，再使用shared_from_this()。
        // CopyEnableShared *s = new CopyEnableShared(); // Copy(int i)
        shared_ptr<CopyEnableShared> s(new CopyEnableShared()); // Copy(int i)
        cout << s.use_count() << endl; // 1

        shared_ptr<CopyEnableShared> s1 = s->getSharedPtr();
        cout << s1.use_count() << endl; // 2
        shared_ptr<CopyEnableShared> s2 = s->getSharedPtr();

        cout << s1.use_count() << endl; // 3
        cout << s2.use_count() << endl; // 3
    }
}


// 
void enable_shared_from_this_why01()
{
    std::shared_ptr<CopyEnableShared> ptr = make_shared<CopyEnableShared>(111);
    cout << ptr.use_count() << endl; // 1
    shared_ptr<CopyEnableShared> ptr1 = ptr->shared_from_this();
    cout << ptr.use_count() << endl;  // 2
    cout << ptr1.use_count() << endl; // 2

    // 用裸指针构造，引用计数并不会加1，这也是要用shared_from_this的一个原因
    std::shared_ptr<CopyEnableShared> ptr2(ptr.get());  
    cout << ptr2.use_count() << endl;  // 1
        
    cout << ptr.use_count() << endl;  // 2
    cout << ptr1.use_count() << endl; // 2
}

void enable_shared_from_this_test01()
{
    std::shared_ptr<CopyEnableShared> ptr = make_shared<CopyEnableShared>(111);

    cout << ptr.use_count() << endl; // 1
    cout << ptr->shared_from_this().use_count() << endl; // 2
    cout << ptr.use_count() << endl; // 1

    weak_ptr<CopyEnableShared> wkPtr = ptr->shared_from_this();
    cout << wkPtr.use_count() << endl;  // 1

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
    // enable_shared_from_this_why01();

    // test_sharedPtr_redestructor();
    // test_use_shared_from_this_slove_redestructor();
    
    // test_no_enable_shared_from_this_with_bind_crash();
    // test_no_enable_shared_from_this_with_bind_placeholders_crash();
    // test_enable_shared_from_this_with_bind();
    // test_enable_shared_from_this_with_bind_placeholders();
    test_enable_shared_from_this_in_constructor();

    return 0;
}
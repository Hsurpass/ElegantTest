#include <iostream>
#include <memory>
#include <vector>
#include <functional>

using namespace std;

class Test : public enable_shared_from_this<Test>
{
public:
    Test(){ cout << "Test()" << endl; m_a = 10; }
    ~Test(){ cout << "~Test()" << endl; m_a = -1; }

    // 可以返回临时对象，不能返回临时对象的引用
    shared_ptr<Test> getSharedPtr()
    {
        cout << "shared_from_this().use_count:" << shared_from_this().use_count() << endl;
        shared_ptr<Test> obj = shared_from_this();
        cout << "getSharedPtr, use_count:" << obj.use_count() << endl;    // 2

        return obj;
    }

    // error 不能返回临时对象的引用
    // const shared_ptr<Test>& getSharedPtrReference()
    // {
    //     return shared_from_this();
    // }

    shared_ptr<Test>&& getSharedPtrRvalueReference()
    {
        return std::move(shared_from_this());
    }

    shared_ptr<Test> get_redestructor_SharedPtr()
    {
        {
            shared_ptr<Test> t(this);   // 临时变量t托管this,离开作用域的时候引用计数减一，this指针还没被释放。
            cout << "get_redestructor_SharedPtr, use_count:" << t.use_count() << endl;
            return t;
        }
    }

    int m_a;
};

// 测试使用enable_shared_from_this解决重析构的问题
void test_shared_ptr_redestructor01()
{
    shared_ptr<Test> t(new Test);
    cout << "t.use_count: " << t.use_count() << endl;

#if 0
    // t 和 t1 都托管了裸指针，会造成重析构。
    shared_ptr<Test> t1 = t->get_redestructor_SharedPtr();
    cout << "t.use_count: " << t.use_count() << endl;   //1
    cout << "t1.use_count: " << t1.use_count() << endl; //1
#endif

#if 1
    // 使用shared_from_this解决此问题
    shared_ptr<Test> t1 = t->getSharedPtr();
    cout << "t.use_count: " << t.use_count() << endl;   // 1
    cout << "t1.use_count: " << t1.use_count() << endl; // 1
#endif

#if 0
    // error 不能返回临时对象的引用
    shared_ptr<Test> t1(t->getSharedPtrReference());    // crash
    cout << "t1.use_count: " << t1.use_count() << endl; 
    cout << "t.use_count: " << t.use_count() << endl;   
    cout << "t1.use_count: " << t1.use_count() << endl; 
#endif

#if 0
    // error 
    shared_ptr<Test>&& t1 = t->getSharedPtrRvalueReference();   // crash
    cout << "t1.use_count: " << t1.use_count() << endl; 
    cout << "t.use_count: " << t.use_count() << endl;   
    cout << "t1.use_count: " << t1.use_count() << endl; 
#endif
}

void test_shared_ptr_redestructor02()
{
    Test* t = new Test;

#if 1
    {
        shared_ptr<Test> t1 = t->get_redestructor_SharedPtr();
        cout << "t1->m_a: " << t1->m_a << endl;             // 10
        cout << "t1.use_count: " << t1.use_count() << endl; //1
        delete t;   // redestructor crash
    }
#endif

#if 0
// enable_shared_from_this中有个weak_ptr成员变量weak_this, shared_from_this()函数就是通过weak_ptr来生成shared_ptr,
// (weak_ptr中保存着引用计数，这样生成的shared_ptr就能共用引用计数了，不会再出现重析构的问题)
// 而weak_this则是在shared_ptr的构造函数中被赋值的，所以要使用shared_from_this()必须先构造一个shared_ptr对象。
// 这也是为什么不能在构造函数中使用shared_from_this()的原因。
    {
        shared_ptr<Test> t1 = t->getSharedPtr();    // error --> throwing an instance of 'std::bad_weak_ptr'
        cout << "t1.use_count: " << t1.use_count() << endl;
        delete t;
    }
#endif
}

int main()
{
    test_shared_ptr_redestructor01();
    // test_shared_ptr_redestructor02();


    return 0;
}

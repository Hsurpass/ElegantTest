#include <iostream>
#include <mutex>
#include <memory>
#include <assert.h>

using namespace std;

//饿汉式, 程序加载的时候就初始化
class EagerSingleton
{
public:
    static EagerSingleton *getInstance()
    {
        return m_ins;
    }
    static void destroyInstance()
    {
        /*饿汉式通常是在main函数开始时就初始化了，那它的释放通常不会再线程里释放，
        而是在main函数结束前释放，没有竞争的关系，所以可以不用加锁。*/
        if(m_ins)
        {   
            delete m_ins;
            m_ins = NULL;
        }
    }
    void run()
    {
        cout << "Eager singleton" << endl;
    }
private:
    static EagerSingleton *m_ins;
    EagerSingleton(){}
    ~EagerSingleton(){}
    EagerSingleton(const EagerSingleton &another);
    EagerSingleton& operator=(const EagerSingleton &another);
};
// 静态成员的初始化程序被认为是类定义的一部分，因此它可以访问私有成员。
EagerSingleton* EagerSingleton::m_ins = new EagerSingleton();



// 懒汉式 调用的时候在初始化
class Singleton
{
public:
    static Singleton *getInstance()
    {
        if (_ins == nullptr) 
        {
            lock_guard<std::mutex> lock(m_mtx);
            if (_ins == nullptr)    //二次判断防止多线程竞争
            {
                _ins = new Singleton;
            }
        }
        return _ins;
    }
    static void destroyInstance()
    {
        lock_guard<std::mutex> lock(m_mtx);
        if (_ins != nullptr)
        {
            delete _ins;
            _ins = NULL;
        }
    }
    void run()
    {
        cout << "test singleton" << endl;
    }

private:
    // static volatile Singleton *_ins;
    static Singleton *_ins;

    Singleton() {}
    ~Singleton() {}
    Singleton(const Singleton &another);
    Singleton& operator=(const Singleton &another);

    static std::mutex m_mtx;
};
Singleton *Singleton::_ins = NULL;
// volatile Singleton *Singleton::_ins = NULL;
std::mutex Singleton::m_mtx;


// 局部静态变量的懒汉式
class Singleton_localStatic
{
public:
    static Singleton_localStatic *getInstance()
    {
        // 局部静态成员变量的初始化时是线程安全的，只有一个线程能执行初始化，其他线程会在此阻塞。
        // 全局的就更不用说了，全局变量是在程序一运行就进行初始化了。
        static Singleton_localStatic instance;
        return &instance;
    }

    void run()
    {
        cout << "test singleton" << endl;
    }

private:

    Singleton_localStatic() {}      // 禁止外部构造
    ~Singleton_localStatic() {}     // 禁止外部析构
    Singleton_localStatic(const Singleton_localStatic &another);    // 禁止外部复制
    Singleton_localStatic& operator=(const Singleton_localStatic &another); // 禁止外部赋值
};


void test_lazy_singleton()
{
    Singleton *p1 = Singleton::getInstance();
    Singleton *p2 = Singleton::getInstance();
    if (p1 == p2)
    {
        cout << "p1 == p2" << endl;
    }
    p1->run();
    p2->run();

    p1->destroyInstance();
    // Singleton a(*p1);
    // Singleton a = *p1;
    // Singleton a;
}

void test_eager_singleton()
{
    EagerSingleton* p1 = EagerSingleton::getInstance();
    EagerSingleton* p2 = EagerSingleton::getInstance();
    assert(p1 == p2);
    p1->run();
    p2->run();

    p1->destroyInstance();
}

class A 
{
public:
    static std::shared_ptr<A> instance;
private:
    A(){}
};
// make_shared是在类外部定义的，因此无法访问私有构造函数。
// shared_ptr<A> A::instance = make_shared<A>();
// 但是静态成员的初始化程序被认为是类定义的一部分，因此它可以访问私有成员。
shared_ptr<A> A::instance(new A());

int main()
{
    // test_lazy_singleton();
    test_eager_singleton();

    return 0;
}

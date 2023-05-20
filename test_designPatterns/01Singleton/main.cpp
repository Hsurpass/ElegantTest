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
    EagerSingleton() {}
    EagerSingleton(const EagerSingleton &another) {}
    ~EagerSingleton() {}
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
    static void releaseInstance()
    {
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
    static Singleton *_ins;
    Singleton() {}
    Singleton(const Singleton &another) {}
    ~Singleton() {}
    static std::mutex m_mtx;
};
Singleton *Singleton::_ins = NULL;
std::mutex Singleton::m_mtx;

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

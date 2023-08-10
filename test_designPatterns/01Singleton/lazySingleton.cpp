#include <iostream>
#include <mutex>
#include <memory>
#include <assert.h>
#include <thread>

using namespace std;

// 懒汉式 调用的时候在初始化
class LazySingleton
{
public:
    static LazySingleton* getInstance()
    {
        // 这里使用double check.好处是，只有判断指针为空的时候才加锁，
        // 避免每次调用 GetInstance的方法都加锁，锁的开销毕竟还是有点大的。
        if (_ins == nullptr) {
            lock_guard<std::mutex> lock(m_mtx);
            if (_ins == nullptr)    //二次判断防止多线程重复调用构造函数
            {
                _ins = new LazySingleton;
            }
        }
        // return _ins;
        return const_cast<LazySingleton*>(_ins);
    }
    static void destroyInstance()
    {
        lock_guard<std::mutex> lock(m_mtx);
        if (_ins != nullptr) {
            delete _ins;
            _ins = NULL;
        }
    }
    void run()
    {
        cout << "test LazySingleton" << endl;
    }

private:
    static volatile LazySingleton* _ins;
    // static LazySingleton *_ins;

    LazySingleton()
    {
        cout << "LazySingleton::LazySingleton()" << endl;
    }
    ~LazySingleton()
    {
        cout << "LazySingleton::~LazySingleton()" << endl;
    }
    LazySingleton(const LazySingleton& another);
    LazySingleton& operator=(const LazySingleton& another);

    static std::mutex m_mtx;
};
// LazySingleton *LazySingleton::_ins = NULL;
volatile LazySingleton* LazySingleton::_ins = NULL;
std::mutex LazySingleton::m_mtx;

void test_lazy_singleton()
{
    LazySingleton* p1 = LazySingleton::getInstance();
    LazySingleton* p2 = LazySingleton::getInstance();
    if (p1 == p2) {
        cout << "p1 == p2" << endl;
    }
    p1->run();
    p2->run();

    p1->destroyInstance();
    // LazySingleton a(*p1);
    // LazySingleton a = *p1;
    // LazySingleton a;
}

void func(int i)
{
    LazySingleton* ins = LazySingleton::getInstance();

    ins->run();

    std::this_thread::sleep_for(std::chrono::seconds(3));
    ins->destroyInstance();
}

void test_lazy_singleton_multithread()
{
    cout << "main: " << this_thread::get_id() << endl;
    thread t[5];

    for (int i = 0; i < 5; i++) {
        t[i] = std::thread(func, i);
    }

    for (auto& i : t) {
        i.join();
    }
}

class A
{
public:
    static std::shared_ptr<A> instance;
private:
    A()
    {}
};
// make_shared是在类外部定义的，因此无法访问私有构造函数。
// shared_ptr<A> A::instance = make_shared<A>();
// 但是静态成员的初始化程序被认为是类定义的一部分，因此它可以访问私有成员。
shared_ptr<A> A::instance(new A());

int main()
{
    // test_lazy_singleton();
    test_lazy_singleton_multithread();

    return 0;
}

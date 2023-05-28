#include <iostream>
#include <mutex>
#include <memory>
#include <assert.h>

using namespace std;

//饿汉式, 程序加载的时候就初始化
class HungrySingleton
{
public:
    static HungrySingleton *getInstance()
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
    static HungrySingleton *m_ins;
    HungrySingleton(){}
    ~HungrySingleton(){}
    HungrySingleton(const HungrySingleton &another);
    HungrySingleton& operator=(const HungrySingleton &another);
};
// 静态成员的初始化程序被认为是类定义的一部分，因此它可以访问私有成员。
HungrySingleton* HungrySingleton::m_ins = new HungrySingleton();


void test_eager_singleton()
{
    HungrySingleton* p1 = HungrySingleton::getInstance();
    HungrySingleton* p2 = HungrySingleton::getInstance();
    assert(p1 == p2);
    p1->run();
    p2->run();

    p1->destroyInstance();
}

int main()
{
    test_eager_singleton();

}
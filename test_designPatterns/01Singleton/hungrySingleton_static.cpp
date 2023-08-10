#include <iostream>

using namespace std;

class A
{
public:
    A()
    {
        cout << "A::A()" << endl;
    }
    ~A()
    {
        cout << "A::~A()" << endl;
    }

    static A a;
};
// A A::a;  // 如果在这定义了，则初始化在main函数之前。

// static A a;  //main函数之前进行初始化
void func()
{
    static A a; // 调用时初始化
}

class HungrySingleton
{
public:
    static HungrySingleton& get_instance()
    {
        return m_ins;
    }
    void run()
    {
        cout << "run" << endl;
    }
private:
    HungrySingleton()
    {
        cout << "HungrySingleton()" << endl;
    }
    ~HungrySingleton()
    {
        cout << "~HungrySingleton()" << endl;
    }
    HungrySingleton(const HungrySingleton& other);
    HungrySingleton& operator=(const HungrySingleton& other);

    static HungrySingleton m_ins;
};
HungrySingleton HungrySingleton::m_ins; // main函数之前初始化

int main()
{
    cout << "----------main----------" << endl;
    // A a;
    // func();

    HungrySingleton::get_instance();

    return 0;
}
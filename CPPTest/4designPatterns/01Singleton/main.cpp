#include <iostream>
#include <mutex>
#include <memory>

using namespace std;

class Singleton
{
public:
    static Singleton* getInstance()
    {
        if(_ins == nullptr)
        {
            lock_guard<std::mutex> lock(m_mtx);
            if(_ins == nullptr)
            {
                _ins = new Singleton;
            }
        }
        return _ins;
    }
    static void releaseInstance()
    {
        if(_ins != nullptr)
        {
            delete _ins;
            _ins = NULL;
        }
    }
    void run()
    {
        cout<<"test singleton"<<endl;
    }
private:
    static Singleton* _ins;
    Singleton() {}
    Singleton(const Singleton& another){}
    ~Singleton() {}
    static std::mutex m_mtx;
};
Singleton* Singleton::_ins = NULL;
std::mutex Singleton::m_mtx;

int main()
{
    Singleton *p1 = Singleton::getInstance();
    Singleton *p2 = Singleton::getInstance();
    if(p1 == p2)
    {
        cout << "p1 == p2" << endl;
    }
    p1->run();
    p2->run();
//    Singleton a(*p1);
//    Singleton a = *p1;
//    Singleton a;
    return 0;
}

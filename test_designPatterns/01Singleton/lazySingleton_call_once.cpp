#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

class Singleton_callonce
{
public:
    static Singleton_callonce *getInstance()
    {
        std::call_once(initFlag, init);
        
        return instance;
    }
    static void destroyInstance()
    {
        std::call_once(destroyFlag, destroy);
    }

    void run()
    {
        cout << "test Singleton_callonce" << endl;
    }

private:
    static void init()
    {
        instance = new Singleton_callonce();
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }

    static void destroy()
    {
        delete instance;
        instance = nullptr;
    }

    Singleton_callonce() { cout << "Singleton_callonce::Singleton_callonce()" << endl; }      // 禁止外部构造
    ~Singleton_callonce() {cout << "Singleton_callonce::~Singleton_callonce()" << endl; }     // 禁止外部析构
    Singleton_callonce(const Singleton_callonce &another);    // 禁止外部复制
    Singleton_callonce& operator=(const Singleton_callonce &another); // 禁止外部赋值

    static std::once_flag initFlag;
    static std::once_flag destroyFlag;
    static Singleton_callonce* instance;
};

std::once_flag Singleton_callonce::initFlag;
std::once_flag Singleton_callonce::destroyFlag;
Singleton_callonce* Singleton_callonce::instance = nullptr;

void func(int i)
{
    Singleton_callonce* ins = Singleton_callonce::getInstance();

    ins->run();

    // std::this_thread::sleep_for(std::chrono::seconds(3));
    // Singleton_callonce::destroyInstance();
}

void test_lazy_singleton_with_callOnce_multithread()
{
    cout << "main: " << this_thread::get_id() << endl;
    thread t[5];

    for(int i = 0; i < 5; i++)
    {
        t[i] = std::thread(func, i); 
    }

    for (auto &i:t)
    {
        i.join();
    }
    Singleton_callonce::destroyInstance();
    
}

int main()
{
    test_lazy_singleton_with_callOnce_multithread();

    return 0;
}
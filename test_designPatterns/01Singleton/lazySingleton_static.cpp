#include <iostream>
#include <mutex>
#include <memory>
#include <assert.h>
#include <pthread.h>
#include <thread>
#include <unistd.h>
#include <sys/syscall.h>

using namespace std;

// 局部静态变量的懒汉式
class Singleton_localStatic
{
public:
    static Singleton_localStatic* getInstance()
    {
        // 局部静态成员变量的初始化时是线程安全的，只有一个线程能执行初始化，其他线程会在此阻塞。
        // 全局的就更不用说了，全局变量是在程序一运行就进行初始化了。
        static Singleton_localStatic instance;
        // std::this_thread::sleep_for(std::chrono::seconds(3));

        return &instance;
    }

    void run()
    {
        cout << "test Singleton_localStatic, id: " << std::this_thread::get_id() << ", " << pthread_self() << endl;
    }

private:

    Singleton_localStatic()
    {
        cout << "Singleton_localStatic::Singleton_localStatic(), id: " << std::this_thread::get_id() << ", "
             << pthread_self() << endl;
        std::this_thread::sleep_for(std::chrono::seconds(3));
    } // 禁止外部构造
    ~Singleton_localStatic()
    {
        cout << "Singleton_localStatic::~Singleton_localStatic() id: " << std::this_thread::get_id() << ", "
             << pthread_self() << endl;
    } // 禁止外部析构
    Singleton_localStatic(const Singleton_localStatic& another); // 禁止外部复制
    Singleton_localStatic& operator=(const Singleton_localStatic& another); // 禁止外部赋值
};

void func(int i)
{
    Singleton_localStatic* ins = Singleton_localStatic::getInstance();

    ins->run();

    // std::this_thread::sleep_for(std::chrono::seconds(3));
}

void test_lazy_singleton_with_static_multithread()
{
    {
        pid_t lwp = static_cast<pid_t>(::syscall(SYS_gettid));

        cout << "main pid: " << getpid() << ",lwp: " << lwp << ", threadid: " << this_thread::get_id() << ", "
             << pthread_self() << endl;
        thread t[5];

        for (int i = 0; i < 5; i++) {
            t[i] = std::thread(func, i);
        }

        for (auto& i : t) {
            i.join();
        }
    }
    cout << "test_lazy_singleton_with_static_multithread end"
         << ", " << pthread_self() << endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
}

int main()
{
    test_lazy_singleton_with_static_multithread();

    return 0;
}
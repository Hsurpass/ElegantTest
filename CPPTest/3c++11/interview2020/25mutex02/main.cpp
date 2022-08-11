#include <iostream>
#include <mutex>
#include <thread>
#include <atomic>

using namespace std;
std::mutex g_mutex;
std::atomic<int> g_count(0);
class mylock
{
public:
    mylock() {
        cout << "m_mutex lock" <<endl;
        m_mutex.lock();}
    ~mylock() {
        cout << "m_mutex unlock" <<endl;
        m_mutex.unlock();}
private:
    std::mutex m_mutex;
};
void func()
{
    for(int i = 0;i <5;++i)
    {
        mylock mlock;
        g_count++;
    }
}
void foo()
{
    g_count =6;
    while(g_count > 0)
    {
        mylock mlock;
        g_count--;
        if(g_count == 5)
        {
            cout << "--------" << endl;
//            break;
            continue;
        }
    }
}
int main()
{
//    func();
//    thread t(&func);
    thread t(&foo);
    if(t.joinable())
    {
        t.join();
    }

    return 0;
}

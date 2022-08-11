#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
using namespace std;
void func()
{

}
int main()
{
//    thread t(&func);
    cout << thread::hardware_concurrency() << endl;
//    cout << thread::physical_
//    if(t.joinable())
//    {
//        cout << "t.join()" << endl;
//        t.join();
//    }
}


int main02()
{
    thread t(&func);
//    thread t1(t);
//    thread t1(std::move(t));
//    thread t1 = std::move(t);

    thread t1;
    t1 = std::move(t);
    if(t.joinable())
    {
        cout << "t.join()" << endl;
        t.join();
    }
    if(t1.joinable())
    {
        cout << "t1.join()" << endl;
        t1.join();
    }

    return 0;
}
void joinworker()
{

}
class Obj
{
public:
    Obj() {cout << "hello" << endl;}
    ~Obj() {cout << "byebye" << endl;}
};
int main01()
{
    Obj obj;
    thread t(joinworker);

    return 0;
}
#if 0
//volatile int count = 0;
 int count = 0;
//std::atomic<int> count(0);
void func()
{
    for(int i = 0;i < 100000;++i)
    {
        count++;
    }
}

int main()
{
//    unsigned int n = std::thread::hardware_concurrency();
//    cout << n << endl;

    thread t[10];
    for(int i =0;i < 10;++i)
    {
        t[i] = thread(func);
    }
    for(auto &k:t)
    {
        k.join();
    }
    cout << "count: " << count << endl;
    return 0;
}
#endif

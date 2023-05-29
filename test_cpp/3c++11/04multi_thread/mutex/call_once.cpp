#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

int g_val = -1;
int count = 0;
std::once_flag flag; 
void setVal(int x)  // 该函数只会进入一次
{   
    std::this_thread::sleep_for(std::chrono::seconds(3));
    count++;
    g_val = x;
}

void test_call_once(int id)
{
    cout << "enter test_call_once" << endl;
    std::call_once(flag, setVal, id);
    cout << "leave test_call_once" << endl;
}

int main()
{
    thread t[5];
    for (size_t i = 0; i < 5; i++)
    {
        t[i] = thread(test_call_once, i);
    }
    
    for(auto &th:t)
    {
        th.join();
    }

    cout << "g_val:" << g_val << ", count:" << count << endl;   // 随机值， 1

    return 0;
}
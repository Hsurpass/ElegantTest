#include <iostream>
#include <string>
#include <thread>

using namespace std;

void thread_func_passByReference(int &n, string &str)
{
    for (int i = 0; i < n; ++i)
    {
        cout << str << endl;
    }

    n = 100;
    str = "america";
}

void thread_func_passByValue(int n, string str)
{
    for (int i = 0; i < n; ++i)
    {
        cout << str << endl;
    }

    n = 100;
    str = "america";
}

void test_thread_detach()
{
    int n = 5;
    std::string str("china");
#if 1
    std::thread t(thread_func_passByReference, std::ref(n), std::ref(str));
#endif
#if 0
    std::thread t(thread_func_passByValue, n, str);
#endif

    t.detach();
    if (t.joinable())
    {
        cout << "joinable" << endl;
        t.join();
    }
    else
    {
        cout << "thread detached" << endl;
    }
    
    std::this_thread::sleep_for(std::chrono::seconds(2));
    //    t.join();
    cout << "n: " << n << "str: " << str << endl;
}

int main()
{
    test_thread_detach();

    return 0;
}

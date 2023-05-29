#include <iostream>
#include <string>
#include <thread>
#include <unistd.h>

using namespace std;

void thread_func_passByReference(int &n, string &str)
{
    // sleep(4);
    for (int i = 0; i < n; ++i)
    {
        cout << str << endl;
    }
    n = 100;
    str = "america";

    sleep(3);
    cout << "thread_func_passByReference, n: " << n << "str: " << str << endl;
}

void thread_func_passByValue(int n, string str)
{
    for (int i = 0; i < n; ++i)
    {
        cout << str << endl;
    }

    n = 100;
    str = "america";

    sleep(3);
    cout << "thread_func_passByReference, n: " << n << "str: " << str << endl;
}

void test_thread_detach()
{
    int n = 5;
    std::string str("china");
#if 0
    std::thread t(thread_func_passByReference, std::ref(n), std::ref(str));
#endif
#if 1
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

    n = 6;
    str = "UK";

    std::this_thread::sleep_for(std::chrono::seconds(5));
}

int main()
{
    test_thread_detach();

    return 0;
}

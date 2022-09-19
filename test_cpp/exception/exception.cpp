#include <iostream>
#include <exception>

using namespace std;

int test01()
{
    try
    {
        int *p = NULL;
        *p = 1; // linux 中对空指针操作不会捕获到异常，只会崩溃, windows中会捕获到异常（SEH）
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        cout << "exception" << endl;
        cout << "222" << endl;
    }

    return 0;
}

void test02()
{
    // c++ primer 5.6.3jie lianxi
    int v1, v2;

    // lianxi 5.23 5.24
    // cin >> v1 >> v2;
    // cout << v1 / v2 << endl;    // if v2 == 0; Floating point exception (core dumped)

    // lianxi 5.25
    while (cin >> v1 >> v2)
    {
        try
        {
            
            if (v2 == 0)
            {
                throw 0;
            }
            
            cout << v1 / v2 << endl;
        }
        catch (int a)
        {
            cout << "v2 = " << a << endl;
            cout << "exception" << endl;
            std::cerr << "try again? enter y or n" << endl;
            char c;
            cin >> c;
            if (!cin || c == 'n')
            {
                break;
            }
        }
        catch (const std::exception &e) // if v2 == 0,并不能捕获？？？
        {
            cout << "exception" << endl;
            std::cerr << e.what() << "try again? enter y or n" << endl;
            char c;
            cin >> c;
            if (!cin || c == 'n')
            {
                break;
            }
            
        }
    }
}

int main()
{
    // test01();
    test02();
    return 0;
}
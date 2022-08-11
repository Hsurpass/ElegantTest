#include <iostream>

using namespace std;

// c++ primer lianxi 5.18
void test01()
{
    do
    {
        int v1, v2;
        cout << "please enter two numbers to sum:";
        if(cin >> v1 >> v2)
            cout << "Sum is: " << v1 + v2 << endl;
    } while (cin);
    

}

int main()
{
    test01();

    return 0;
}
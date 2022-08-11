#include <iostream>

using namespace std;

int main()
{
    int i = 10, &r1 = i; 
    double d = 0, &r2 = d;
    // int &r3 = d; // error
    cout << "&i: " << &i << endl; 
    cout << "&r1: " << &r1 << endl; 


    int &tmp = r1;
    cout << "tmp:" << tmp << endl;
    cout << "i:" << i << ", r1:" << r1 << endl;

    const int &tmp1 = i;
    r1 = 100;
    cout << "tmp1:" << tmp1 << endl;
    cout << "tmp:" << tmp << endl;
    cout << "i:" << i << ", r1:" << r1 << endl;

    ////////////////////////////////////////////////////
    cout << "d:" << d << ", r2:" << r2 << endl;
    r2 = 3.14159;
    cout << "d:" << d << ", r2:" << r2 << endl;

    // r2 = r1; // type cast int to double
    // cout << "d:" << d << ", r2:" << r2 << endl;

    // i = r2; // type cast double to int
    // cout << "i:" << i << ", r1:" << r1 << endl;

    // r1 = d; // type cast double to int
    // cout << "i:" << i << ", r1:" << r1 << endl;


    int *p = &i;
    int &pr = *p;
    cout << "pr:" << pr << endl;

    return 0;
}

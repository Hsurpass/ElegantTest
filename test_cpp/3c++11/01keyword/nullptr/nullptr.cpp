#include <iostream>

using namespace std;

void func(int){cout << "func(int)" << endl;}
void func(bool){cout << "func(bool)" << endl;}
void func(void *){cout << "func(void*)" << endl;}

void test_0_NULL_nullptr()
{
    func(0);    // func(int)
    // func(NULL);  // compile error ambiguous
    func(nullptr);  // func(void*)

}

int main()
{
    test_0_NULL_nullptr();

    return 0;
}

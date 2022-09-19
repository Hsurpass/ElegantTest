#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

class A
{
public:
    char a;
    short b;
    int c;
    long d;
    float e;
    double f;
    bool g;

    std::string str;
};

struct B
{
    char a;
    short b;
    int c;
    long d;
    float e;
    double f;
    bool g;

    std::string str;
};

void test_class_struct_default_value()
{
    A ra;
    cout << ra.a << endl;
    cout << ra.b << endl;
    cout << ra.c << endl;
    cout << ra.d << endl;
    cout << ra.e << endl;
    cout << ra.f << endl;

    cout << "-------------------------" << endl;
    B rb;
    cout << rb.a << endl;
    cout << rb.b << endl;
    cout << rb.c << endl;
    cout << rb.d << endl;
    cout << rb.e << endl;
    cout << rb.f << endl;
    cout << boolalpha;
    cout << rb.g << endl;
    printf("%d\n", rb.g); 
    cout << ra.g << endl;
    printf("%d\n", rb.g); 

}

int main()
{
    test_class_struct_default_value();

    return 0;
}
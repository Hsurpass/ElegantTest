#include <iostream>
#include <stdlib.h>
#include<stdio.h>
#include<cstring>
using namespace std;

void dummyMalloc(char *p)
{
    p = (char*)malloc(8);
}
int main()
{
    char str[] = "hello world";
    dummyMalloc(str);
    strcpy(str,"Hi World\n");
    auto n = printf(str);
    cout << "n: " << n << endl;
    return 0;
}

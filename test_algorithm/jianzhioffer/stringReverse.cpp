#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>

using namespace std;

void reverseString(char* str, int n)
{
    char* p = str;
    int i = 0, j = n - 2;
    while(i < j)
    {
        char t = p[i];
        p[i] = p[j];
        p[j] = t;

        i++;
        j--;
    }

}

int main()
{
    char p[] = "hello";
    reverseString(p, sizeof(p));
    cout << p << endl;

    return 0;
}
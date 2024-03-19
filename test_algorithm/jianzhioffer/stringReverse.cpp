#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>

using namespace std;

void reverseString_recursive(char* str, int n)
{
    if (n > 1) {
        reverseString_recursive(str + 1, n - 2);

        char tmp = str[0];
        str[0] = str[n - 1];
        str[n - 1] = tmp;
    }
}

void reverseString(char* str, int n)
{
    char* p = str;
    int i = 0, j = n - 2;
    while (i < j) {
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
    cout << "sizeof(p): " << sizeof(p) << endl;    //6
    cout << "strlen(p): " << strlen(p) << endl; //5

    reverseString(p, sizeof(p));
    cout << p << endl;

    reverseString_recursive(p, strlen(p)); // 长度不能包含'\0',否则'\0'就交换到第一个位置去了。
    cout << p << endl;

    return 0;
}
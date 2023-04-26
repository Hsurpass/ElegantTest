#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

class A{
public:
    A(): str{'a', 'b', 'c', 'd', 'e', 'f'} {}
    A(const A& other) {
        memcpy(str, other.str, sizeof(other.str));
    }
    char str[6];
};

void test_class_memcpy()
{
    cout << sizeof(A) << endl;  // 1
    A a;
    cout << a.str << endl;

    A a1 = a;
    cout << a1.str << endl;
}


void testmemcpy()
{
    char str[] = "abcdefg";
    int len = sizeof(str);
    printf("len:%d\n", len);

    char *p = (char*)malloc(len);
    memcpy(p, str, len);
    printf("str:%s, p:%s, p_len:%ld\n", str, p, strlen(p));

    // free(p);    
}

int main()
{
    // testmemcpy();
    test_class_memcpy();

    return 0;
}
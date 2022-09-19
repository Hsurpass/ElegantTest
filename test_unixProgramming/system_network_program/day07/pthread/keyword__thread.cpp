#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <iostream>
#include <string>

__thread int var = 2;   //可以修饰全局变量
// __thread std::string s = "";   // error 只能修饰POD类型 error: non-local variable ‘s’ declared ‘__thread’ needs dynamic initialization
// __thread std::string s1("abc");   // error 只能修饰POD类型
// __thread std::string *s2 = new std::string("cde");   // error
// __thread std::string *s3 = NULL;    // current

class A
{
public:
    // __thread int m_a;   // 不能修饰成员变量
};

void func()
{
    printf("%d\n", var);
    // __thread int i = 10;    //不能修饰函数内局部变量
    // __thread static int b = 11; // 可以修饰静态局部变量
    static __thread int b = 11; // 可以修饰静态局部变量
    printf("%d\n", b);
}

void* worker1(void* arg)
{
    ++var;
    printf("thread-id:%lx, var:%d\n", pthread_self(), var);
}

void* worker2(void* arg)
{
    sleep(1);
    ++var;
    printf("thread-id:%lx, var:%d\n", pthread_self(), var);
}

void test___thread()
{
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, worker1, NULL);
    pthread_create(&tid2, NULL, worker2, NULL);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
}

int main()
{
    // func();
    test___thread();

    return 0;
}
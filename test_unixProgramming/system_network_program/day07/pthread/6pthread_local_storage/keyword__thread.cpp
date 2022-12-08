#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <iostream>
#include <string>

// __thread变量在每一个线程有一份独立实体，各个线程的值互不干扰。可以用来修饰那些带有全局性且值可能变，但是又不值得用全局变量保护的变量
// 其值将在线程开始时被初始化，而在线程结束时，该值也将不再有效。
__thread int var = 2;   //可以修饰全局变量
// __thread std::string s = "";   // error 只能修饰POD类型 error: non-local variable ‘s’ declared ‘__thread’ needs dynamic initialization
// __thread std::string s1("abc");   // error 只能修饰POD类型,不能调用对象的构造函数
// __thread std::string *s2 = new std::string("cde");   // error 指针类型是POD类型，但是初始化必须是编译期常量，不能是运行期的
// __thread std::string *s3 = NULL;    // currect 

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

    return NULL;
}

void* worker2(void* arg)
{
    sleep(1);
    ++var;
    printf("thread-id:%lx, var:%d\n", pthread_self(), var);

    return NULL;
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
// 互斥锁: 处理器不会因为线程被阻塞而空闲，它会去处理其它事务。
// 自旋锁是一种busy-waiting的锁。也就是说，与互斥锁相反，
// 此时运行T2的处理器core2会一直不断地循环检查是否可用（自旋锁请求），直到获得到这个自旋锁为止。

// 从“自旋锁”的名称也可以看出，如果一个线程想要获得一个被使用的自旋锁，
// 那么它会一直占用CPU请求这个自旋锁使得CPU不能去做其它的事情，
// 直到获取这个锁为止，这就是“自旋”的含义。
// 当发生阻塞时，互斥锁可以让CPU去处理其它的事务，但自旋锁让CPU一直不断循环请求获取这个锁。
// 通过比较，我们可以明显的得出结论：“自旋锁”是比较消耗CPU的。

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>

pthread_spinlock_t spinlock;

void* func(void* args)
{
    pthread_spin_lock(&spinlock);

    sleep(20);

    printf("thread[%ld] LWP[%ld] get lock\n", pthread_self(), syscall(SYS_gettid));

    pthread_spin_unlock(&spinlock);
}

void test_spin_lock()
{
    pthread_t tid1, tid2;
    pthread_spin_init(&spinlock, PTHREAD_PROCESS_PRIVATE);

    pthread_create(&tid1, NULL, func, NULL);
    pthread_create(&tid1, NULL, func, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    pthread_spin_destroy(&spinlock);
}

int main()
{
    test_spin_lock();

    return 0;
}
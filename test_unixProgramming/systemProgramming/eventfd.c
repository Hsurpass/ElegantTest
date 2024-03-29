#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/eventfd.h>
#include <errno.h>

/*
referenece:
    https://www.jianshu.com/p/f0bd843befbc
    https://www.cnblogs.com/kekukele/p/12531824.html
    https://zhuanlan.zhihu.com/p/393748176
    https://zhuanlan.zhihu.com/p/424198922

"可读可写事件" 这是个有趣的问题，我们可以去发散下，对比思考下 socket fd，文件 fd：
    socket fd：可以写入发送数据，那么触发可写事件，网卡数据来了，可以读，触发可读事件；
    文件 fd：文件 fd 的可读可写事件就更有意思了，因为文件一直是可写的，所以一直都触发可写事件，文件里的数据也一直是可读的，所以一直触发可读事件。
            这个也是为什么类似 ext4 这种文件不实现 poll 接口的原因。因为文件 fd 一直是可读可写的，poll 监听没有任何意义。
    
回到最初问题：eventfd 呢？它的可读可写事件是什么？
    我们之前说过，eventfd 实现的是计数的功能。所以 eventfd 计数不为 0 ，那么 fd 是可读的。
    由于 eventfd 一直可写（可以一直累计计数），所以一直有可写事件。
    所以，这里有个什么隐藏知识点呢？
    eventfd 如果用 epoll 监听事件，那么都是监听读事件，因为监听写事件无意义。
    
    eventfd:
        write: 写一个8字节(uint64)的整数,eventfd实现逻辑是累计计数。
        read: 读到总计数，并且清0。

    总结：
        1. eventfd内部有一个 uint64_t 的整型变量，write就是该变量自增，read就是读取该变量的值后并清零。
            - 如果eventfd设置了 EFD_SEMAPHORE 则read时读到1并且该变量自减1。
            - 如果eventfd没有设置EFD_NONBLOCK，当计数变量为0时，则会阻塞。
        2. 因为变量总是可写的，所以监听写事件没有意义；只需监听读事件即可。
*/

// 写一次，读一次
// 写入2，读出2
void test_eventfd1()
{
    int efd = eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
    // int efd = eventfd(0, EFD_CLOEXEC);
    uint64_t buf = 2;
    int ret = write(efd, &buf, sizeof(buf));
    printf("write ret:%d\n", ret);

    uint64_t count;
    ret = read(efd, &count, sizeof(count));
    printf("read ret:%d, count:%ld\n", ret, count); // 会把efd清零

    // 如果设置了NONBLOCK, 再次read就会返回-1; 如果没有设置NON_BLOCK, 则会一直阻塞
    ret = read(efd, &count, sizeof(count));
    printf("read ret:%d, count:%ld, errno:%d\n", ret, count, errno);
    perror("read");  // 11 EAGAIN;
    close(efd);
}

// 写多次，读一次
void test_eventfd2()
{
    int efd = eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
    uint64_t buf = 2;   
    uint64_t buf1 = 3;  
    uint64_t buf2 = 4;  

    int ret = write(efd, &buf, sizeof(buf));    // 写入2，计数器值为2
    printf("write ret:%d\n", ret);
    ret = write(efd, &buf1, sizeof(buf1));  // 写入3，计数器值为5
    printf("write ret:%d\n", ret);    
    ret = write(efd, &buf2, sizeof(buf2));  // 写入4，计数器值为9
    printf("write ret:%d\n", ret);

    uint64_t count;
    ret = read(efd, &count, sizeof(count));
    printf("read ret:%d, count:%ld\n", ret, count);
    close(efd);
}

// EFD_SEMAPHORE: 每次只会读取1(计数器减一)
void test_eventfd_EFD_SEMAPHORE()
{
    int efd = eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC | EFD_SEMAPHORE);
    uint64_t buf = 2;
    int ret = write(efd, &buf, sizeof(buf));    // 2
    printf("write ret:%d\n", ret);

    uint64_t count;
    ret = read(efd, &count, sizeof(count)); // 自减1
    printf("read ret:%d, count:%ld\n", ret, count); 

    count = -2;
    ret = read(efd, &count, sizeof(count)); // 自减1
    printf("read ret:%d, count:%ld, errno:%d\n", ret, count, errno);
    perror("read");

    // 如果设置了NONBLOCK, 再次read就会返回-1; 如果没有设置NON_BLOCK, 则会一直阻塞
    count = -2;
    ret = read(efd, &count, sizeof(count));
    printf("read ret:%d, count:%ld, errno:%d\n", ret, count, errno);    // -1 -2 11
    perror("read");
    close(efd);
}

// 全双工
void test_fork_eventfd_fullDuplex()
{
    // 先open再fork,共享同一个fd
    int efd = eventfd(0, 0);
    pid_t pid = fork();  
    if(pid == 0)
    {
        uint64_t buf = 2;   
        uint64_t buf1 = 3;  
        uint64_t buf2 = 4;  

        write(efd, &buf, sizeof(buf));      // 计数器值为2
        write(efd, &buf1, sizeof(buf1));    // 计数器值为5
        write(efd, &buf2, sizeof(buf2));    // 计数器值为9

        sleep(2);
        uint64_t count;
        int ret = read(efd, &count, sizeof(count)); // 24
        printf("child read, ret:%d, count:%ld\n", ret, count);
    }  
    else if (pid > 0)
    {
        sleep(1);
        uint64_t count;
        int ret = read(efd, &count, sizeof(count));
        printf("parent read ret:%d, count:%ld\n", ret, count);  // 9

        uint64_t buf = 7;   
        uint64_t buf1 = 8;  
        uint64_t buf2 = 9;  
        write(efd, &buf, sizeof(buf));      // 计数器值为7
        write(efd, &buf1, sizeof(buf1));    // 计数器值为15
        write(efd, &buf2, sizeof(buf2));    // 计数器值为24
    }
    else
    {
        perror("fork");
    }
    
    close(efd);
    exit(1);
}

int main()
{
    // test_eventfd1();
    // test_eventfd2();
    // test_eventfd_EFD_SEMAPHORE();
    test_fork_eventfd_fullDuplex();

    return 0;
}
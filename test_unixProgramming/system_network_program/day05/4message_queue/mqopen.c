#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

void test_mqopen()
{
    mqd_t mqd = mq_open("/mymqueue", O_CREAT, 0664, NULL);
    if (-1 == mqd)
    {
        perror("mq_open");
        _exit(0);
    }
    printf("create mqueue success\n");

    // get mq attr
    struct mq_attr mqattr;
    int ret = 0;
    ret = mq_getattr(mqd, &mqattr);
    if (-1 == ret)
    {
        perror("mq_getattr");
    }
    printf("nonblock flag:%ld\n", mqattr.mq_flags); // 是否是非阻塞
    printf("max msgs: %ld\n", mqattr.mq_maxmsg);    // 消息队列可以容纳的最大消息个数 默认10
    printf("max msg size: %ld\n", mqattr.mq_msgsize);   // 消息的最大字节数 默认8192
    printf("current msg count: %ld\n", mqattr.mq_curmsgs);  // 队列中当前的消息个数
    printf("--------------------------------------\n");

    // set mq attr
    mqattr.mq_maxmsg = 8;
    mqattr.mq_msgsize = 1024;
    mqattr.mq_flags = O_NONBLOCK;
    mq_setattr(mqd, &mqattr, NULL);

    printf("nonblock flag:%ld\n", mqattr.mq_flags);
    printf("max msgs: %ld\n", mqattr.mq_maxmsg);
    printf("max msg size: %ld\n", mqattr.mq_msgsize);
    printf("current msg count: %ld\n", mqattr.mq_curmsgs);

    mq_close(mqd);
    mq_unlink("/mymqueue");
}

int main()
{
    printf("mq_prio_max:%ld\n", sysconf(_SC_MQ_PRIO_MAX));  // 32768
    printf("mq_open_max:%ld\n", sysconf(_SC_MQ_OPEN_MAX));  // -1   -1表示不限制

    // test_mqopen();


    return 0;
}
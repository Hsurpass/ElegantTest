#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <list>
#include <semaphore.h>
#include <iostream>

class Task
{
public:
    Task(int taskID)
    {
        this->taskID = taskID;
    }

    void doTask()
    {
        std::cout << "handle a task, taskID: " << taskID << ", threadID: " << pthread_self() << std::endl;
    }

private:
    int taskID;
};

pthread_mutex_t mymutex;
std::list<Task*> tasks;
sem_t mysemaphore;
static int taskID = 0;

void *consumer_thread(void *param)
{
    Task *pTask = NULL;
    while (true)
    {
        if (sem_wait(&mysemaphore) != 0)
            continue;

        if (tasks.empty())
            continue;

        pthread_mutex_lock(&mymutex);
        pTask = tasks.front();
        tasks.pop_front();
        pthread_mutex_unlock(&mymutex);

        pTask->doTask();
        delete pTask;
    }

    return NULL;
}

void *producer_thread(void *param)
{
    Task *pTask = NULL;

    while (true)
    {
        pTask = new Task(taskID);

        pthread_mutex_lock(&mymutex);
        tasks.push_back(pTask);
        std::cout << "produce a task, taskID: " << taskID << ", threadID: " << pthread_self() << std::endl;
        taskID++;
        pthread_mutex_unlock(&mymutex);

        //释放信号量，通知消费者线程
        sem_post(&mysemaphore);

        //休眠1秒
        sleep(1);
    }

    return NULL;
}

void test_producer_consumer_by_sem()
{
    pthread_mutex_init(&mymutex, NULL);
    //初始信号量资源计数为0
    sem_init(&mysemaphore, 0, 0);

    //创建5个消费者线程
    pthread_t consumerThreadID[5];
    for (int i = 0; i < 5; ++i)
    {
        pthread_create(&consumerThreadID[i], NULL, consumer_thread, NULL);
    }

    //创建一个生产者线程
    pthread_t producerThreadID;
    pthread_create(&producerThreadID, NULL, producer_thread, NULL);

    pthread_join(producerThreadID, NULL);

    for (int i = 0; i < 5; ++i)
    {
        pthread_join(consumerThreadID[i], NULL);
    }

    sem_destroy(&mysemaphore);
    pthread_mutex_destroy(&mymutex);
}

int main()
{
    test_producer_consumer_by_sem();

    return 0;
}
#pragma once

#include <pthread.h>
#include <stdio.h>

class SpinMutex
{
public:
    SpinMutex()
    {
        pthread_spin_init(&spinlock, PTHREAD_PROCESS_PRIVATE);
    }
    void lock()
    {
        pthread_spin_lock(&spinlock);
    }
    void unlock()
    {
        pthread_spin_unlock(&spinlock);
    }
    ~SpinMutex()
    {
        pthread_spin_destroy(&spinlock);
    }
private:
    pthread_spinlock_t spinlock;
};

class SpinLockGuard
{
public:
    SpinLockGuard(SpinMutex& SpinMutex) : m_mutex(SpinMutex)
    {
        m_mutex.lock();
    }
    ~SpinLockGuard()
    {
        m_mutex.unlock();
    }
private:
    SpinMutex& m_mutex;
};

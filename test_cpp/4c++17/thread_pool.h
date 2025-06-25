#pragma once

#include <atomic>
#include <condition_variable>
#include <cstddef>
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

class ThreadPool
{
    using TASK = std::function<void()>;
public:
    ThreadPool(size_t numThreads) : m_stop(false)
    {}
    
private:
    std::vector<std::thread> m_workers;
    std::mutex m_mutex;
    std::queue<TASK> m_tasks;
    std::condition_variable m_condition;
    std::atomic<bool> m_stop;
};

int main()
{
    return 0;
}

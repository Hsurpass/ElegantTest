#pragma once

#include <atomic>
#include <condition_variable>
#include <cstddef>
#include <cstdio>
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <type_traits>
#include <utility>
#include <vector>

using TASK = std::function<void()>;
struct Task
{
    int priority;
    TASK task;

    bool operator<(const Task& other) const
    {
        return priority < other.priority; // Higher priority tasks should be executed first
    }
};

class ThreadPool
{
public:
    ThreadPool(size_t numThreads) : m_stop(false)
    {
        m_workers.reserve(numThreads);
        for (int i = 0; i < numThreads; ++i) {
            m_workers.emplace_back([this]() {
                while (true) {
                    Task task;
                    {
                        std::unique_lock<std::mutex> lock(m_mutex);
                        m_condition.wait(lock, [this] {
                            return m_stop || !m_tasks.empty();
                        });
                        if (m_stop && m_tasks.empty()) {
                            return;
                        }
                        task = std::move(m_tasks.top());
                        m_tasks.pop();
                    }
                    task.task();
                }
            });
        }
    }

    ~ThreadPool()
    {
        shutdown();
    }

    void shutdown()
    {
        // m_stop is std::atomic
        // {
        //     std::lock_guard<std::mutex> lock(m_mutex);
        //     m_stop = true;
        // }
        m_stop = true;
        m_condition.notify_all();
        for (std::thread& worker : m_workers) {
            if (worker.joinable()) {
                worker.join();
            }
        }
    }

    template<typename F, typename... ARGS>
    auto addTask(int priority, F&& f, ARGS&&... args) -> std::future<std::result_of_t<F(ARGS...)>>;

private:
    std::vector<std::thread> m_workers;
    std::mutex m_mutex;
    std::priority_queue<Task> m_tasks;
    std::condition_variable m_condition;
    std::atomic<bool> m_stop;
};

template<typename F, typename... ARGS>
auto ThreadPool::addTask(int priority, F&& f, ARGS&&... args) -> std::future<std::result_of_t<F(ARGS...)>>
{
    using return_type = std::result_of_t<F(ARGS...)>;
    // packaged_task is non-copyable
    // std::packaged_task<return_type()> task(std::bind(std::forward<F>(f), std::forward<ARGS>(args)...));
    // std::future<return_type> fut_res = task.get_future();

    auto task =
        std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<F>(f), std::forward<ARGS>(args)...));
    std::future<return_type> fut_res = task->get_future();

    {
        std::lock_guard<std::mutex> lock(m_mutex);
        if (m_stop) {
            printf("ThreadPool is stopped, cannot add new task.\n");
            // throw std::runtime_error("ThreadPool is stopped, cannot add new task.");
        }
        Task newTask;
        newTask.priority = priority;
        newTask.task = [task] {
            printf("thread id: %ld\n", std::this_thread::get_id());
            (*task)();
        };
        m_tasks.emplace(std::move(newTask));
    }
    m_condition.notify_one();
    return fut_res;
}

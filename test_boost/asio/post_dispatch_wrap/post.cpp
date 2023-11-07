#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/thread/thread.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <memory>
#include <mutex>

std::mutex g_mtx;

void func(int i)
{
    std::lock_guard<std::mutex> lock(g_mtx);
    std::cout << "func thread id: " << std::this_thread::get_id() << ", i: " << i << std::endl;
}

// post把任务添加到任务队列后会马上返回，然后任务由io_context进行调度
void test_post_is_or_not_block()
{
    boost::asio::io_context io_context;

    for (int i = 0; i < 5; i++) {
        io_context.post(std::bind(&func, i));
    }

    boost::thread_group threads;
    for (int i = 0; i < 3; i++) {
        threads.create_thread([&io_context]() {
            io_context.run();
        });
    }

    std::this_thread::sleep_for(std::chrono::seconds(2));
    threads.join_all();
}

int main()
{
    test_post_is_or_not_block();

    return 0;
}

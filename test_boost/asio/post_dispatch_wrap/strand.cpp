#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/thread/thread.hpp>
#include <functional>
#include <iostream>
#include <thread>
#include <chrono>
#include <memory>
#include <boost/thread.hpp>

void func(int i)
{
    printf("strand func thread id: %ld, i:%d\n", std::this_thread::get_id(), i);
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void test_keep_order_by_strand()
{
    boost::asio::io_context io_context;
    boost::asio::io_context::strand strand_one(io_context), strand_two(io_context);

    // 前5个保持顺序
    for (int i = 0; i < 5; i++) {
        io_context.post(strand_one.wrap(std::bind(&func, i)));
        // strand_one.wrap(std::bind(&func, i))();
        // strand_one.post(std::bind(&func, i));
        // io_context.post(io_context.wrap(std::bind(&func, i)));//没有strand是不保证顺序的
        // io_context.wrap(std::bind(&func, i))(); //没有strand是不保证顺序的
    }

    // 后5个保持顺序,但是不意味着它们是在一个线程中执行的，
    // 也不意味着后五个一定会在前五个的后面执行。
    for (int i = 5; i < 10; i++) {
        io_context.post(strand_two.wrap(std::bind(&func, i)));
        // strand_one.wrap(std::bind(&func, i))();
        // strand_two.dispatch(std::bind(&func, i));
        // strand_two.post(std::bind(&func, i));
        // io_context.post(io_context.wrap(std::bind(&func, i)));//没有strand是不保证顺序的
        // io_context.wrap(std::bind(&func, i))();//没有strand是不保证顺序的
    }

    std::this_thread::sleep_for(std::chrono::seconds(2));

    boost::thread_group threads;
    for (int i = 0; i < 10; i++) {
        threads.create_thread([&io_context]() {
            io_context.run();
        });
    }

    std::this_thread::sleep_for(std::chrono::seconds(2));

    threads.join_all();
}

int main()
{
    test_keep_order_by_strand();

    return 0;
}
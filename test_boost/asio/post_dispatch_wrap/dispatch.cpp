#include <boost/asio.hpp>
#include <cstdio>
#include <iostream>
#include <chrono>
#include <thread>

void dispatch_func()
{
    printf("dispatch_func thread id:%ld\n", std::this_thread::get_id());
    std::this_thread::sleep_for(std::chrono::seconds(3));
}

void post_func1()
{
    printf("post_func1 thread id:%ld\n", std::this_thread::get_id());
    std::this_thread::sleep_for(std::chrono::seconds(3));
}
void post_func2()
{
    printf("post_func2 thread id:%ld\n", std::this_thread::get_id());
}

void test_dispatch_is_block_and_run_now()
{
    boost::asio::io_context io_context;
    printf("main thread id:%ld\n", std::this_thread::get_id());

    // post把异步任务添加到io_context会马上返回。
    // io_context.post(std::bind(&post_func1));

    std::cout << "start add dispatch..." << std::endl;
    // 如果当前线程被占用，则返回等待io_context调度；如果当前没被占用则立即执行任务，dispatch返回不会阻塞。
    io_context.dispatch(std::bind(dispatch_func));
    std::cout << "end add dispatch..." << std::endl;

    io_context.post(std::bind(post_func2));
    std::cout << "end" << std::endl;

    io_context.run();

    // std::thread t([&io_context]() {
    //     io_context.run();
    // });

    // t.join();
}

void func_dispatch(int i)
{
    std::cout << "func_dispatch called, thread id:" << std::this_thread::get_id() << " i= " << i << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
}

void func_post(int i)
{
    std::cout << "func_post called, thread id:" << std::this_thread::get_id() << " i= " << i << std::endl;
}

void run_dispatch_and_post()
{
    boost::asio::io_context service;

    for (int i = 0; i < 10; i += 2) {
        service.dispatch(std::bind(func_dispatch, i));
        service.post(std::bind(func_post, i + 1));
    }
    std::cout << "add task finish" << std::endl;

    service.run();
}

int main()
{
    // test_dispatch_is_block_and_run_now();
    run_dispatch_and_post();

    return 0;
}
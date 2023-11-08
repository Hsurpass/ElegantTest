// #define BOOST_ASIO_ENABLE_HANDLER_TRACKING

#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/read.hpp>
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

int g_count = 0;
void add(int num)
{
    printf("task[%d], thread_id:%ld, g_count:%d\n", num, std::this_thread::get_id(), g_count);

    for (int i = 0; i < 10000; i++) {
        g_count++;
    }
    printf("task[%d], thread_id:%ld, g_count:%d\n", num, std::this_thread::get_id(), g_count);
    // std::this_thread::sleep_for(std::chrono::seconds(2));
}
// 多个线程使用strand.post()函数向同一个strand添加任务不会发生数据竞争，而且只会在同一个线程中按照顺序执行。
// 只要任务被添加到同一个strand中，那么就只能串行执行，不管是哪个线程添加的
void test_multithread_add_task_to_one_strand()
{
    boost::asio::io_context io_context;
    boost::asio::io_context::strand strand_one(io_context);
    // 前5个保持顺序
    for (int i = 0; i < 5; i++) {
        printf("main thread id:%ld, start post task\n", std::this_thread::get_id());
        // io_context.post(strand_one.wrap(std::bind(&func, i)));
        // strand_one.wrap(std::bind(&func, i))();
        strand_one.post(std::bind(&add, i));
        printf("main thread id:%ld, finish post task\n", std::this_thread::get_id());
    }

    std::thread t([&strand_one]() {
        printf("thread t id:%ld, start post task\n", std::this_thread::get_id());
        for (int i = 5; i < 10; i++) {
            strand_one.post(std::bind(&add, i));
        }
        printf("thread t id:%ld, finish post task\n", std::this_thread::get_id());
    });

    std::thread t1([&strand_one]() {
        printf("thread t1 id:%ld, start post task\n", std::this_thread::get_id());
        for (int i = 10; i < 15; i++) {
            strand_one.post(std::bind(&add, i));
        }
        printf("thread t1 id:%ld, finish post task\n", std::this_thread::get_id());
    });

    std::thread t2([&strand_one]() {
        printf("thread t2 id:%ld, start post task\n", std::this_thread::get_id());
        for (int i = 15; i < 20; i++) {
            strand_one.post(std::bind(&add, i));
        }
        printf("thread t2 id:%ld, finish post task\n", std::this_thread::get_id());
    });

    std::this_thread::sleep_for(std::chrono::seconds(2));

    boost::thread_group threads;
    for (int i = 0; i < 3; i++) {
        threads.create_thread([&io_context]() {
            io_context.run();
        });
    }

    std::this_thread::sleep_for(std::chrono::seconds(2));

    t.join();
    t1.join();
    t2.join();
    threads.join_all();
}

// 两个strand中有各自的任务，每个strand只保证自己队列中任务是有序的；
// 由于io_context只在一个线程中执行，两个strand不能并行执行，只能交替执行。
void test_one_thread_two_strand_post()
{
    boost::asio::io_context io_context;
    boost::asio::io_context::strand strand_one(io_context), strand_two(io_context);

    for (int i = 0; i < 5; i++) {
        printf("main thread id:%ld, strand_one start post task\n", std::this_thread::get_id());
        // io_context.post(strand_one.wrap(std::bind(&func, i)));
        // strand_one.wrap(std::bind(&func, i))();
        strand_one.post(std::bind(&add, i));
        printf("main thread id:%ld, strand_one finish post task\n", std::this_thread::get_id());
    }
    // 两个strand中有各自的任务，每个strand只保证自己队列中任务是有序的；
    // 由于io_context只在一个线程中执行，两个strand不能并行执行。
    for (int i = 5; i < 10; i++) {
        printf("main thread id:%ld, strand_two start post task\n", std::this_thread::get_id());
        // io_context.post(strand_one.wrap(std::bind(&func, i)));
        // strand_one.wrap(std::bind(&func, i))();
        strand_two.post(std::bind(&add, i));
        printf("main thread id:%ld, strand_two finish post task\n", std::this_thread::get_id());
    }

    io_context.run();

    std::this_thread::sleep_for(std::chrono::seconds(2));
}

// 多个线程执行io_service::run(), 两个strand有各自的任务，这种场景下：
// 这两个strand可以由io_context调度在两个线程上并行执行，并且各个strand保证自己任务的执行顺序。
// 但是两个strand不是原子性的，如果他们当中的任务访问共享资源，会发生数据竞争。
void test_multi_thread_two_strand_post()
{
    boost::asio::io_context io_context;
    boost::asio::io_context::strand strand_one(io_context), strand_two(io_context);

    for (int i = 0; i < 5; i++) {
        printf("main thread id:%ld, strand_one start post task\n", std::this_thread::get_id());
        // io_context.post(strand_one.wrap(std::bind(&func, i)));
        // strand_one.wrap(std::bind(&func, i))();
        strand_one.post(std::bind(&add, i));
        printf("main thread id:%ld, strand_one finish post task\n", std::this_thread::get_id());
    }
    // 两个strand中有各自的任务，每个strand只保证自己队列中任务是有序的；
    for (int i = 5; i < 10; i++) {
        printf("main thread id:%ld, strand_two start post task\n", std::this_thread::get_id());
        // io_context.post(strand_one.wrap(std::bind(&func, i)));
        // strand_one.wrap(std::bind(&func, i))();
        strand_two.post(std::bind(&add, i));
        printf("main thread id:%ld, strand_two finish post task\n", std::this_thread::get_id());
    }

    // std::thread t1([&strand_one]() {
    //     printf("thread t1 id:%ld, start post task\n", std::this_thread::get_id());
    //     for (int i = 10; i < 15; i++) {
    //         strand_one.post(std::bind(&add, i));
    //     }
    //     printf("thread t1 id:%ld, finish post task\n", std::this_thread::get_id());
    // });

    // std::this_thread::sleep_for(std::chrono::seconds(2));

    boost::thread_group threads;
    for (int i = 0; i < 3; i++) {
        threads.create_thread([&io_context]() {
            io_context.run();
        });
    }

    std::this_thread::sleep_for(std::chrono::seconds(2));

    // t1.join();
    threads.join_all();
}

void test_multiIorun_multipost_onestrand_wrap()
{
    boost::asio::io_context io_context;
    boost::asio::io_context::strand strand_one(io_context), strand_two(io_context);

    printf("main thread id:%ld, strand_one start post task\n", std::this_thread::get_id());
    for (int i = 0; i < 5; i++) {
        // strand_one.wrap(std::bind(&add, i))所包装成的对象由io_context调度到某个线程去执行，
        // 然后执行strand_one.wrap(std::bind(&add, i))() == strand_one.dispatch(std::bind(&add, i))
        // 这样一来添加到strand队列中的任务顺序就不一定是0,1,2,3...
        // 但是同一strand中的任务一定是在一个线程中执行。
        // io_context.post(strand_one.wrap(std::bind(&add, i)));
        io_context.dispatch(strand_one.wrap(std::bind(&add, i)));
    }
    printf("main thread id:%ld, strand_one finish post task\n", std::this_thread::get_id());

    std::thread t1([&io_context, &strand_one]() {
        printf("thread t1 id:%ld, start post task\n", std::this_thread::get_id());
        for (int i = 5; i < 10; i++) {
            io_context.post(strand_one.wrap(std::bind(&add, i)));
        }
        printf("thread t1 id:%ld, finish post task\n", std::this_thread::get_id());
    });

    boost::thread_group threads;
    for (int i = 0; i < 3; i++) {
        threads.create_thread([&io_context]() {
            io_context.run();
        });
    }

    std::this_thread::sleep_for(std::chrono::seconds(2));

    t1.join();
    threads.join_all();
}

// 因为只有一个线程执行io::run(),即使有两个strand，它们中的任务也不会发生竞争
void test_oneThreadIo_post_two_strandWrap()
{
    boost::asio::io_context io_context;
    boost::asio::io_context::strand strand_one(io_context), strand_two(io_context);

    printf("main thread id:%ld, strand_one start post task\n", std::this_thread::get_id());
    for (int i = 0; i < 5; i++) {
        io_context.post(strand_one.wrap(std::bind(&add, i)));
    }
    printf("main thread id:%ld, strand_one finish post task\n", std::this_thread::get_id());

    // 两个strand中有各自的任务，每个strand只保证自己队列中任务是有序的；
    // 由于io_context只在一个线程中执行，两个strand不能并行执行。
    printf("main thread id:%ld, strand_two start post task\n", std::this_thread::get_id());
    for (int i = 5; i < 10; i++) {
        // io_context.post(strand_one.wrap(std::bind(&func, i)));
        // strand_one.wrap(std::bind(&func, i))();
        strand_two.post(std::bind(&add, i));
    }
    printf("main thread id:%ld, strand_two finish post task\n", std::this_thread::get_id());

    io_context.run();

    std::this_thread::sleep_for(std::chrono::seconds(2));
}

// 多个线程执行io_service::run(), 两个strand有各自的任务，这种场景下：
// 这两个strand可以由io_context调度在两个线程上并行执行，并且各个strand保证自己任务的执行顺序。
// 但是两个strand不是原子性的，如果他们当中的任务访问共享资源，会发生数据竞争。
void test_multithreadIo_post_twostrandWrap()
{
    boost::asio::io_context io_context;
    boost::asio::io_context::strand strand_one(io_context), strand_two(io_context);

    printf("main thread id:%ld, strand_one start post task\n", std::this_thread::get_id());
    for (int i = 0; i < 5; i++) {
        io_context.post(strand_one.wrap(std::bind(&add, i)));
    }
    printf("main thread id:%ld, strand_one finish post task\n", std::this_thread::get_id());

    // 两个strand中有各自的任务，每个strand只保证自己队列中任务是有序的；
    printf("main thread id:%ld, strand_two start post task\n", std::this_thread::get_id());
    for (int i = 5; i < 10; i++) {
        io_context.post(strand_two.wrap(std::bind(&add, i)));
    }
    printf("main thread id:%ld, strand_two finish post task\n", std::this_thread::get_id());

    // std::thread t1([&strand_one]() {
    //     printf("thread t1 id:%ld, start post task\n", std::this_thread::get_id());
    //     for (int i = 10; i < 15; i++) {
    //         strand_one.post(std::bind(&add, i));
    //     }
    //     printf("thread t1 id:%ld, finish post task\n", std::this_thread::get_id());
    // });

    // std::this_thread::sleep_for(std::chrono::seconds(2));

    boost::thread_group threads;
    for (int i = 0; i < 3; i++) {
        threads.create_thread([&io_context]() {
            io_context.run();
        });
    }

    std::this_thread::sleep_for(std::chrono::seconds(2));

    // t1.join();
    threads.join_all();
}

int main()
{
    // test_keep_order_by_strand();
    // test_multithread_add_task_to_one_strand();
    // test_one_thread_two_strand_post();
    // test_multi_thread_two_strand_post();

    // test_multiIorun_multipost_onestrand_wrap();
    // test_oneThreadIo_post_two_strandWrap();
    test_multithreadIo_post_twostrandWrap();

    return 0;
}
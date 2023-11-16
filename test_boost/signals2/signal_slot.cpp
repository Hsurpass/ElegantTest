#include <boost/signals2/detail/slot_groups.hpp>
#include <iostream>
#include <boost/signals2.hpp>

// using namespace std;

class Hello
{
public:
    void operator()() const
    {
        std::cout << "hello" << std::endl;
    }
};

class World
{
public:
    void operator()() const
    {
        std::cout << "world" << std::endl;
    }
};

void test_signal_slotS()
{
    boost::signals2::signal<void()> sig;

    Hello hello;
    World world;
    sig.connect(hello);
    sig.connect(world);

    sig();
}

void func1()
{
    std::cout << "func1" << std::endl;
}

void func2()
{
    std::cout << "func2" << std::endl;
}

void func3(int i)
{
    std::cout << "func" << i << std::endl;
}

// func3
// func1
// world
// func2
// hello
// lambda
void test_signal_slotS_group()
{
    boost::signals2::signal<void()> sig;

    Hello hello;
    World world;
    sig.connect(1, hello);
    sig.connect(0, world);
    sig.connect(1, []() {
        std::cout << "lambda" << std::endl;
    });

    sig.connect(0, func1, boost::signals2::at_front);
    sig.connect(0, std::bind(func2), boost::signals2::at_back);
    sig.connect(0, std::bind(func3, 3), boost::signals2::at_front);

    sig();
}

void func4()
{
    std::cout << "func4" << std::endl;
}

void func5()
{
    std::cout << "func5" << std::endl;
}

// func5
// func1
// world
// hello
// lambda
// func4
// slot执行顺序：
// 1.ungrouped at_front
// 2.grouped orders
// 3.ungrouped at_back
void test_signal_slotS_group_ungroup()
{
    boost::signals2::signal<void()> sig;

    // ungrouped
    sig.connect(func4); // 默认是at_back
    Hello hello;
    World world;
    // grouped
    sig.connect(1, hello);
    sig.connect(0, world);
    sig.connect(1, []() {
        std::cout << "lambda" << std::endl;
    });

    sig.connect(0, func1, boost::signals2::at_front);

        // ungrouped
    sig.connect(func5, boost::signals2::at_front);

    sig();
}

int main()
{
    // test_signal_slotS();
    // test_signal_slotS_group();
    test_signal_slotS_group_ungroup();

    return 0;
}
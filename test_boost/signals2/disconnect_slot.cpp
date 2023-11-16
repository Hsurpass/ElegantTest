#include <algorithm>
#include <boost/signals2/connection.hpp>
#include <boost/signals2/shared_connection_block.hpp>
#include <cstdio>
#include <iostream>
#include <boost/signals2.hpp>
#include <boost/optional/optional_io.hpp>
#include <iterator>
#include <ostream>

using namespace std;

class Hello
{
public:
    void operator()() const
    {
        std::cout << "hello" << std::endl;
    }
};

void disconnect_slot()
{
    boost::signals2::signal<void()> sig;

    boost::signals2::connection c = sig.connect(Hello());
    std::cout << "c is connected\n";
    sig(); // Prints "Hello, World!"

    c.disconnect(); // Disconnect the HelloWorld object
    std::cout << "c is disconnected\n";
    sig(); // Does nothing: there are no connected slots
}

void blocking_slot()
{
    boost::signals2::signal<void()> sig;
    boost::signals2::connection c = sig.connect(Hello());
    std::cout << "c is not blocked.\n";
    sig(); // Prints "Hello, World!"

    {
        boost::signals2::shared_connection_block block(c);
        std::cout << "c is blocked.\n";
        sig(); // No output: the slot is blocked
    }// shared_connection_block going out of scope unblocks the slot
    std::cout << "c is not blocked.\n";
    sig(); // Prints "Hello, World!"}
}

void scope_connection()
{
    boost::signals2::signal<void()> sig;

    {
        boost::signals2::scoped_connection c(sig.connect(Hello()));
        sig();
    }
    sig();

    boost::signals2::scoped_connection c0 = sig.connect(Hello());   // compile right
    boost::signals2::scoped_connection c2;
    c2 = sig.connect(Hello());      // compile right
}

void foo()
{
    std::cout << "foo";
}
void bar()
{
    std::cout << "bar\n";
}

void foo_()
{
    std::cout << "foo_";
}
void bar_()
{
    std::cout << "bar_\n";
}
void disconnect_one_slot()
{
    boost::signals2::signal<void()> sig;

    sig.connect(&foo);
    sig.connect(&bar);

    sig.connect(0, &foo_);
    sig.connect(0, &bar_);

    sig();

    // disconnects foo, but not bar
    // sig.disconnect(&foo);
    sig.disconnect(0);    // disconnect all
    sig();
}

int main()
{
    // disconnect_slot();
    // blocking_slot();
    // scope_connection();
    disconnect_one_slot();

    return 0;
}
#include <iostream>
#include <boost/signals2.hpp>

using namespace std;

void print_args(float x, float y)
{
    std::cout << "The arguments are " << x << " and " << y << std::endl;
}

void print_sum(float x, float y)
{
    std::cout << "The sum is " << x + y << std::endl;
}

void print_product(float x, float y)
{
    std::cout << "The product is " << x * y << std::endl;
}

void print_difference(float x, float y)
{
    std::cout << "The difference is " << x - y << std::endl;
}

void print_quotient(float x, float y)
{
    std::cout << "The quotient is " << x / y << std::endl;
}

void test_pass_value()
{
    boost::signals2::signal<void(float, float)> sig;

    sig.connect(&print_args);
    sig.connect(&print_sum);
    sig.connect(&print_product);
    sig.connect(&print_difference);
    sig.connect(&print_quotient);

    sig(5, 3);
}

int main()
{
    test_pass_value();
    
    return 0;
}

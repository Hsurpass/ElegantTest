#include <algorithm>
#include <cstdio>
#include <iostream>
#include <boost/signals2.hpp>
#include <boost/optional/optional_io.hpp>
#include <iterator>
#include <ostream>

using namespace std;

float product(float x, float y)
{
    return x * y;
}
float quotient(float x, float y)
{
    return x / y;
}
float sum(float x, float y)
{
    return x + y;
}
float difference(float x, float y)
{
    return x - y;
}

void test_sig_return_val()
{
    boost::signals2::signal<float(float, float)> sig;

    sig.connect(&product);
    sig.connect(&quotient);
    sig.connect(&sum);
    sig.connect(&difference);

    auto r = sig(5, 3);
    cout << r << endl;
}

// combiner which returns the maximum value returned by all slots
template<typename T>
struct maximum
{
    typedef T result_type;

    template<typename InputIterator>
    T operator()(InputIterator first, InputIterator last) const
    {
    // If there are no slots to call, just return the
    // default-constructed value
        if (first == last)
            return T();
        T max_value = *first++;
        while (first != last) {
            if (max_value < *first)
                max_value = *first;
            ++first;
        }

        return max_value;
    }
};

void test_sig_return_max_val()
{
    boost::signals2::signal<float(float, float), maximum<float>> sig;

    sig.connect(&product);
    sig.connect(&quotient);
    sig.connect(&sum);
    sig.connect(&difference);

    auto r = sig(5, 3);
    cout << r << endl;
}

// aggregate_values is a combiner which places all the values returned
// from slots into a container
template<typename Container>
struct aggregate_values
{
    typedef Container result_type;

    template<typename InputIterator>
    Container operator()(InputIterator first, InputIterator last) const
    {
        Container values;

        while (first != last) {
            values.push_back(*first);
            ++first;
        }
        return values;
    }
};

void test_sig_return_all_val()
{
    boost::signals2::signal<float(float, float), aggregate_values<std::vector<float>>> sig;

    sig.connect(&product);
    sig.connect(&quotient);
    sig.connect(&sum);
    sig.connect(&difference);

    auto r = sig(5, 3);
    std::copy(r.begin(), r.end(), std::ostream_iterator<float>(std::cout, " "));
    putchar(10);
}

int main()
{
    // test_sig_return_val();   // 默认返回最后被调用的slot的值。
    // test_sig_return_max_val();  //
    test_sig_return_all_val();

    return 0;
}
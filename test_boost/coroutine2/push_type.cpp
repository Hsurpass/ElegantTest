// g++ -g push_type.cpp -lboost_coroutine -lboost_context

#include <functional>
#include <iostream>
#include <iomanip>
#include <tuple>
#include <vector>
#include <string>
#include <utility>

#include <boost/coroutine2/all.hpp>

struct FinalEOL
{
    ~FinalEOL()
    {
        std::cout << std::endl;
    }
};

void set_layout()
{
    using std::begin;
    using std::end;
    std::vector<std::string> words{"peas",
                                   "porridge",
                                   "hot",
                                   "peas",
                                   "porridge",
                                   "cold",
                                   "peas",
                                   "porridge",
                                   "in",
                                   "the",
                                   "pot",
                                   "nine",
                                   "days",
                                   "old"};
    int num = 5, width = 15;
    boost::coroutines2::coroutine<std::string>::push_type writer(
        [&](boost::coroutines2::coroutine<std::string>::pull_type& in) {
            // finish the last line when we leave by whatever means
            FinalEOL eol;
            // pull values from upstream, lay them out 'num' to a line
            for (;;) {
                for (int i = 0; i < num; ++i) {
                    // when we exhaust the input, stop
                    if (!in)
                        return;
                    std::cout << std::setw(width) << in.get();
                    // now that we've handled this item, advance to next
                    in();
                }
                // after 'num' items, line break
                std::cout << std::endl;
            }
        });

    std::copy(begin(words), end(words), begin(writer));
    std::cout << "\nDone";
}

void get_int_val(boost::coroutines2::coroutine< int >::pull_type& pull)
{

    for (auto& i : pull) {
        std::cout << "pull " << i << std::endl;
    }
}

void test_pass_val()
{

    // boost::coroutines2::coroutine<int>::push_type push(get_int_val);
    boost::coroutines2::coroutine<int>::push_type push(std::bind(&get_int_val, std::placeholders::_1));

    std::vector<int> v = {0, 1, 2, 3, 4, 5, 6};
    for (auto i : v) {
        std::cout << "push " << i << std::endl;
        push(i);
    }
}

void get_tuple_val(boost::coroutines2::coroutine<std::tuple<int, std::string> >::pull_type& pull)
{
    while (pull) {
        // auto r = pull.get();
        // auto&& r = pull.get();
        // std::cout << std::get<0>(r) << ", " << std::get<1>(r) << std::endl;
        int i;
        std::string s;
        std::tie(i, s) = pull.get();
        std::cout << i << ", " << s << std::endl;

        pull();
    }
}

void test_pass_tuple()
{

    boost::coroutines2::coroutine<std::tuple<int, std::string>>::push_type push(get_tuple_val);

    push(std::make_tuple(1, "abc"));
}

int main(int argc, char* argv[])
{
    // set_layout();
    // test_pass_val();
    test_pass_tuple();

    return EXIT_SUCCESS;
}
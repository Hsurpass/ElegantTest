#include <iostream>
#include <coroutine>
#include <future>

using namespace std;

class Result
{
public:
    class promise_type
    {
    public:
        std::suspend_always initial_suspend()
        {
            return {};
        }
        suspend_never final_suspend() noexcept
        {
            return {};
        }
        Result get_return_object()
        {
            return {};
        }
        void unhandled_exception()
        {}
    };
};

class Input
{
public:
    bool await_ready()
    {
        return false;
    }
    void await_suspend(coroutine_handle<> handle)
    {}

    int await_resume()
    {
        return 0;
    }
};

Result test_coroutine(int a, int b)
{
    Input input;
    co_await input;

    cout << "coroutine task" << endl;
}

int main()
{
    auto fut = test_coroutine(2, 3);

    return 0;
}
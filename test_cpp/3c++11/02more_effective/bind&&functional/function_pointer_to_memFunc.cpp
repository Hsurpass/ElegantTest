#include <iostream>
#include <functional>

using namespace std;
using namespace std::placeholders;

class A
{
public:
    void dis() { cout << "A::dis()" << endl; }

private:
    int m_a;
};

class B
{
public:
    void dis() { cout << "B::dis()" << endl; }

private:
    int m_a;
};

class C
{
public:
    void dis(int a, double b) { cout << "C::dis(int a, double b)" << endl; }

private:
    int m_a;
};

// 测试muduo WeakCallback
#if 1
template <typename T>
void functionTemplate(const function<void(T *)> ft, T *obj)
{
    ft(obj);
}
#endif

#if 1
template <typename T, typename... ARGS> //类型包
void functionTemplate02(const function<void(T *, ARGS...)> &ft /*, T* obj, ARGS&&... args*/ /*参数包*/)
{
    // cout << sizeof...(ARGS) << " " << sizeof...(args) << endl;
    // ft(obj);
}

template <typename CLASS, typename... ARGS>
class WeakCallback
{
public:
    WeakCallback(const std::function<void(CLASS *, ARGS...)> &function)
        : function_(function)
    {
    }

private:
    std::function<void(CLASS *, ARGS...)> function_;
};
#endif

template <typename T, typename... ARGS> //类型包
void funcTemplate(void (T::*func)(ARGS...), T *obj, ARGS&&...args)
{
    cout << "sizeof...(ARGS):" << sizeof...(ARGS) << endl;
    (obj->*func)(std::forward<ARGS>(args)...);

    // function<void (T*, ARGS...)> ft = func;
    // functionTemplate02<T, ARGS...>(func);
    WeakCallback<T, ARGS...>(func);
}

void test_function_pointer_to_memFunc_with_template02()
{
    A a;
    B b;
    C c;

    funcTemplate(&A::dis, &a);
    funcTemplate(&B::dis, &b);
    funcTemplate(&C::dis, &c, 10, 12.1);
}

void test_function_pointer_to_memFunc_with_template()
{
    A a;
    B b;
    void (A::*pa)() = &A::dis;
    void (B::*pb)() = &B::dis;

    functionTemplate<A>(pa, &a);
    functionTemplate<B>(pb, &b);

    functionTemplate<A>(&A::dis, &a);
    functionTemplate<B>(&B::dis, &b);
}

// 测试muduo WeakCallback
void test_function_pointer_to_memFunc()
{
    std::function<void(void)> f;
    std::function<void(A *)> f1;

    A a;
    void (A::*pf)() = &A::dis;
    (a.*pf)();

    f = bind(&A::dis, &a);
    f();

    f1 = pf;
    f1(&a);

    f1 = &A::dis;
    f1(&a);

    f1 = bind(&A::dis, std::placeholders::_1);
    f1(&a);

    f1 = bind(&A::dis, &a);
    f1(&a);
}

int main()
{
    // test_function_pointer_to_memFunc();
    // test_function_pointer_to_memFunc_with_template();
    test_function_pointer_to_memFunc_with_template02();

    return 0;
}

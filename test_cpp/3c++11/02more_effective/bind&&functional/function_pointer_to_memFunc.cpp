#include <iostream>
#include <functional>
#include <memory>

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
#if 0
template <typename T>
void functionTemplate(const function<void(T *)> ft, T *obj)
{
    ft(obj);
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
#endif

#if 1
template <typename T, typename... ARGS> //类型包
void functionTemplate02(const T* obj, const std::function<void(T *, ARGS...)>& ft /*,  ARGS&&... args*/ /*参数包*/)
{
    // cout << sizeof...(ARGS) << " " << sizeof...(args) << endl;
    // ft(obj);
}

  template <typename CLASS, typename... ARGS>
  class WeakCallback
  {
  public:
    WeakCallback(const std::weak_ptr<CLASS> &object,
                 const std::function<void(CLASS *, ARGS...)> &function)
        : object_(object), function_(function)
    {
        cout << "object_.use_count:" << object_.use_count() << endl;
        cout << sizeof...(ARGS) << endl;
        cout << "WeakCallback(const std::function<void(CLASS *, ARGS...)> &function))" << endl;
    }

    // Default dtor, copy ctor and assignment are okay

    void operator()(ARGS &&...args) const
    {
      std::shared_ptr<CLASS> ptr(object_.lock()); // 使用weak_ptr可以保证安全的调用回调函数，也就是调用成员函数时，类对象还存在。
      if (ptr)
      {
        function_(ptr.get(), std::forward<ARGS>(args)...);
      }
      // else
      // {
      //   LOG_TRACE << "expired";
      // }
    }

  private:
    std::weak_ptr<CLASS> object_;
    std::function<void(CLASS *, ARGS...)> function_;
  };

template <typename T, typename... ARGS> //类型包
void funcTemplate(void (T::*func)(ARGS...), T *obj, ARGS&&...args)
{
    cout << "sizeof...(ARGS):" << sizeof...(ARGS) << endl;
    (obj->*func)(std::forward<ARGS>(args)...);

    {
        shared_ptr<T> spt(obj);
        WeakCallback<T, ARGS...>(spt, func);
        cout << spt.use_count() << endl;
    }   // 这里把栈上的内存给释放了，所以会崩

    // functionTemplate02<T, ARGS...>(obj, func);
}

template <typename T, typename... ARGS> //类型包
void funcTemplate0(void (T::*func)(ARGS...) )
{
    cout << "sizeof...(ARGS):" << sizeof...(ARGS) << endl;
}

void test_function_pointer_to_memFunc_with_template02()
{
    A a;
    B b;
    C c;

    funcTemplate0(&A::dis);
    funcTemplate0(&B::dis);
    funcTemplate0(&C::dis);
    cout << "-----------------------------" << endl;

    funcTemplate(&A::dis, &a);
    funcTemplate(&B::dis, &b);
    funcTemplate(&C::dis, &c, 10, 12.1);
}
#endif

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

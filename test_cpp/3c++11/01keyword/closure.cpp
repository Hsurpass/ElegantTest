#include <iostream>
#include <vector>
#include <functional>

using namespace std;

auto lazy_sum()
{
    int sum = 0;
    // return [=](int val) {// error 要修改外层函数变量的值需要加mutable, 不加mutable编译报错
    // return [&](int val) { //改成引用类型，总是引用的sum=0值，不会累加
    return [=](int val) mutable { //其实就是lambda所生成对象内部有个sum在累加，和外层函数的sum没关系了（仿闭包）
        sum += val;
        return sum;
    };
}

void testClosure01()
{
    auto sum = lazy_sum();
    cout << sum(0) << endl; // 0
    cout << sum(1) << endl; // 1
    cout << sum(2) << endl; // 3
    cout << sum(3) << endl; // 6
    cout << sum(4) << endl; // 10

    for (int i = 0; i < 5; i++) {
        printf("%d ", sum(i)); // 10 11 13 16 20
        // cout << sum(i) << " ";
    }
    cout << endl;
}

auto sum_(int* arr, int n)
{
    int sum = 0;
    return [=]() mutable {
        for (int i = 0; i < n; i++) { // 形参也属于外层函数的变量
            sum += arr[i];
        }
        return sum;
    };
}

void testClosure02()
{
    int arr[5] = {0, 1, 2, 3, 4};
    auto sum = sum_(arr, 5);
    cout << sum() << endl; //10
}

typedef int (*pf)();
typedef function<int()> PF;
std::vector<PF> funcArr()
{
    vector<PF> vpf;
    for (int i = 0; i < 3; i++) {
        PF f = [i]() -> int { //闭包拷贝了i值 lambda表达式相当于拷贝i值构造了一个对象
            // PF f = [=]() -> int {   //闭包拷贝了i值
            // PF f = [&]() -> int { //引用了i值，数据：9 481100356 481100356 ？？？// 改用引用的话，等调用时栈变量就释放了
            return i * i;
        };
        vpf.push_back(f);
    }

    return vpf;
}

void testClosure03()
{
    vector<PF> v = funcArr();
    for (auto& f : v) {
        cout << f() << endl; // 0 1 4
    }
}

class A
{
public:
    A() : i(100)
    {
        cout << "A()" << endl;
    }

    A(const A& other)
    {
        cout << "A(const A& other)" << endl;
    }
    A& operator=(const A& other)
    {
        cout << "A& operator=(const A& other)" << endl;
        return *this;
    }

    ~A()
    {
        cout << "~A()" << endl;
    }
public:
    int i;
};

typedef function<void()> voidPF;
// voidPF func1()
auto func1()
{
    A a;

    // voidPF func2 = [=]() {  // 改用引用的话，等调用时栈变量就释放了
    return [a]() {
        cout << a.i << endl;
    };

    // return func2;
}

void testClosure04()
{
    auto f = func1();
    f();
}

int main()
{
    // testClosure01();
    // testClosure02();
    testClosure03();
    // testClosure04();

    return 0;
}
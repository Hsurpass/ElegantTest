#include <iostream>
#include <vector>

using namespace std;

class Copy
{
public:
    Copy(int i = 10) : _i(new int(i))
    {
        cout << "Copy(int i)" << this << endl;
    }
    // 若拷贝自实现，移动默认即无
    Copy(const Copy &another) : _i(new int(*another._i))
    {
        cout << "Copy(const Copy & another), copy " << &another << " to " << this << endl;
    }
    // 若移动自实现，拷贝默认即无
    Copy(Copy &&another) : _i(nullptr)
    {
        cout << "MOVE Copy(Copy&& another), move " << &another << " to " << this << endl;
        _i = another._i;
        another._i = nullptr;
    }

    Copy &operator=(Copy &&another)
    {
        if (this != &another)
        {

            cout << "MOVE operator=(Copy&& another), move assign " << &another << " to " << this << endl;
            delete _i;
            _i = another._i;
            another._i = nullptr;
        }

        return *this;
    }
    Copy &operator=(const Copy &another)
    {
        cout << "Copy& operator=(const Copy& another), copy assign " << &another << " to " << this << endl;

        if (&another != this)
        {
            delete _i;
            _i = new int(*(another._i));
        }

        return *this;
    }

    ~Copy()
    {
        cout << "~Copy()" << this << endl;
        delete _i;
    }

    void dis() const
    {
        cout << *_i << endl;
    }

    int *_i;
};

//getObjectNROV函数返回类型仍然是Copy，而不是Copy&&。
//这意味着函数还是会创建一个Copy类的临时对象，只是临时对象是通过右值引用得到的，也就是说通过移动构造函数移动得到的。
//如果没定义move constructor，则调用copy constructor，
Copy getObjectNROV()
{
    Copy c = Copy();
    return std::move(c);    // 只要有std::move就会调一次移动构造,没有移动构造调用拷贝构造
}

Copy getObject()
{
    return Copy();
}

const Copy getConstObject()
{
    return Copy();
}

//函数的返回类型是右值引用，return右值引用，没有临时对象的消耗，但是仍不可取，因为右值引用的对象在使用前已经析构了。
// 将亡值
Copy &&getXvalueObject()
{
    return Copy();
}



/************************从 const T& 到 &&*****************************/
void acceptValue(Copy o)
{
    cout << "acceptValue: " << &o << endl;
}
void acceptRef(const Copy &o)
{
    cout << "acceptRef: " << &o << endl;
}
void accetpRRef(Copy &&o)
{
    cout << "accetpRRef: " << &o << endl;
}

void fromConstTRefToRefref()
{
    {
        acceptValue(getObject());
    }
    cout << "------------------------" << endl;
    {
        acceptRef(getObject());
    }
    cout << "------------------------" << endl;
    {
        accetpRRef(getObject());
    }
}

/************************从 const T& 到 &&*****************************/

void test_lvalue()
{
    cout << "&\"abc\":" << &"abc" << endl; // 字符串常量是一个左值， 可以取地址&
    int a = 5;
    int &a1 = a;
    cout << "&a1: " << &a1 << endl;
    cout << "&(a = 1)" << &(a = 1) << endl; // lvalue
    cout << "&(++a)" << &(++a) << endl;     // lvalue
    // cout << "&(a++)" << &(a++) << endl; // rvalue
    cout << "&(cout<<'')" << &(cout << ' ') << endl; // lvalue operator<<

    const int &a2 = 5;
    cout << "&a2: " << &a2 << endl; // lvalue

    vector<int> v = {1, 2, 3};
    auto &&v1 = v[0]; // v1 is lvalue
    cout << "&v1:" << &v1 << endl;
}

void test_rvalue()
{
    int a = 10;
    int b = 100;
    int &b1 = b;
    int &&a1 = std::move(a);
    // int& b1 = std::move(b);  // error

    cout << "a1:" << a1 << endl;    //10
    cout << "a:" << a << endl;      //10
    cout << "&a1:" << &a1 << endl;  //0x7ffc029ea5a0
    cout << "&a:" << &a << endl;    //0x7ffc029ea5a0
    a1 = 100;
    cout << "a1:" << a1 << endl;    //100
    cout << "a:" << a << endl;      //100
    cout << "&a1:" << &a1 << endl;  //0x7ffc029ea5a0
    cout << "&a:" << &a << endl;    //0x7ffc029ea5a0

    cout << "&b:" << &b << endl;    //0x7ffc029ea5a0
    cout << "&b1:" << &b1 << endl;  //0x7ffc029ea5a0
    // c++编译器默认是开启RVO的，-fno-elide-constructors关闭RVO
#if 1
    {
        // 1.关闭RVO, 如果只实现了copy constructor, 先把返回值拷贝给临时对象，再把临时对象拷贝给c
        // 2.关闭RVO, 如果实现了move constructor, 则先把返回值移动给临时对象，再把临时对象移动给c
        // Copy c = getObject();
        
        Copy c = getObjectNROV();

        c.dis();                
        cout << "&c:" << &c << endl;
    }
#endif
    cout << "****************************************" << endl;
#if 1
    {
        // 1.关闭RVO, 对于常量左值引用，如果只实现了copy constructor, 则直接把返回值拷贝给临时对象, c1是临时对象的引用。
        // 2.关闭RVO, 对于常量左值引用，如果实现了move constructor, 则直接把返回值移动给临时对象, c1是临时对象的引用。
        const Copy &c1 = getObject();   
        // const Copy &c1 = getConstObject();   

        // 3.1关闭RVO, 如果只实现了copy constructor, std::move先把局部变量拷贝给一个临时对象，再把这个临时对象拷贝给另一个临时对象， c1是最后一个临时对象的引用。
        // 3.2关闭RVO，对于右值引用，如果实现了move constructor, std::move先把局部变量移动给一个临时对象，再把这个临时对象移动给另一个临时对象， c1是最后一个临时对象的引用。
        // const Copy &c1 = getObjectNROV();   
        // const Copy &c1 = getXvalueObject(); // error egmentation fault
        
        cout << "&c1:" << &c1 << endl;
        c1.dis();                       
    }
#endif
    cout << "****************************************" << endl;
#if 1
    {
        // 关闭RVO，对于右值引用，如果实现了move constructor, 则直接把返回值移动给临时对象, c2是临时对象的右值引用。
        Copy &&c2 = getObject();  

        // 关闭RVO，对于右值引用，如果实现了move constructor, std::move先把局部变量移动给一个临时对象，再把这个临时对象移动给另一个临时对象， c1是最后一个临时对象的引用。
        // Copy &&c2 = getObjectNROV();
        // Copy &&c2 = getXvalueObject();  // Segmentation fault
        
        cout << "&c2:" << &c2 << endl;
        c2.dis();
    }
#endif
}

void test_xvalue()
{
    // getObject().dis();
    // cout << &(getXvalueObject()) << endl;   // xvalue不能&
    
    // const Copy &c = getXvalueObject(); // xvalue Segmentation fault
    // c.dis();

    // Copy()是一个纯右值，访问其成员函数dis()却需要一个泛左值，所以这里会发生一次临时变量实质化，
    // 将Copy()转换为将亡值，最后再访问其属性。
    // 在c++17标准之前临时变量是纯右值，只有转换为右值引用的类型才是将亡值。
    Copy().dis();
}

void test_move_constructor()
{
    // 如何将右值引用绑定到左值上
    int i = 1;
    // int &&k = i;    // compile error
    // 利用static_cast转换为将亡值, 将亡值属于右值，右值可以被右值引用绑定
    // 值得注意的是，由于转换的并不是右值，因此它依然有着和转换之前相同的声明周期和内存地址。
    int &&k = static_cast<int&&>(i);

    // static_cast<Copy&&>的最大作用是让左值使用移动语义。
    Copy c1;
    Copy c2 = static_cast<Copy&&>(c1);
}

int main()
{
    // test_lvalue();
    cout << "----------------------" << endl;
    // test_rvalue();
    cout << "----------------------" << endl;
    // test_xvalue();
    // test_move_constructor();

    fromConstTRefToRefref();

    return 0;
}
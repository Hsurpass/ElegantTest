#include <iostream>
#include <memory>
#include <vector>
#include <functional>

using namespace std;
using namespace placeholders;

class Copy
{
public:
    // static shared_ptr<Copy> create_shared_ptr() { return make_shared<Copy>(); } // error constructor is private
// private:
    Copy(int i = 10) : _i(new int(i))
    {
        cout << "Copy(int i)" << this << endl;
    }
public:

    // 若拷贝自实现，移动默认即无
    Copy(const Copy &another) : _i(new int(*another._i))
    {
        cout << " Copy(const Copy & another)" << endl;
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

            cout << "MOVE operator=(Copy&& another)" << endl;
            delete _i;
            _i = another._i;
            another._i = nullptr;
        }

        return *this;
    }
    Copy &operator=(const Copy &another)
    {
        cout << "Copy& operator=(const Copy& another)" << endl;

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

class Derive : public Copy
{
public:
    Derive(){ cout << "Derive" << endl; }
    ~Derive(){ cout << "~Derive" << endl; }
};

void test_shared_ptr_inherit_destructor()
{
    // {
    //     shared_ptr<Copy> spd = make_shared<Derive>();
    // }

    // {
    //     shared_ptr<Copy> spd = (shared_ptr<Copy>)(make_shared<Derive>());
    // }
    
    // 赋值之前强制转换成父类，就不会释放子类了，因为refcount.ptr记录的是父类的指针。
    {
        shared_ptr<Copy> spd((Copy*)(new Derive));
    }
}

void test_make_shared()
{
    // shared_ptr<Copy> spc = Copy::create_shared_ptr();

    {
        shared_ptr<Copy> sc = make_shared<Copy>(123);
    }
}

// 没测试出延迟释放的场景
void test_make_shared_delay_release_memory()
{
    shared_ptr<Copy> sc = make_shared<Copy>(123);
    weak_ptr<Copy> wc(sc);

    {
        weak_ptr<Copy> wpc(sc);
        // sc.reset();
        cout << "-------------------" << endl;

    }
    cout << "-------------------" << endl;
}

int main()
{
    // test_make_shared();
    // test_make_shared_delay_release_memory();
    test_shared_ptr_inherit_destructor();

    return 0;
}
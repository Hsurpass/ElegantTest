#include <iostream>
#include <memory>

using namespace std;

class Copy
{
public:
    Copy(int i) : _i(new int(i))
    {
        cout << "Copy(int i)" << endl;
    }
    Copy(const Copy &another) : _i(new int(*another._i))
    {
        cout << " Copy(const Copy & another)" << endl;
    }
    ~Copy()
    {
        cout << "~Copy()" << endl;
    }
    int *_i;
};

void func(auto_ptr<Copy> tmp)
{
}

void auto_ptr_redestructor01()
{
    auto_ptr<Copy> ap(new Copy(111)); // Copy(int i)
    cout << *ap->_i << endl;          // 111

    func(ap); // ~Copy()

    printf("================\n");
    cout << *ap->_i << endl; // Segmentation fault (core dumped)
}

void auto_ptr_redestructor02()
{
    int *p = new int(10); // Copy(int i)
    {
        auto_ptr<int> ap(p);
        cout << *ap << endl; // 10 // ~Copy()
    }

    cout << p << endl;
    auto_ptr<int> ap1(p);
    cout << *ap1 << endl; // Segmentation fault (core dumped)
}

void test_auto_ptr_constructor()
{
    auto_ptr<int> ap(new int(100));
    cout << *ap << endl;    // 100

    auto_ptr<int> app(ap);
    cout << *app << endl;   // 100
    // cout << *ap << endl;    // core dump  所有权被转移
}

int main()
{
    // auto_ptr_redestructor01();
    // auto_ptr_redestructor02();
    test_auto_ptr_constructor();

    return 0;
}

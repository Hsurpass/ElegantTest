#include <iostream>
#include <assert.h>
#include <typeinfo>

using namespace std;

// 使用dynamic_cast必须有虚函数
class A
{
public:
    virtual ~A() {}
};
class B : public A
{
};
class C : public A
{
};
class D
{
};

//downcast no-relation
void test_dynamic_cast()
{
    B b;
    A& ra = b;
    A *pa = &b;
    // static_assert(typeid(*pa) == typeid(b), "typeid(*pa) == typeid(b)");
    assert(typeid(*pa) == typeid(b));
    assert(typeid(*pa).name() == typeid(b).name());

    B *pb = dynamic_cast<B*>(pa);
    if (pb != NULL)
        cout << "pb != NULL" << endl;   // pb != NULL
    else
        cout << "pb == NULL" << endl;
    
    C* pc = dynamic_cast<C*>(pa);
    if (pc != NULL)
        cout << "pc! = NULL" << endl;   
    else
        cout << "pc == NULL" << endl; // pc == NULL
    
    D *pd = dynamic_cast<D *>(pa);
    if (pd != NULL)
        cout << "pc! = NULL" << endl;
    else
        cout << "pc == NULL" << endl;   // pc == NULL

    cout << "----------------------" << endl;
    B& rb = dynamic_cast<B&>(ra);
    // D& rd = dynamic_cast<D&>(ra);   // throw std::bad_cast

}

int main()
{
    test_dynamic_cast();

    return 0;
}
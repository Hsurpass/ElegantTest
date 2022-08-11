#include <iostream>
#include <memory>
#include <functional>
//#include <assert.h>
#include <vector>
#include <cassert>
using namespace std;

namespace Test {

class A
{
public:
    A() {cout << "A()" << endl;}
    ~A() {cout << "~A()" << endl;}
};
class Object
{
public:
    Object()
    {
        cout << "Object()" << endl;
    }
     ~Object()
    {
        cout << "~Object()" << endl;
    }
    using pointer = shared_ptr<Object>;
//    shared_ptr<Object> pointer;
    virtual std::string debugName() const = 0;
};
class RealObject :public Object
{
public:
    RealObject()
    {
        cout << "RealObject()" << endl;
    }
    ~RealObject()
    {
        cout << "~RealObject()" << endl;
    }
//    string debugPrint() const {return "RealObject";}
    string debugName()const
    {
        return "RealObject debugName";
    }
private:
    A a;
};
void testObject(const Object& obj)
{
    cout << obj.debugName() << endl;
}
void testCase()
{
//    cout << sizeof(Object) << endl;
//    RealObject robj;
//    testObject(robj);
//    auto pObj = std::make_shared<RealObject>();
//    testObject(*pObj);
//    unique_ptr<Object> uobj = make_unique<RealObject>();
//    unique_ptr<Object> uobj(new RealObject);
//    unique_ptr<Object> uobj = unique_ptr<RealObject>();
//    testObject(*uobj);

//    shared_ptr<int> si = std::make_shared<int>();
//    shared_ptr<Object> siObj = const_pointer_cast<Object>(si);
    shared_ptr<Object> spObj = std::make_shared<RealObject>();
//    shared_ptr<RealObject> rObj = static_pointer_cast<RealObject>(spObj);
    shared_ptr<RealObject> rObj = dynamic_pointer_cast<RealObject>(spObj);
    shared_ptr<Object> sspObj = dynamic_pointer_cast<Object>(rObj);
    cout << spObj.use_count() << endl;
    cout << rObj.use_count() << endl;
    cout << "--------------" << endl;
    cout << spObj << " " << rObj << " " <<sspObj << " " << endl;
    cout << spObj.get() << " " << rObj.get() << " " <<sspObj.get() << " " << endl;
    if(spObj == rObj)
    {
        cout << "spObj == rObj" << endl;
    }
    else
    {
        cout << "spObj != rObj" << endl;
    }
    if(spObj == sspObj)
    {
        cout << "spObj == sspObj" << endl;
    }
    else
    {
        cout << "spObj != sspObj" << endl;
    }
    if(rObj == sspObj)
    {
        cout << "rObj == sspObj" << endl;
    }
    else
    {
        cout << "rObj != sspObj" << endl;
    }
//    assert(spObj == rObj);
//    static_assert((spObj == rObj));
//    spObj.reset();
    cout << spObj.use_count() << endl;
    cout << rObj.use_count() << endl;
    testObject(*rObj);
//    spObj.reset();
//    Object *sp = spObj.get();
//    cout << spObj.use_count() << endl;
//    shared_ptr<Object> spObj(new RealObject);
//    auto spObj = std::make_shared<RealObject>();
//    testObject(*spObj);

}
void bitoffset()
{
    char a = 64;
//    cout << a << endl;
    printf("%d\n",a);
    a = a<<1;
    printf("%d\n",a);
    a = a >> 1;
    printf("%d\n",a);
}

}


int main()
{
    using namespace Test;
//    cout << sizeof(Test::Object) << endl;
    testCase();
    bitoffset();
    return 0;
}


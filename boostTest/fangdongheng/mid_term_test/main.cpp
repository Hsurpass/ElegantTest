#include <boost/smart_ptr.hpp>
#include <boost/smart_ptr/make_unique.hpp>
#include <iostream>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
using namespace std;
using namespace boost;


namespace Test {
    class Object
    {
    public:
        Object()
        {
            cout << "Object()" << endl;
        }
        virtual ~Object()
        {
            cout << "~Object()" << endl;
        }
        using pointer = boost::shared_ptr<Object>;
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
            //std::unique_ptr<Object> uobj = boost::make_unique<RealObject>();
        //std::unique_ptr<Object> uobj(new RealObject);
        //    unique_ptr<Object> uobj = unique_ptr<RealObject>();
        //testObject(*uobj);

        boost::shared_ptr<Object> spObj(new RealObject);
        //boost::shared_ptr<Object> spObj = boost::make_shared<RealObject>();
        boost::shared_ptr<RealObject> rObj = static_pointer_cast<RealObject>(spObj);
        //boost::shared_ptr<RealObject> rObj = dynamic_pointer_cast<RealObject>(spObj);
        //boost::shared_ptr<Object> sspObj = dynamic_pointer_cast<Object>(rObj);
        cout << spObj.use_count() << endl;
        //cout << rObj.use_count() << endl;
        cout << "--------------" << endl;
        testObject(*spObj);
        //std::shared_ptr
    }

}


int main()
{
    using namespace Test;
    //    cout << sizeof(Test::Object) << endl;
    testCase();

    this_thread::sleep_for(boost::chrono::minutes(2));
    return 0;
}

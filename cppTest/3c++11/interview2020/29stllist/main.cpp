#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <functional>
#include <iterator>

using namespace std;
using namespace std::placeholders;
class A
{
    friend bool operator==(const A&one,const A& another);
    friend bool operator <(const A&one,const A&another);
public:
    A()
    {
        cout<<"A()"<<this<<endl;
    }
    A(int i):_data(i)
    {
        cout<<"A(int i):_data(i),i:" << i <<" "<<this<<endl;
    }
    A(const A & other)
    {
        cout<<"A(const A & other),other._data:"<<other._data << " " << this<<" from "<<&other<<endl;
        this->_data = other._data;
    }
    A& operator=(const A & other)
    {
        cout<<"A& operator=(const A & other),other._data:" << other._data << " " <<this<<" from "<<&other<<endl;
        if(this != &other)
        {
            this->_data = other._data;
        }
        return *this;
    }
    bool operator==(const A& another)
    {
        cout << "bool operator ==(const A&another)" << endl;
        return (this->_data == another._data);
    }
    //    bool operator <(const A&another) const
    //    {
    //        cout << "bool operator <(const A&another),this->_data:" <<this->_data<< ",another._data:"<< another._data<< endl;
    //        return (this->_data < another._data);
    //    }
    bool operator >(const A&another) const
    {
        cout << "bool operator >(const A&another),this->_data:" << this->_data<< ",another._data:"<< another._data<< endl;
        return (this->_data > another._data);
    }
    ~A()
    {
        cout<<"~A()"<<this<<endl;
    }
    int dis()const
    {
        return _data;
    }
    //    private:
public:
    //    int _data;
    //    string _data;
    int _data;
};
bool operator==(const A&one,const A& another)
{
    cout << "bool operator==(const A&one,const A& another),one._data:"<<one._data<< ",another._data:"<< another._data << endl;
    return (one._data == another._data);
}
bool operator <(const A&one,const A&another)
{
    cout << "bool operator <(const A&one,const A&another),one._data:" <<one._data<< ",another._data:"<< another._data<< endl;
    return (one._data < another._data);
}
struct comp
{
    bool operator()(const A &x)const  {
        cout << "bool operator()(A &x)" << endl;
        A tmp(2);
        return x > tmp;
        //        return x > A(2);
    }
    typedef A argument_type;
};

ostream& operator<<(ostream& ostr,const list<int>& list)
{
    for (auto &i : list) {
        ostr << " " << i;
    }
    return ostr;
}

void printLists (const list<int>& l1,
                 const list<int>& l2)
{
    cout << "list1: ";
    copy (l1.cbegin(), l1.cend(),
          ostream_iterator<int>(cout," "));
    cout << endl << "list2: ";
    copy (l2.cbegin(), l2.cend(),
          ostream_iterator<int>(cout," "));
    cout << endl << endl;
}
int main()
{
    list<int> list1, list2;
    for (int i=0; i<6; ++i)
    {
        list1.push_back(i);
        list2.push_front(i);
    }
    printLists(list1, list2);
    list2.splice(find(list2.begin(),list2.end(),3),list1);
    printLists(list1, list2);
    list2.splice(list2.end(),list2, list2.begin());
    list2.sort();
    list1 = list2;
    list2.unique();
    printLists(list1, list2);
    list1.merge(list2);
    printLists(list1, list2);
    return 0;
}


int mai09()
{
    list<int> list1 = { 1, 2, 3, 4, 5 };
    list<int> list2 = { 10, 20, 30, 40, 50 };
    auto it = list1.begin();
    advance(it, 2);
    list1.splice(it, list2);
    cout << "list1: " << list1 << "\n";
    cout << "list2: " << list2 << "\n";
    list2.splice(list2.begin(), list1, it, list1.end());
    cout << "list1: " << list1 << "\n";
    cout << "list2: " << list2 << "\n";
    return 0;
}

int main08()
{
    list<A> ll;
    ll.emplace_back(1);ll.emplace_back(3);ll.emplace_back(5);
    ll.emplace_back(7);ll.emplace_back(9);
    list<A> ll2;
    ll2.emplace_back(2);ll2.emplace_back(4);ll2.emplace_back(6);
    ll2.emplace_back(8);ll2.emplace_back(10);

    //    ll.merge(ll2);
    //    ll.merge(ll2,bind(greater<A>(),_1,_2));
    //    ll.merge(ll2,[](A& a,A &b){
    //        return a > b;
    //    });

    cout << "-------------------" << endl;
    cout << ll.size() << endl;
    cout << ll2.size() << endl;
    cout << "-------------------" << endl;
    for(auto &x:ll)
    {
        cout << x.dis() << " ";
    }
    cout << endl;
    return 0;
}

int main07()
{
    list<A> ll;
    ll.emplace_back(1);ll.emplace_back(2);ll.emplace_back(3);
    ll.emplace_back(1);ll.emplace_back(2);ll.emplace_back(4);
    ll.emplace_back(5);ll.emplace_back(5);ll.emplace_back(5);ll.emplace_back(3);
    cout << "-------------------" << endl;
    cout << ll.size() << endl;
    cout << "-------------------" << endl;
    list<A> ll2;
    //    ll.insert();
    //    ll2.splice(ll2.begin(),ll,ll.begin(),ll.end());
    //    ll2.insert(ll2.begin(),ll.begin(),ll.end());

    cout << "-------------------" << endl;
    cout << ll.size() << endl;
    cout << ll2.size() << endl;
    cout << "-------------------" << endl;
    for(auto &x:ll2)
    {
        cout << x.dis() << endl;
    }
    return 0;
}

int main06()
{
    //    A a(111);
    //    auto x = bind(&A::_data,a);
    //    cout << x() << endl;
    list<A> ll;
    ll.emplace_back(1);ll.emplace_back(2);ll.emplace_back(3);
    ll.emplace_back(1);ll.emplace_back(2);ll.emplace_back(4);
    ll.emplace_back(5);ll.emplace_back(5);ll.emplace_back(5);ll.emplace_back(3);
    cout << "-------------------" << endl;
    cout << ll.size() << endl;
    cout << "-------------------" << endl;

    //    ll.unique();
    //    ll.unique([](A&a,A&b){return a == b;});
    //    auto itr = std::unique(ll.begin(),ll.end());
    //    auto itr = std::unique(ll.begin(),ll.end(),[](A&a,A&b){return a == b;});
    //    cout << itr->dis() << endl;
    //    ll.erase(itr,ll.end());

    cout << "-------------------" << endl;
    cout << ll.size() << endl;
    cout << "-------------------" << endl;
    for(auto &x:ll)
    {
        cout << x.dis() << endl;
    }
    return 0;
}
int main05()
{
    //    int arr[] = {1,3,5,7,9,2,4,6,8,10};
    //    std::sort(arr,arr+sizeof(arr)/sizeof(*arr),less<int>());
    //    std::sort(arr,arr+sizeof(arr)/sizeof(*arr),greater<int>());
    //    for(auto &x:arr)
    //    {
    //        cout << x << " ";
    //    }
    list<A> ll;
    ll.emplace_back(1);
    ll.emplace_back(2);
    ll.emplace_back(3);
    ll.emplace_back(1);
    ll.emplace_back(2);
    ll.emplace_back(4);
    ll.emplace_back(5);
    ll.emplace_back(3);
    cout << "-------------------" << endl;
    cout << ll.size() << endl;
    cout << "-------------------" << endl;

    //    std::sort(ll.begin(),ll.end());
    //    ll.sort();
    //    ll.sort(less<A>());
    //    ll.sort(not2(less<A>()));
    //    ll.sort(greater<A>());
    int count = 0;
    //    count = std::count(ll.begin(),ll.end(),1);
    //    count = std::count(ll.begin(),ll.end(),A(1));
    A tmp(2);
    //    count = std::count_if(ll.begin(),ll.end(),/*not1(*/[&tmp](A &x){
    //  /          return x > A(2);
    //            return x > tmp;
    //    }/*)*/);
    //    count = count_if(ll.begin(),ll.end(),not1(comp()));
    count = count_if(ll.begin(),ll.end(),/*not1*/(bind(greater<A>(),_1,tmp)));
    cout << "count:" << count << endl;

    cout << "-------------------" << endl;
    for(auto &x:ll)
    {
        cout << x.dis() << endl;
    }
    cout << "-------------------" << endl;
    cout << endl;
    return 0;
}

int main04()
{
    vector<int> v ={1,2,3,3,3,3,4,5,6,3,7};
    cout << v.size() << endl;
    cout << "---------------" << endl;

    auto itr = std::remove(v.begin(),v.end(),3);
    cout << *itr << endl;
    //    v.resize(6);
    //    v.shrink_to_fit();
    v.erase(itr,v.end());
    v.shrink_to_fit();
    cout<< "----------------" << endl;
    cout << "size: " << v.size() << endl;
    cout << "capacity:" << v.capacity() << endl;
    cout<< "----------------" << endl;
    for(auto &x:v)
    {
        cout << x << endl;
    }
    return 0;
}
bool func(const A &a)
{
    A b(2);
    return a > b;
}
int main03()
{
    list<A> ll;
    ll.emplace_back(1);
    ll.emplace_back(2);
    ll.emplace_back(3);
    ll.emplace_back(1);
    ll.emplace_back(2);
    ll.emplace_back(4);
    ll.emplace_back(5);
    ll.emplace_back(3);
    cout << "-------------------" << endl;
    cout << ll.size() << endl;
    cout << "-------------------" << endl;

    list<A>::iterator itr = ll.begin();
    //    itr = ll.erase(ll.begin(),++ll.begin());
    //    std::advance(itr,3);
    //    itr = ll.erase(ll.begin(),itr);
    //    itr = ll.erase(++ll.begin());

    //    itr = std::remove(ll.begin(),ll.end(),3);
    //    itr = std::remove(ll.begin(),ll.end(),A(3));
    //    itr = std::remove_if(ll.begin(),ll.end(),func);
    //    itr = std::remove_if(ll.begin(),ll.end(),[](A &x){return x > 2;});
    itr = std::remove_if(ll.begin(),ll.end(),[](A &x){return x > A(2);});
    cout << itr->dis() << endl;
    //    ll.erase(itr,ll.end());




    cout << "-------------------" << endl;
    cout << ll.size() << endl;
    cout << "-------------------" << endl;
    for(auto &v:ll)
    {
        cout << v.dis() << endl;
    }
    return 0;
}
int main02()
{
    //    A a(2);
    //    vector<A> ll;
    //    list<A> ll{1,2,3,4,5};
    list<A> ll;
    ll.emplace_back(1);
    ll.emplace_back(2);
    ll.emplace_back(3);
    ll.emplace_back(4);
    ll.emplace_back(5);
    ll.emplace_back(3);
    ll.emplace_back(3);
    ll.emplace_back(3);
    ll.emplace_back(3);
    cout << "-------------------" << endl;
    cout << ll.size() << endl;

    //    ll.remove(3);
    //    A a(1);
    //    ll.remove_if([&a](A n){return n>a; });


    //    std::remove(ll.begin(),ll.end(),3);

    //    list<A>::iterator itr = ll.erase(ll.begin());
    //    list<A>::iterator itr = ll.erase(ll.begin(),ll.end());
    //    cout << itr->dis() << endl;
    //    ll.reverse();

    //    ll.emplace_back(2);
    //    ll.resize(10,A(4));
    //    ll.resize(5);
    cout << "------------------" << endl;
    //    ll.clear();

    cout << ll.size() << endl;
    cout << "-------------------" << endl;
    for(auto &v:ll)
    {
        cout << v.dis() << endl;
    }
    return 0;
}

int main01()
{
    list<A> la;
    //    list<A> la(5,2);
    //    list<A> la2(10,3);

    //    list<A> la(10,A(4));
    //    list<A> lla(la);
    //    list<A> lla(la.begin(),la.end());
    //    list<A> lla({1,2,3});
    //    list<A> lla2 = {1,2,3};
    //    A a(2);
    //    A b(3);
    //    cout << (a == b) << endl;
    //    if(lla == lla2)
    //    {
    //        cout << "lla == lla2" << endl;
    //    }
    //    else {
    //        cout << "lla != lla2" << endl;
    //    }

    //    la = la2;
    //    la = {1,2,3};

    //    la.assign(5,3);
    //    list<A> lswp;
    //    la.swap(lswp);
    //    std::swap(la,lswp);

    //    cout << la.front().dis() << endl;
    //    cout << la.back().dis() << endl;

    //    la.push_back(1);
    la.push_back(A(2));
    la.push_front(A(1));
    la.pop_back();
    la.pop_front();
    cout << "------------" << endl;
    //    la.insert(la.begin(),A(3));
    //    la.insert(la.end(),3,A(1));
    //    list<A> lisert;
    //    lisert.insert(lisert.begin(),la.begin(),la.end());
    //    cout << lisert.size() << endl;

    la.insert(la.begin(),{1,2,3});
    //    la.push_front(3);
    la.emplace(la.begin(),3);
    //    la.emplace_back(A(4));
    la.emplace_back(4);
    la.emplace_front(2);
    //    cout << lswp.size() << endl;
    cout << la.size() << endl;
    cout << "-----------------" << endl;
    for(auto &v:la)
    {
        cout << v.dis() << endl;
    }
    //    cout << la.max_size() << endl;

    return 0;
}


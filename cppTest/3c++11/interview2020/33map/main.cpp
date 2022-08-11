#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include <functional>
using namespace std;
template<typename T>
class comp
{
public:
    comp(const bool& x = true):reverse(x) {}
    bool operator()(const T& one,const T& another)
    {
        if(reverse)
        {
            return one < another;
        }
        else {
            return one > another;
        }
    }
private:
    bool reverse;
};
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

int main()
{
    map<int,string> mis;

    mis[1] = "aaa";
    mis[3] = "ccc";
    mis[4] = "ddd";
    mis[2] = "bbb";
    mis.insert(map<int,string>::value_type(6,"fff"));
    mis.insert(pair<int,string>(5,"eee"));
    mis.insert(make_pair<int,string>(7,"ggg"));
    mis.emplace(8,"hhh");
    map<int,string>::iterator itr;
    itr = mis.find(7);
    if(itr != mis.end())
    {
        itr = mis.erase(itr);

    }
    if (itr != mis.end())
    {
        cout << itr->first << ":" << itr->second << endl;
    }
    else
    {
        cout << "next element is ::end()" << endl;
    }
}

int main04()
{
    vector<A> v = {1,3,5,7,9,2,4,6,8,10};
    map<int,vector<A>> miva;
    miva.insert(make_pair(1,v));
//    miva.emplace(1,v);

    for(auto &x:miva)
    {
        for(auto &xx:x.second)
        {
            cout << xx.dis() << " ";
        }
        cout << endl;
    }
    cout << miva.size() << endl;
    return 0;
}

int main03()
{
    map<A,string> mas;
    mas[A(2)] = "bbb";
    mas.insert(make_pair<A,string>(A(3),"ccc"));
    mas.insert(pair<A,string>(A(1),"aaa"));
    mas.insert(map<A,string>::value_type(A(4),"ddd"));
    mas.emplace(6,"fff");
    map<A,string>::iterator itr;
    itr = mas.find(A(4));
    cout << itr->first.dis() << ":" << itr->second << endl;
    mas.insert(itr,make_pair(A(5),"eee"));
    mas.insert(mas.end(),make_pair(A(7),"ggg"));


    cout << "------------------------" << endl;
    for(auto &x:mas)
    {
        cout << x.first.dis() << ":" << x.second << endl;
    }
    cout << mas.size() << endl;
    return 0;
}
int main02()
{
    vector<int> v = {1,3,5,7,9,2,4,6,8,10};
    map<int,vector<int>> miv;
    miv.insert(make_pair(1,v));
    map<int,vector<int>> miv2;
    miv2.swap(miv);

    cout << "v.size:" << v.size() << endl;
    cout << "miv.size:" << miv.size()<<endl;
    cout << "miv2.size:" << miv2.size() << endl;
    cout << "----------------------" << endl;
    for(auto &i:v)
    {
        cout << i << " ";
    }
    cout << endl;
    cout << "----------------------" << endl;
    for(auto &xx:miv)
    {
        vector<int> x = xx.second;
        for(auto &i:x)
        {
            cout << i << " ";
        }
    }
    cout << endl;
    cout << "----------------------" << endl;
    for(auto &xx:miv2)
    {
        vector<int> x = xx.second;
        for(auto &i:x)
        {
            cout << i << " ";
        }
    }
    cout << endl;
    cout << "----------------------" << endl;
    cout << miv.size()<<endl;
    return 0;
}
int main01()
{
    map<int,map<int,string>> mmis;
    map<int,string> mis;
//    map<int,string,greater<int>> mis;
//    map<int,string,comp<int>> mis;
//    map<int,string,greater<int>> mis(greater<int>());
    mis[1] = "aaa";
    mis[3] = "ccc";
    mis[4] = "ddd";
    mis[2] = "bbb";
    mis.insert(map<int,string>::value_type(6,"fff"));
    mis.insert(pair<int,string>(5,"eee"));
    mis.insert(make_pair<int,string>(7,"ggg"));
    mis.emplace(8,"hhh");
    map<int,string>::iterator itrr;
    itrr = mis.find(8);
    if(itrr != mis.end())
    {
        mis.insert(itrr,make_pair(9,"iii"));
    }
    mis.insert(mis.end(),make_pair(0,"jjj"));

    mmis.insert(make_pair(1,mis));

    map<int,map<int,string>> mmis2;
    mmis2.swap(mmis);
//    map<int,string> mis2;
//    mis2.swap(mis);
//    map<int,string,greater<int>> mis2(mis);

    cout << "mis.size:" << mis.size() << endl;
    cout << "mmis.size:"<< mmis.size() << endl;
    cout << "mmis2.size:"<< mmis2.size() << endl;
    //    cout << mis.max_size() << endl;
    cout << "----------------------" << endl;
    map<int,string>::iterator itr;
    for(itr = mis.begin();itr != mis.end();++itr)
    {
        cout << itr->first << ":"<< itr->second << endl;
    }
    cout << "----------------" << endl;
//    for(auto mitr = mmis2.begin();mitr != mmis2.end();++mitr)
//    {
//        map<int,string> x = mitr->second;
//        for(auto itr = x.begin();itr != x.end();++itr)
//        {
//            cout << itr->first << ":"<< itr->second << endl;
//        }
//    }
    for(auto &xx:mmis2)
    {
        map<int,string> x = xx.second;
        for(auto &i:x)
        {
            cout << i.first << ":"<< i.second << endl;
        }
//        for(auto itr = x.begin();itr != x.end();++itr)
//        {
//            cout << itr->first << ":"<< itr->second << endl;
//        }
    }
    mis.clear();
    cout << mis.size()<<endl;;
    return 0;
}

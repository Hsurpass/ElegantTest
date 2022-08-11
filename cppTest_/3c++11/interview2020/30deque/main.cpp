#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
//#include <stack>
using namespace std;
//using namespace std::placeholders;
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
//    deque<int> d;
//    deque<int> d = {0,1,2,3,4,5,6,7,8,9};
//    cout << "size:" << d.size() << endl;
//    cout << "max size:" << d.max_size() << endl;
    deque<A> d;
//    d.resize(10,3);
//    d.resize(10);
    d.push_back(3);
    d.push_back(2);
    d.push_back(1);
    d.push_front(10);
    d.push_front(20);
    d.push_front(30);
//    cout << (d.front()).dis() << endl;
//    d.pop_front();
//    cout << d.back().dis() << endl;;
//    d.pop_back();

//    d.erase(d.begin(),d.end());
    deque<A>::iterator itr;
//    itr = std::find(d.begin(),d.end(),1);
//    cout << itr->dis() << endl;
    cout << d.size() << endl;
//    cout << d[2].dis() << endl;
    d.insert(d.begin()+1,A(10));
    cout << "----------------" << endl;
//    d.erase(itr);
    itr = std::remove(d.begin(),d.end(),10);
    cout << itr->dis() << endl;
    cout << "----------------" << endl;
    for(auto &x:d)
    {
        cout <<x.dis() << endl;
    }
    cout << "-----------------------" << endl;
//    d.resize(5);
    d.erase(itr,d.end());
    for(auto &x:d)
    {
        cout <<x.dis() << " ";
    }
    cout << endl;
    d.clear();
    cout << d.size() << endl;

    return 0;
}

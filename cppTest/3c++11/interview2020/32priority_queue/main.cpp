#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <list>
#include <string.h>
//#include <stdio.h>
//#include <stdlib.h>

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

/***********************/
struct Node
{
    Node(int n,const char *s):priority(n) {
        strcpy(str,s);
    }

    char str[20];
    int priority;
};
struct Nodecmp
{
    bool operator()(const Node& one,const Node& another){
        if(one.priority != another.priority)
        {
            return one.priority > another.priority;
        }
        else {
            return (strcmp(one.str,another.str) < 0);
        }
    }
};

int main()
{
    priority_queue<Node,vector<Node>,Nodecmp> pn;
    pn.emplace(2,"2aaa");
    pn.emplace(2,"2bbb");
    pn.emplace(1,"1aaa");
    pn.emplace(3,"3ccc");


    cout << pn.size() << endl;
    cout << "-------------------------" << endl;
    while(!pn.empty())
    {
        cout << pn.top().priority <<":" << pn.top().str << endl;
        pn.pop();
    }
    return 0;
}
/***********************/

int main02()
{
//    vector<A> v = {1,2,3};
    vector<A> v;
    v.reserve(10);
    v.emplace_back(3);v.emplace_back(1);v.emplace_back(2);v.emplace_back(4);
    priority_queue<A,vector<A>,comp<A>> pq(comp<A>(false),v);
//    pq.push(3);
//    A b(3);
//    pq.emplace(3);


    cout << "-------------" << endl;
    cout << "v size:" << v.size() << endl;
    cout << "pq size:" << pq.size() << endl;
    cout << "----------------" << endl;
    while (!pq.empty()) {
        cout << pq.top().dis() << " ";
        pq.pop();
    }

    return 0;
}

int main01()
{
//    priority_queue<int> pq(greater<int>());
//    priority_queue<int,vector<int>,greater<int>> pq;
//    cout << pq.size() << endl;
//    pq.push(2);
//    pq.push(1);
//    pq.push(0);
//    pq.push(3);
    vector<int> v = {2,4,3,1};
//    list<int> v = {2,4,3,1,5};
//    deque<int> v = {2,4,3,1,7,6};
//    priority_queue<int,vector<int>,greater<int>> pq(v.begin(),v.end(),greater<int>());
//    priority_queue<int,vector<int>,greater<int>> pq(v.begin(),v.end());
    priority_queue<int,vector<int>,comp<int>> pq(comp<int>(false),v);
//    priority_queue<int,vector<int>,comp<int>> pq(v.begin(),v.end(),comp<int>(false));
//    priority_queue<int> pq(less<int>(),v);
//    priority_queue<int,vector<int>,greater<int>> pq(greater<int>(),v);
    cout << "----------------" << endl;
    cout << pq.size() << endl;
//    cout << pq.top() << endl;
    cout << "----------------------" << endl;

    while (!pq.empty()) {
        cout << pq.top() << " ";
        pq.pop();
    }
    cout << endl;

    return 0;
}

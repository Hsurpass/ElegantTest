#include <iostream>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;
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
    queue<A> qa;
    for(int i = 0;i < 10;++i)
    {
//        qa.push(i);
        qa.emplace(i);
    }
    cout << qa.size() << endl;
    A x;
//    for(int i = 0;i = qa.size();++i)
//    {
//        x = qa.front();
//        cout << x.dis() << " ";
//        qa.pop();
//    }
    while (!qa.empty()) {
        x = qa.front();
        cout << x.dis() << endl;
        qa.pop();
    }
    return 0;
}
int main_stack()
{
    stack<A> sa;
    for(int i = 0;i < 10;++i)
    {
        //        sa.push(i);
        sa.emplace(i);
    }
    cout << sa.size() << endl;
    A x;
    for(int i = 0;i = sa.size();++i)
    {
        x = sa.top();
        cout << x.dis() << " ";
        sa.pop();
    }
    return 0;
}

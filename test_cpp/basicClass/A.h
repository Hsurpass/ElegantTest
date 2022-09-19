#include <iostream>
#include <string>

using namespace std;

class A
{
public:
    A()
    {
        cout << "A()" << this << endl;
    }
    A(int i) : _data(i)
    {
        cout << "A(int i):_data(i),i:" << i << " " << this << endl;
    }
    A(const A& other)
    {
        cout << "A(const A& other),other._data:" << other._data << " " << this << " from " << &other << endl;
        this->_data = other._data;
    }
#if 1
    A(A&& another):_data(another._data)
    {
        cout << "A(A&& another), another._data:" << another._data << " " << this << " from " << &another << endl;
    }
    A& operator=(A&& another)
    {
        cout << "A& operator=(A&& another), another._data:" << another._data << " " << this << " from " << &another << endl;
        if(this != &another)
        {
            _data = another._data;
        }

        return *this;
    }
#endif
    A& operator=(const A& other)
    {
        cout << "A& operator=(const A& other),other._data:" << other._data << " " << this << " from " << &other << endl;
        if (this != &other)
        {
            this->_data = other._data;
        }
        return *this;
    }
    ~A()
    {
        cout << "~A()" << this << endl;
    }

    bool operator==(const A& other)
    {
        cout << "bool operator==(const A& other), other._data:" << &other << "|" << other._data << " " << "this.data:" << this << "|" << this->_data << endl;
        if(this->_data == other._data)
        {
            return true;
        }

        return false;
    }

    int print() const
    {
        return _data;
    }
    
private:
    int _data;
};
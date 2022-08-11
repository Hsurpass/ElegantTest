#include <iostream>
#include <string>

using namespace std;

class B
{
public:
    B()
    {
        cout << "B()" << this << endl;
    }
    B(string s) : _data(s)
    {
        cout << "B(string s):_data(s),s:" << s << " " << this << endl;
    }
    B(const B& other)
    {
        cout << "B(const B& other),other._data:" << other._data << " " << this << " from " << &other << endl;
        this->_data = other._data;
    }
    B &operator=(const B& other)
    {
        cout << "B& operator=(const B& other),other._data:" << other._data << " " << this << " from " << &other << endl;
        if (this != &other)
        {
            this->_data = other._data;
        }
        return *this;
    }
    ~B()
    {
        cout << "~B()" << this << endl;
    }

    void print() const
    {
        cout << _data << endl;;
    }
    
//private:
    string _data;
};
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
    A(int i) : a(i)
    {
        cout << "A(int i):a(i),i:" << i << " " << this << endl;
    }
    A(const A& other)
    {
        cout << "A(const A& other),other.a:" << other.a << " " << this << " from " << &other << endl;
        this->a = other.a;
    }
#if 1
    A(A&& another):a(another.a)
    {
        cout << "A(A&& another), another.a:" << another.a << " ,move another:" << &another << " to this:" << this << endl;
    }
    A& operator=(A&& another)
    {
        cout << "A& operator=(A&& another), another.a:" << another.a << " ,move another:" << &another << " to this:" << this << endl;
        if(this != &another)
        {
            a = another.a;
        }

        return *this;
    }
#endif
    A& operator=(const A& other)
    {
        cout << "A& operator=(const A& other),other.a:" << other.a << " " << this << " from " << &other << endl;
        if (this != &other)
        {
            this->a = other.a;
        }
        return *this;
    }
    ~A()
    {
        cout << "~A()" << this << endl;
    }

    bool operator==(const A& other) const
    {
        cout << "bool operator==(const A& other), other.a:" << &other << "|" << other.a << " " << "this.a:" << this << "|" << this->a << endl;
        if(this->a == other.a)
        {
            return true;
        }

        return false;
    }

    bool operator<(const A& other) const
    {
        cout << "bool operator<(const A& other), other.a:" << &other << "|" << other.a << " " << "this.a:" << this << "|" << this->a << endl;
        return a < other.a;
    }

    bool operator>(const A& other) const
    {
        cout << "bool operator>(const A& other), other.a:" << &other << "|" << other.a << " " << "this.a:" << this << "|" << this->a << endl;
        return other < a;
    }

    int geta() const
    {
        return a;
    }

    int print() const
    {
        return a;
    }
    
private:
    int a;
};

struct hash_A
{
    int operator()(const A &a) const 
    {
        cout << "hash_A operator()(const A &a) const" << endl;
        return a.geta() % 10; 
    }
};

template <typename T, bool reverse>
class Comp
{
public:
    // Comp(bool reverse=false) : m_reverse(reverse) {}
    // ~Comp() {}

    bool operator()(const T &one, const T &other) const
    {
        cout << "bool operator()(const T& one, const T& other), reverse: " << reverse << endl;
        if (reverse)
        {
            return one > other;
        }
        else
        {
            return one < other;
        }
    }

// private:
    // bool m_reverse;
};

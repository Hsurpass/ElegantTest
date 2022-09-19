/*** from fangdongheng P6 8-TCP03***/

#include <iostream>
#include <string>
#include <mcheck.h>
#include <stdlib.h>

using namespace std;

class ObjectA
{
public:
    explicit ObjectA(int a):m_value(new int(a)) {  cout << "ObjectA(int a):m_value(new int(a))" << endl;  }
    ~ObjectA() { delete m_value; cout << "~ObjectA()" << endl; }
private:
    int* m_value;
};

class Evil
{
public:
    Evil() 
    {
        int* pa = new int(10);
        cout << "Evil()" << endl;
        throw 10;
    }
    ~Evil() { cout << "~Evil()" << endl;}
};

class Normal : public ObjectA
{
public:
    explicit Normal(int a): ObjectA(a), m_a(a+1), m_resource(new int(a+2)) { cout << "Normal(int a)" << endl; }
    ~Normal() { delete m_resource; cout << "~Normal()" << endl; }
private:
    ObjectA m_a;
    Evil m_evil;
    int* m_resource;
};

static void hasMemoryLeak()
{
    try 
    {
        Normal n(1);
    }  
    catch (...)
    {

    }
}

int main()
{
    setenv("MALLOC_TRACE", "memoryCheck.log", 1);
    mtrace();

    hasMemoryLeak();

    return 0;
}
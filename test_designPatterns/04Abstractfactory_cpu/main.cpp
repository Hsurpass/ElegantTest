#include <iostream>

using namespace std;

class Cpu
{
public:
    virtual void work() = 0;
};
class SingleCoreA : public Cpu
{
public:
    void work()
    {
        cout << "SingleCoreA working" << endl;
    }
};
class SingleCoreB : public Cpu
{
public:
    void work()
    {
        cout << "SingleCoreB working" << endl;
    }
};

class AbstractFactory //
{
public:
    virtual Cpu *createSingleCore() = 0;
};

class factoryA : public AbstractFactory
{
public:
    factoryA() {}
    Cpu *createSingleCore()
    {
        return new SingleCoreA;
    }
};
class FactoryB : public AbstractFactory
{
public:
    FactoryB() {}
    Cpu *createSingleCore()
    {
        return new SingleCoreB;
    }
};

int main()
{
    AbstractFactory *abfac = new factoryA;
    abfac->createSingleCore()->work();

    abfac = new FactoryB;
    abfac->createSingleCore()->work();
    return 0;
}

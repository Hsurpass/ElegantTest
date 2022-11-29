#include <iostream>

using namespace std;

enum coretype
{
    coreA,
    coreB
};

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

class simplefactory
{
public:
    simplefactory() {}
    Cpu *createSingleCore(enum coretype type)
    {
        if (type == coreA)
        {
            return new SingleCoreA;
        }
        if (type == coreB)
        {
            return new SingleCoreB;
        }
    }
};

int main()
{
    simplefactory sf;
    Cpu *cpu = sf.createSingleCore(coreA);
    cpu->work();

    cpu = sf.createSingleCore(coreB);
    cpu->work();

    delete cpu;
    return 0;
}

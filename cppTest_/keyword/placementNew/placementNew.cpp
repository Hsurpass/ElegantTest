/*from fangdongheng P18 22-*/

#include <iostream>
#include <vector>

using namespace std;

class A
{
public:
    A() /*: m_value(new int(4))*/
    {
        cout << "A()" << endl;
    }
    ~A()
    {
        // delete m_value;
        cout << "~A()" << endl;
    }
private:
    int m_data[100];
    // int* m_value;
};

char info[10000];
void test_placementNew()
{
    // new 两个操作: 1.分配内存 2.调用构造函数
    // vector reserve 先申请一片连续的空间，等插入元素的时候调用 placement new 运算符
    A* s = new(info)A();

    // right
    s->~A();

    // error
    // delete 两个操作: 1.调用析构函数 2.释放内存
    // 但是此时释放的内存并不是new分配的，所以会出错
    // delete s;
}

int main()
{
    test_placementNew();


    return 0;
}
#include <iostream>

using namespace std;

class Object
{
public:
    Object():m_value(new int(4)) {}
    ~Object() {
        delete m_value;
    }
private:
    int m_data[100];
    int *m_value;
};
int main()
{
    char *info = new char[1000];
//    char info[10000];
    Object *s = new(info)Object;
    s->~Object();//正确的
    delete s;//内存泄漏
    return 0;
}

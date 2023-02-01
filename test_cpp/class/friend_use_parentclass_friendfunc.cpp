#include <iostream>

using namespace std;

class Student
{
public:
    Student():a(1),b(2)
    {
    }
    friend ostream &operator<<(ostream &out, Student &stu);

private:
    int a;
    int b;
};

ostream &operator<<(ostream &out, Student &stu)
{
    out << stu.a << "--" << stu.b << endl;
    return out;
}

class Graduate : public Student
{
    friend ostream &operator<<(ostream &out, Graduate &gra);
public:
    Graduate():c(10), d(20)
    {}
private:
    int c;
    int d;
};

ostream &operator<<(ostream &out, Graduate &gra)
{
    out << (Student&)gra << endl;
    out << gra.c << "**" << gra.d << endl;

    out << (Student&)gra << gra.c << "**" << gra.d << endl;

    return out;
}

void test_childcalss_use_parentclass_friendfunc()
{
    Student stu;
    cout << stu;

    Graduate gra;
    cout << gra;
}

int main()
{
    test_childcalss_use_parentclass_friendfunc();

    return 0;
}
#include <iostream>
#include <typeinfo>

using namespace std;

class A
{
public:
	virtual ~A() {} // 若无此虚函数， 则称运行时信息不成立
};
class B : public A
{
};
class C : public A
{
};
void func(A *pa)
{
	cout << typeid(pa).name() << endl;
	cout << typeid(*pa).name() << endl;
}
void func(A &ra)
{
	cout << typeid(ra).name() << endl;
}

void test_typeid_with_virtualFunc()
{
	B b;
	C c;
	A *pa = &b;

	cout << typeid(A).name() << endl;
	cout << typeid(B).name() << endl;
	cout << typeid(C).name() << endl;

	cout << typeid(A*).name() << endl;
	cout << typeid(B*).name() << endl;
	cout << typeid(C*).name() << endl;
	cout << "------------------------------" << endl;

	cout << typeid(b).name() << endl;	// B
	cout << typeid(c).name() << endl;	// C
	cout << typeid(pa).name() << endl;	// A
	
	A &ra = b;
	cout << typeid(b).name() << endl;	// B
	cout << typeid(ra).name() << endl;	// B
	ra = c;
	A& raa = c;
	cout << typeid(c).name() << endl;	// C
	cout << typeid(ra).name() << endl;	// B
	cout << typeid(raa).name() << endl;	// C
	
	func(&c);	// A C
	func(&b);	// A B
}

void test_typeid()
{
	cout << typeid(char).name() << endl;			   // char
	cout << typeid(signed char).name() << endl;		   // char
	cout << typeid(unsigned char).name() << endl;	   // unsigned char
	cout << typeid(short).name() << endl;			   // short
	cout << typeid(signed short).name() << endl;	   // short
	cout << typeid(unsigned short).name() << endl;	   // unsigned short
	cout << typeid(int).name() << endl;				   // int
	cout << typeid(signed int).name() << endl;		   // int
	cout << typeid(unsigned int).name() << endl;	   // unsigned int
	cout << typeid(long).name() << endl;			   // long
	cout << typeid(signed long).name() << endl;		   // long
	cout << typeid(unsigned long).name() << endl;	   // unsigned long
	cout << typeid(long long).name() << endl;		   // long long __int64
	cout << typeid(signed long long).name() << endl;   // long long __int64
	cout << typeid(unsigned long long).name() << endl; // unsigned long long unsigned __int64
	cout << typeid(float).name() << endl;			   // float
	cout << typeid(double).name() << endl;			   // double
	cout << typeid(char *).name() << endl;			   // char*
	cout << typeid(signed char *).name() << endl;	   // char*
	cout << typeid(unsigned char *).name() << endl;	   // unsigned char*

	int i = 10;
	cout << typeid(i).name() << endl; // int 不同平台name可能不相同
}

int main()
{
	// test_typeid();
	test_typeid_with_virtualFunc();

	return 0;
}
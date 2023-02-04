#include <iostream>
#include <string.h>
#include <stdlib.h>

using namespace std;

struct TrafficEvent
{
	bool forbid;					// 1
	int restrictedVehicleTypes;		// 4
	char eventIdUpstream[256];		// 256
	int eventSource;				// 4
	int eventId;					// 4
	int type;						// 4
	int descriptionLength;			// 4
	char description[];				// 0
};									// 277

struct A
{
	int a;
	char b[];
};

struct B
{
	// char c;		// 1
	// char c[1];	// 1
	// char c[2];	// 2
	// char c[3];	// 3
	/* data */
};

struct C
{
	int a;
	char* p;
	char b[];	// 必须在末尾
};

class D{
public:
	D(){ cout << "D()" << endl; }
	~D(){ cout << "~D()" << endl; }

	void setc(const char* str) { strcpy(c, str); }
	const char* getc() { return c; }

	int a;
// protected:
// private:
	char c[];   //不使用非类型模板参数，空数组一定要放后面是。否则error: flexible array member ‘D::c’ not at end of ‘class D’
	// int a;
};

// 使用const int n作为数组参数还是不行的
class E{
public:
	E(int _n):n(_n) { cout << "E()" << endl; }
	~E(){ cout << "~E()" << endl; }

	// void setc(const char* str) { strncpy(c, str); }  // error
	// void setc(const char* str) { strncpy(c, str, n); }  // error
	// const char* getc() { return c; }

	int a;
// protected:
private:
    const int n;
	// char c[n];  // error
};

template<int N>
class F
{
public:
    F() { cout << "F()" << endl; }
	~F(){ cout << "~F()" << endl; }

	void setc(const char* str) { strncpy(c, str, N); }
	const char* getc() { return c; }

	// int a;
// protected:
// private:
	char c[N];  // 使用非类型模板参数，空数组就不一定要放到末尾了
	int a;
};


void test_classF()
{
    cout << "sizeof(F):" << sizeof(F<6>) << endl;       // 4 + 6=10 --->内存对齐 12
    cout << "sizeof(F.a):" << sizeof(F<6>().a) << endl;   // 4
    cout << "sizeof(F.c):" << sizeof(F<6>().c) << endl;   // 6

    F<6> f;
    cout << "sizeof(f):" << sizeof(f) << endl;       // 4 + 6=10 --->内存对齐 12
    cout << "sizeof(f.a):" << sizeof(f.a) << endl;   // 4
    cout << "sizeof(f.c):" << sizeof(f.c) << endl;   // 6
    cout << "&f.a:" << &f.a << endl;
    cout << "&f.c:" << &f.c << endl;

    f.a = 100;
    f.setc("hello");
    cout<< f.a << endl;
    cout<< f.getc() << endl;

    cout << "---------------------------" << endl;
    F<12>* pf = new F<12>();
    cout << "sizeof(*pf):" << sizeof(*pf) << endl;       // 4 + 12=16 
    cout << "sizeof(pf->a):" << sizeof(pf->a) << endl;   // 4
    cout << "sizeof(pf->c):" << sizeof(pf->c) << endl;   // 12
    pf->a = 200;
    pf->setc("hello world");
    cout<< pf->a << endl;
    cout << pf->getc() << endl;
    delete pf;
    pf->setc("12345 67890232429");
    cout << pf->getc() << endl;

}

void test_classD_malloc_plus_placementNew()
{
    // void * p = malloc( sizeof(D) + 6);
    // void *p = new char[sizeof(D) + 6];
    char p[sizeof(D) + 6] = {0};
	D* pd = new (p)D;

	pd->a = 100;
	pd->setc("world");
	cout << pd->a << endl;
	cout << pd->getc() << endl;

	pd->~D();   // 要显示的调用析构函数
	// free(pd);
    // delete[] p;
}

void test_classD()
{
	// D d;
	// d.a = 10;
	// strcpy(d.c, "hello");	// abort
	cout << "sizeof(D):" << sizeof(D) << endl;	// 4
	
    // 都没由调用构造和析构，要想调用使用定位new运算符，看上面的例子。
	D* pd = (D*)malloc(sizeof(D) + 6);	// 10
	cout << "sizeof(D):" << sizeof(D) << endl;	// 4

	pd->a = 100;
	// strcpy(pd->c, "world");
	pd->setc("world");
	cout << pd->a << endl;
	// cout << pd->c << endl;
	cout << pd->getc() << endl;

	free(pd);
}

void test_structA()
{
	// A a1;
	// a1.a = 10;
	// strcpy(a1.b, "hello");	// abort
	cout << "sizeof(A):" << sizeof(A) << endl;	// 4
	
	A* pa = (A*)malloc(sizeof(A) + 6);	// 10
	cout << "sizeof(A):" << sizeof(A) << endl;	// 4

	pa->a = 100;
	strcpy(pa->b, "world");
	cout << pa->a << endl;
	cout << pa->b << endl;

	free(pa);

}

void test_structC()
{
	// A a1;
	// a1.a = 10;
	// strcpy(a1.b, "hello");	// abort

	cout << "sizeof(void*):" << sizeof(void*) << endl;	// 8
	cout << "sizeof(C):" << sizeof(C) << endl;	// 4 + 8 => 16

	C* pc = (C*)malloc(sizeof(C) + 12);
	pc->a = 100;
	// *(pc->p) = 'c';
	strcpy(pc->b, "hello world");
	cout << pc->a << endl;
	// cout << pc->p << endl;
	cout << pc->b << endl;

	free(pc);
}

void test_struct()
{
	cout << "sizeof(TrafficEvent):" << sizeof(TrafficEvent) << endl;
	cout << "sizeof(A):" << sizeof(A) << endl;	// 4	空数组不占位
	cout << "sizeof(B):" << sizeof(B) << endl;	// 1
	cout << "sizeof(C):" << sizeof(C) << endl;	// 16
	cout << "sizeof(D):" << sizeof(D) << endl;	// 4
}


int main()
{
    // test_struct();
	// test_structA();
	// test_structC();
	test_classD();
    // test_classD_malloc_plus_placementNew();
    // test_classF();

    return 0;
}
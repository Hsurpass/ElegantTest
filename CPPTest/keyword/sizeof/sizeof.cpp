#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <deque>
#include <forward_list>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <hash_fun.h>
#include <memory>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

// #include "struct/routing/routingResponse.h"

using namespace std;

// #pragma pack(push, 1)

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
	/* data */
};

struct C
{
	int a;
	char* p;
	char b[];	// 必须在末尾
};

void test_structA()
{
	// A a1;
	// a1.a = 10;
	// strcpy(a1.b, "hello");	// abort
	cout << "sizeof(A):" << sizeof(A) << endl;	// 4
	A* pa = (A*)malloc(sizeof(A) + 6);	// 10
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

void test01()
{
	char b[] = {0};
	char b1[] = {0,0};
	int c[] = {0};
	int c1[] = {0,0};
	cout << "sizeof(TrafficEvent):" << sizeof(TrafficEvent) << endl;
	cout << "sizeof(A):" << sizeof(A) << endl;	// 4
	cout << "sizeof(B):" << sizeof(B) << endl;	// 1
	cout << "sizeof(C):" << sizeof(C) << endl;	// 16

	cout << sizeof(b) << endl;			// 1
	cout << sizeof(b1) << endl;			// 2
	cout << sizeof(c) << endl;			// 4
	cout << sizeof(c1) << endl;			// 8

	cout << "sizeof(bool):" << sizeof(bool)	<< endl;		// 1
	cout << "sizeof(char):" << sizeof(char)	<< endl;		// 1
	cout << "sizeof(wchar_t):" << sizeof(wchar_t) << endl;	// 4
	cout << "sizeof(char16_t):" << sizeof(char16_t) << endl;	// 2
	cout << "sizeof(char32_t):" << sizeof(char32_t) << endl;	// 4
	cout << "sizeof(int):" << sizeof(int) << endl;		//4
	cout << "sizeof(long int):" << sizeof(long int) << endl;		//4
	cout << "sizeof(long):" << sizeof(long)	<< endl;			// 4 8
	cout << "sizeof(long long):" << sizeof(long long) << endl;	// 8
	cout << "sizeof(float):" << sizeof(float)	<< endl;			// 4
	// cout << "sizeof(double):" << sizeof(long float)	<< endl;			// 8
	cout << "sizeof(double):" << sizeof(double)	<< endl;			// 8
	cout << "sizeof(long double):" << sizeof(long double)<< endl;	// 16
	cout << "sizeof(size_t):" << sizeof(size_t)<< endl;	// 8
	cout << "sizeof(void*):" << sizeof(void*)<< endl;	// 8

}

enum event {
	aa,
	bb,
	cc
};
enum _Rb_tree_color_ { _S_red = false, _S_black = true };

void test02()
{
	event e;
	cout << sizeof(e) << endl;	// 4
	
	cout << sizeof(event) << endl;	// 4
	cout << sizeof(_Rb_tree_color_) << endl;	// 4
}

void func()
{
	int a = 3;
}
void test03()
{
	// c++ primer 4.9 lianxi 4.30
	int x = 1, y = 2;
	int count = 0;
	
	count = sizeof x + y;	// 相当于sizeof(x) + y
	cout << count << endl; 	// 6
	count = sizeof(x + y);	// 4
	cout << count << endl; 

	count = sizeof x < y;	// 相当于sizeof(x) < y ---> 4 < 2 --->false
	cout << count << endl;	// 0
	count = sizeof(x < y);	
	cout << count << endl;	// 1

	count = sizeof func();	// 1
	cout << count << endl;
	count = sizeof(func());	// 1
	cout << count << endl;

	struct A
	{
		double mem[16];
	};
	A* p = NULL;
	count = sizeof p->mem[0];	// 8
	cout << count << endl;
	count = sizeof(p->mem[0]);	// 8
	cout << count << endl;

}

void test04()
{	
	// void*
	cout << "sizeof(void*):" << endl;
	void* p = NULL;
	cout << sizeof(p) << endl;
	cout << sizeof(void*) << endl;

	// array
	cout << "sizeof array:" << endl;
	array<int, 1> arri;
	cout << sizeof(arri) << endl;
	cout << sizeof(array<int, 10>) << endl;
	cout << sizeof(array<string, 1>) << endl;
	cout << sizeof(array<string, 10>) << endl;

	// forward_list
	cout << "sizeof forward_list:" << endl;
	forward_list<int> fl;
	cout << sizeof(fl) << endl;
	cout << sizeof(forward_list<bool>) << endl;
	cout << sizeof(forward_list<string>) << endl;

	// vector
	cout << "sizeof vector:" << endl;
	std::vector<int> a;
	cout << sizeof(a) << endl;
	cout << sizeof(vector<int>) << endl;
	cout << sizeof(vector<string>) << endl;

	// list
	cout << "sizeof list:" << endl;
	list<int> l;
	cout << sizeof(l) << endl;
	cout << sizeof(list<int>) << endl;
	cout << sizeof(list<string>) << endl;

	// string
	cout << "sizeof string:" << endl;
	string b;
	cout << sizeof(b) << endl;
	cout << sizeof(string) << endl;

	// deque
	cout << "sizeof deque:" << endl;
	deque<int> di;
	cout << sizeof(di) << endl;
	deque<string> ds;
	cout << sizeof(ds) << endl;

	// stack 适配器 adapter
	cout << "sizeof stack:" << endl;
	cout << sizeof(stack<int>) << endl;
	cout << sizeof(stack<string>) << endl;

	// queue
	cout << "sizeof queue:" << endl;
	cout << sizeof(queue<int>) << endl;
	cout << sizeof(queue<string>) << endl;

	// priority queue
	cout << "sizeof priority queue:" << endl;
	cout << sizeof(priority_queue<int>) << endl;
	cout << sizeof(priority_queue<string>) << endl;
	
	// map 
	cout << "sizeof map:" << endl;
	std::map<int, int> m1;
	std::map<int, string> m2;
	std::map<string, string> m3;
	
	cout << sizeof(m1) << endl;
	cout << sizeof(m2) << endl;
	cout << sizeof(m3) << endl;


	// multimap
	cout << "sizeof multimap:" << endl;
	multimap<int, int> mul1;
	multimap<int, string> mul2;
	multimap<string, string> mul3;
	cout << sizeof(mul1) << endl;
	cout << sizeof(mul2) << endl;
	cout << sizeof(mul3) << endl;

	// set
	cout << "sizeof set:" << endl;
	set<int> s1;
	set<string> s2;
	set<bool> s3;
	cout << sizeof(s1) << endl;
	cout << sizeof(s2) << endl;
	cout << sizeof(s3) << endl;

	// multiset 
	cout << "sizeof multiset:" << endl;
	multiset<int> multis1;
	multiset<string> multis2;
	multiset<bool> multis3;
	cout << sizeof(s1) << endl;
	cout << sizeof(s2) << endl;
	cout << sizeof(s3) << endl;
}


void test05()
{
	std::cout << sizeof("exec ") << std::endl;
}

void test_smart_ptr()
{
	cout << "sizeof(void*):" << sizeof(void*) << endl;	// 8
	// auto_ptr
    cout << "sizeof(auto_ptr<int>): " << sizeof(auto_ptr<int>) << endl;			// 8
	cout << "sizeof(auto_ptr<double>): " << sizeof(auto_ptr<double>) << endl;	// 8
	
	// unique_ptr
	cout << "sizeof(unique_ptr<int>): " << sizeof(unique_ptr<int>) << endl;		 // 8
	cout << "sizeof(unique_ptr<double>): " << sizeof(unique_ptr<double>) << endl;// 8
	
	// shared_ptr
	cout << "sizeof(shared_ptr<int>): " << sizeof(shared_ptr<int>) << endl;		 // 16
	cout << "sizeof(shared_ptr<double>): " << sizeof(shared_ptr<double>) << endl;// 16
	// weak_ptr
	cout << "sizeof(weak_ptr<int>): " << sizeof(weak_ptr<int>) << endl;		// 16
	cout << "sizeof(weak_ptr<double>): " << sizeof(weak_ptr<double>) <<endl;// 16
}

class Empty
{

};
class HoldsAnInt
{
// private:
public:
	int x;		// 4	
	Empty e;	// 4(字节对齐)
};
class InheritEmpty : public Empty
{
// public:
private:
	int x;
};

void test_empty_class01()
{
	cout << sizeof(Empty) << endl;	// 1
	cout << sizeof(HoldsAnInt) << endl;	// 8
	// sizeof(int) < sizeof(HoldsAnInt)
	if( sizeof(int) == sizeof(HoldsAnInt) )
	{
		cout << "sizeof(int) == sizeof(HoldsAnInt)" << endl;
	}
	else if(sizeof(int) > sizeof(HoldsAnInt))
	{
		cout << "sizeof(int) > sizeof(HoldsAnInt)" << endl;
	}
	else
	{
		cout << "sizeof(int) < sizeof(HoldsAnInt)" << endl;
	}
	// assert(sizeof(int) == sizeof(HoldsAnInt));
	// static_assert(sizeof(int) == sizeof(HoldsAnInt), "sizeof(int) == sizeof(HoldsAnInt)");
}

void test_empty_class02()
{
	cout << "sizeof(InheritEmpty):" << sizeof(InheritEmpty) << endl;	// 8
	// sizeof(int) == sizeof(InheritEmpty)
	if( sizeof(int) == sizeof(InheritEmpty) )
	{
		cout << "sizeof(int) == sizeof(InheritEmpty)" << endl;
	}
	else if(sizeof(int) > sizeof(InheritEmpty))
	{
		cout << "sizeof(int) > sizeof(InheritEmpty)" << endl;
	}
	else
	{
		cout << "sizeof(int) < sizeof(InheritEmpty)" << endl;
	}
}

int main()
{
	cout << "sizeof(int):" << sizeof(int) << endl;
	cout << "sizeof(int32_t):" << sizeof(int32_t) << endl;
	cout << "sizeof(int64_t):" << sizeof(int64_t) << endl;
	cout << "sizeof(void*)" << sizeof(void*) << endl;
	// cout << sizeof(ncStruct::RegulationResult) << endl;
	
	// test01();
	// test02();
	// test03();
	// test04();
	//test05();
	// test_smart_ptr();
	// test_structA();
	// test_structC();
	// test_empty_class01();
	test_empty_class02();
}

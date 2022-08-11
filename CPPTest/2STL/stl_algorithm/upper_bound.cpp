#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <iterator>

using namespace std;

template<typename T>
void printIterator(std::vector<T>& v, typename std::vector<T>::iterator& posItr)
{
	if (posItr != v.end())
	{
		cout << "lowiter pos: " << posItr - v.begin() << endl;
	}
	else
	{
		cout << "lowiter == end" << endl;
	}
}

class A
{
public:
	A(int a,char b);
	~A();
	void dis(){ cout << "a:" << m_a << ", " << "b:" << m_b << endl; }
//private:
	int m_a;
	char m_b;
};

A::A(int a,char b)
{
	m_a = a;
	m_b = b;
}

A::~A()
{
}
void func(A& raa)
{
	raa.m_a = 100;
}

void func1(A* raa)
{
	raa->m_a = 200;
}

int test()
{
	// unsigned char a = 0xff + 251;
	char a = 0xff;

	printf("%d\n", a);
	printf("%u\n", a);

	return 0;
}

int main03()
{
	//int a = 0;
	//int b = 1;
	A a(10, 'a');
	A b(20, 'b');

	//int &ra = a;
	func(a);
	//func1(&a);

	//ra = 100;
	cout << "a:" << a.m_a << endl;
	cout << "b:" << b.m_a << endl;

	//ra = b;
	//ra = 101;
	func(b);

	//func1(&b);
	cout << "a:" << a.m_a << endl;
	cout << "b:" << b.m_a << endl;

	return 0;
}

void test_std_lower_bound_and_upper_bound_useClass()
{
	A a(1, 'a');
	A b(2, 'b');
	A c(2, 'c');
	A d(3, 'd');
	A e(5, 'e');
	A f(6, 'f');

	vector<A> v;
	v.push_back(a);
	v.push_back(b);
	v.push_back(c);
	v.push_back(d);
	v.push_back(e);
	v.push_back(f);

	for (vector<A>::iterator itr = v.begin(); itr != v.end();++itr)
	{
		itr->dis();
	}
	cout << "--------------------" << endl;
	std::sort(v.begin(), v.end(), [](const A& m, const A& n){
		return m.m_a < n.m_a;
	});
	for (vector<A>::iterator itr = v.begin(); itr != v.end(); ++itr)
	{
		itr->dis();
	}
	cout << "--------------------" << endl;

	// 第一个大于等于5的位置  // notice v.begin() + 2  pos:2
#if 0
	vector<A>::iterator lowiter = std::lower_bound(v.begin(), v.begin() + 2, 5, [](const int& value, const A& tmp){
		return value < tmp.m_a;
	});
#endif
#if 1
	vector<A>::iterator lowiter = std::lower_bound(v.begin(), v.begin() + 2, A(5, 'g'), [](const A& value, const A& tmp){
		return value.m_a < tmp.m_a;
	});
#endif
	printIterator(v, lowiter);
	lowiter->dis();

	// 第一个大于5的位置  // // notice v.begin() + 2  pos:2
	vector<A>::iterator upiter = std::upper_bound(v.begin(), v.begin() + 2, 5, [](const int& value, const A& tmp){
		return value < tmp.m_a;
	});
	printIterator(v, upiter);
	upiter->dis();

	cout << "-----------------------------------------" << endl;
	// 第一个大于等于5的位置  // notice v.end()  pos:4
#if 0
	vector<A>::iterator lowiter = std::upper_bound(v.begin(), v.end(), 5, [](const int& value, const A& tmp){
		return value < tmp.m_a;
	});
#endif
#if 1
	lowiter = std::lower_bound(v.begin(), v.end(), A(5, 'g'), [](const A& value, const A& tmp){
		return value.m_a < tmp.m_a;
	});
#endif
	printIterator(v, lowiter);
	lowiter->dis();

	// 第一个大于5的位置  // // notice v.end()  pos:5
	upiter = std::upper_bound(v.begin(), v.end(), 5, [](const int& value, const A& tmp){
		return value < tmp.m_a;
	});
	printIterator(v, upiter);
	upiter->dis();

	return ;
}


void test_std_lower_bound_and_upper_bound_useArray() 
{
	//  0  1  2  3  4  5  6  7
	// 10 10 10 20 20 20 30 30

	// 10 20 30 30 20 10 10 20
	int myints[] = { 10, 20, 30, 30, 20, 10, 10, 20 };

	// 使用lower_bound 和 upper_bound 的序列必须是有序的
	std::sort(myints, myints + 8);     
	for (auto i : myints)
	{
		cout << i << " ";
	}
	cout << endl;
	           
	int count = sizeof(myints);

	int* low = std::lower_bound(myints, myints + count, 30);	//  6   第一个大于等于30的位置
	int* up = std::upper_bound(myints, myints + count, 30);  //  8   第一个大于30的位置

	int lowPos = low - myints;
	if (lowPos != count)
	{
		cout << "low: " << *low  << ", lower_bound at position: "<< lowPos << endl;

	}
	else
	{
		cout << "low == end" << endl;
	}

	int upPos = up - myints;
	if (upPos != count)
	{
		cout << "up: " << *up << ", upper_bound at position " << upPos << endl;
	}
	else
	{
		cout << "up == end" << ", upper_bound at position " << upPos << endl;
	}

}

void test_std_lower_bound_and_upper_bound_useVector() 
{
	//  0  1  2  3  4  5  6  7
	// 10 10 10 20 20 20 30 30

	// 10 20 30 30 20 10 10 20
	int myints[] = { 10, 20, 30, 30, 20, 10, 10, 20 };
	std::vector<int> v(myints, myints + 8);           

	// 使用lower_bound 和 upper_bound 的序列必须是有序的
	std::sort(v.begin(), v.end());     
	for (auto i : v)
	{
		cout << i << " ";
	}
	cout << endl;
	           

	std::vector<int>::iterator low, up;
	low = std::lower_bound(v.begin(), v.end(), 30);	//  6   第一个大于等于30的位置
	up = std::upper_bound(v.begin(), v.end(), 30);  //  8   第一个大于30的位置
	printIterator(v, low);
	printIterator(v, up);

	cout << "----------------------------" << endl;
	low = std::lower_bound(v.begin(), v.end(), 40);	//  end   第一个大于等于40的位置
	up = std::upper_bound(v.begin(), v.end(), 40);  //  end   第一个大于40的位置
	printIterator(v, low);
	printIterator(v, up);

	//  0  1  2  3  4  5  6  7
	// 10 10 10 20 20 20 30 30
	cout << "----------------------------" << endl;
	low = std::lower_bound(v.begin(), v.end(), 10);	//  0   第一个大于等于10的位置
	up = std::upper_bound(v.begin(), v.end(), 10);  //  3   第一个大于10的位置
	printIterator(v, low);
	printIterator(v, up);


}

int main()
{
	test_std_lower_bound_and_upper_bound_useVector();
	// test_std_lower_bound_and_upper_bound_useArray();
	// test_std_lower_bound_and_upper_bound_useClass();

	return 0;
}
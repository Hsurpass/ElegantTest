#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
using namespace std;

template<typename T> 
static void _string2number(const char* str, T* number)
{
	cout << "_string2number(const char* str, T* number)" << endl;
	*number = atoi(str);
}

// 函数模板的全特化
template<>
void _string2number(const char* str, float* number)
{
	cout << "_string2number(const char* str, float* number)" << endl;
	*number = atof(str);
}

template<>
void _string2number(const char* str, long long* number)
{
	cout << "_string2number(const char* str, long long* number)" << endl;
	*number = atoll(str);
}

template <typename T>
static void _numberArrayFromString(vector<T>* arr, const char* str)
{
	T element;

	_string2number(str, &element);

	arr->push_back(element);
}

void test_string2number()
{
	const char* str = "123.34";
	float num1;
	_string2number(str, &num1);	// _string2number(const char* str, float* number)
	cout << num1 << endl;
	
	str = "12345";
	int num2;
	_string2number(str, &num2);	// _string2number(const char* str, T* number)
	cout << num2 << endl;

	str = "1234567890123456789";
	long long num3;
	_string2number(str, &num3);	// _string2number(const char* str, long long* number)
	cout << num3 << endl;
}

void test_numberArrayFromString()
{
	/*char* str = "123.34";
	vector<float> f;
	_numberArrayFromString(&f, str);*/

	/*char* str = "12345";
	vector<int> v;
	_numberArrayFromString(&v, str);*/

	const char* str = "1234567890123456789";
	vector<long long> v;
	_numberArrayFromString(&v, str);

	for (auto &i : v)
	{
		cout << i << " ";
	}
	cout << endl;

}

template<typename T>
T sum(T a, T b)
{
	return a + b; 
}


int main()
{
	// test_string2number();
	cout << sum(1.5, 2.3) << endl;

	return 0;
}
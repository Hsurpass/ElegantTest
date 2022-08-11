#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
using namespace std;

template<typename T> 
void _string2number(const char* str, T* number)
{
	*number = atoi(str);
}

template<>
static void _string2number(const char* str, float* number)
{
	*number = atof(str);
}

template<>
static void _string2number(const char* str, long long* number)
{
	*number = atoll(str);
}

template <typename T>
static void _numberArrayFromString(vector<T>* arr, const char* str)
{
	T element;

	_string2number(str, &element);

	arr->push_back(element);
}

int main()
{
	char* str = "123.34";
	float num1;
	_string2number(str, &num1);
	cout << num1 << endl;
	
	str = "12345";
	int num2;
	_string2number(str, &num2);
	cout << num2 << endl;

	str = "1234567890123456789";
	long long num3;
	_string2number(str, &num3);
	cout << num3 << endl;
}

int main01()
{
	/*char* str = "123.34";
	vector<float> f;
	_numberArrayFromString(&f, str);*/

	/*char* str = "12345";
	vector<int> v;
	_numberArrayFromString(&v, str);*/

	char* str = "1234567890123456789";
	vector<long long> v;
	_numberArrayFromString(&v, str);

	for (auto &i : v)
	{
		cout << i << " ";
	}
	cout << endl;

	return 0;
}
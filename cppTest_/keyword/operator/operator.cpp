#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>

using namespace std;

void test1()
{
    // c++ primer 4.1.3
    int i = 0;
    cout << i << " " << ++i << endl;
}

void test2()
{
    // c++ primer 4.2
    int i = 1024;
    int k = -i; //-1024

    bool b = true;
    bool b2 = -b;   // true; 布尔值不参与运算
    cout << b << endl;
    cout << b2 << endl;
}

void test3()
{
    // c++ primer 练习4.13
    int i; double d;
    d = i = 3.5;
    cout << d << " " << i << endl;
    i = d = 3.5;
    cout << d << " " << i << endl;
}

void test4()
{
    // c++ primer 练习4.20
    vector<string> vs = {"abc", "def", "hig"};
    vector<string>::iterator iter;
    iter = vs.begin();
    cout << *iter << endl;

    // cout << ++*iter << endl; // error
    cout << iter++->empty() << endl;    // right
}

void test5()
{
    // c++ primer 4.7
    int grade = 30;
    cout << (grade < 60) ? "fail" : "pass";     // 相当于 cout << (grade < 60);
                                                //        cout << ? "fail" : "pass";
    // cout << grade < 60 ? "fail" : "pass";   // error

    cout << endl;

    // c++ primer 练习4.23
    string s = "word";
    // string p1 = s + s[s.size() - 1] == 's' ? "" : "s";
    string p1 = s + s[s.size() - 1] == "s" ? "" : "s";
    cout << p1 << endl;
    // cout << s == 'a';
    
}

void test6()
{
    cout << L"\\" << endl;
    char *p = "\\\\";
    // char *p1 = L"\\"; //cannot convert ‘const wchar_t*’ to ‘char*’ in initialization
    wchar_t p1[10] = L"\\\\";

    printf("%s\n", p);
    printf("%S\n", p1);

}

int main()
{
    // test1();
    // test2();
    // test3();
    
    // test4();
    // test5();
    test6();


    return 0;
}

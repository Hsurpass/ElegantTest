#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

struct A
{
    string s;
    vector<string> vvs;
};

struct B
{
    string b;
    A a;
};

// string::find_last_not_of s.find_last_not_of(args) 在s中查找最后一个不在args中的字符的位置，没搜索到返回string::npos
void test12()
{
    string numbers("0123456789"), dept("03714p3a"), str("123");
    auto pos = dept.find_last_not_of(numbers); // name中的字符第一个不会出现在numbers中的位置
    cout << pos << endl;    // 7

    pos = str.find_last_not_of(numbers);
    cout << pos << endl;    // string::npos (unsigned ..)-1
}

// string::find_first_not_of  s.find_first_not_of(args) 在s中查找第一个不在args中的字符的位置，  没搜索到返回string::npos
void test11()
{
    string numbers("0123456789"), dept("03714p3"), str("123");
    auto pos = dept.find_first_not_of(numbers); // name中的字符第一个不会出现在numbers中的位置
    cout << pos << endl;    // 5

    pos = str.find_first_not_of(numbers);
    cout << pos << endl;    // string::npos (unsigned ..)-1
}

// std::find_last_of s.find_last_of(args) 在s中查找args任一字符最后一次出现在s中的位置，没搜索到返回string::npos
void test10()
{
    string numbers("0123456789"), str("abc"), name("r2d2");
    auto pos = name.find_last_of(numbers); // numbers中的字符第一个出现在name中的位置
    cout << pos << endl;    // 3

    auto pos1 = name.find_last_of(str);
    cout << pos1 << endl;   // string::npos (unsigned ..)-1
}

// string::find_first_of s.find_first_of(args) 在s中查找args中任一字符第一次出现在s中的位置， 没搜索到返回string::npos
void test09()
{
    string numbers("0123456789"), str("abc"), name("r2d2");
    auto pos = name.find_first_of(numbers); // numbers中的字符第一个出现在name中的位置
    cout << pos << endl;    // 1

    auto pos1 = name.find_first_of(str);
    cout << pos1 << endl;   // string::npos (unsigned ..)-1

}

// string::rfind  s.rfind(args) //在s中查找args最后一次出现在s中的位置， 没搜索到返回string::npos
void test08()
{
    string name("AnnaBelleAnna");
    auto pos = name.rfind("Anna");
    cout << pos << endl;    // 9

    auto pos1 = name.rfind("Annl");
    cout << pos1 << endl;    // string::npos (unsigned ..)-1
}

// string::find  s.find(args) //在s中查找args第一次出现在s中的位置, 没搜索到返回string::npos
void test07()
{
    string name("AnnaBelle");
    auto pos = name.find("Anna");
    cout << pos << endl;    // 0

    auto pos1 = name.find("Annl");
    cout << pos1 << endl;    // string::npos (unsigned ..)-1

}

// c++ primer string substr
void test06()
{
    string s("hello world");

    string s3 = s.substr(6);
    cout << s3 << endl;
    // string s5 = s.substr(12);   // 抛出out_of_range异常
}

//memset后默认值的问题
void test05()
{
    cout << "sizeof(A):" << sizeof(A) << endl;

    A* p = (A*)malloc(sizeof(A));
    memset(p, 0, sizeof(A));

    cout << "-" << p->s << "-" << endl;
    if (p->s.empty())   // string 默认是空串，如果加判断的话，就会进入到if里面，如果不加判断就会打印空串
    {
        cout << "p->s is empty" << endl;
    }
    else    // is not empty
    {
        cout << "p->s is not empty" << endl;
        cout << "-" << p->s << "-" << endl;
    }

    // vector 默认就为0
    if (p->vvs.empty())
    {
        cout << "p->vvs is empty" << endl;
    }
    else
    {
        for (vector<string>::iterator itr = p->vvs.begin(); itr != p->vvs.end(); ++itr)
        {
            cout << "#" << *itr << "#" << endl;
        }
    }
    
    cout << "-----------------------------------" << endl;

    p->s = "string";
    p->vvs.push_back("abc");
    p->vvs.push_back("def");
    p->vvs.push_back("lmn");
    p->vvs.push_back("gdk");
    p->vvs.push_back("ccc");

    cout << "sizeof(A):" << sizeof(A) << endl;
    cout << p->s << endl;
    for (vector<string>::iterator itr = p->vvs.begin(); itr != p->vvs.end(); ++itr)
    {
        cout << *itr << endl;
    }
    
    /////////////////////////////////////////////////////////////////

    B* pb = (B*)malloc(sizeof(B));
    memset(pb, 0, sizeof(B));

    cout << "sizeof(B):" << sizeof(B) << endl;
    cout << "sizeof(pb->a):" << sizeof(pb->a) << endl;
    cout << "sizeof(pb->b):" << sizeof(pb->b) << endl;

    cout << "-" << pb->b << "-" << endl;    // ""
    cout << "-" << pb->a.s << "-" << endl;  // ""

    cout << "" << pb->a.vvs.size() << endl; // 0

}

void test04()
{
    unsigned int cnt = 40;
    const unsigned int sz = 40;
    int arr[cnt];

    string bad[cnt];
    string strs[sz];
    vector<string> vs;  

    cout << sizeof(string) << endl; // 32
    cout << sizeof(bad)/sizeof(string) << endl;     // 40
    cout << sizeof(strs)/sizeof(string) << endl;    // 40
    cout << sizeof(vs) << endl; // 24

    vs.push_back("abc");
    vs.push_back("def");
    vs.push_back("ghi");
    vs.push_back("jkl");

    cout << sizeof(vs) << endl; // 24

}

void test03()
{
    string line;
    while (getline(cin,line))
    {
        cout << line << endl;
        // line.size();
        // string::size_type;
    }

}

void test02()
{
    string word;

    while (cin >> word)
    {
        cout << word << endl;
    }

}

void test01()
{
    string s1, s2;
    cin >> s1 >> s2;

    cout << s1 << s2 << endl;

}

int main()
{
    // test01();
    // test02();
    // test03();
    // test04();
    // test05();
    // test06();
    // test07();
    // test08();
    // test09();
    // test10();
    // test11();
    test12();


    
    return 0;
}
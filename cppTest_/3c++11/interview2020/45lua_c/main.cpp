#include <iostream>
//#include "lua.h"
//#include "lualib.h"
//#include "lauxlib.h"
#include "lua.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

using namespace std;

void printluastack(lua_State* L)
{
    static int count = 0;
    count++;
    printf("begin dump lua stack %d\n", count);
    int i = 0;
    int top = lua_gettop(L);
    for(i = top;i >= 1;--i)
    {
        int type = lua_type(L,i);
        switch (type) {
        case LUA_TNUMBER:
            printf("%g\n",lua_tonumber(L,i));
            break;
        case LUA_TSTRING:
            printf("'%s'\n",lua_tostring(L,i));
            break;
        case LUA_TBOOLEAN:
            printf("%s\n",lua_toboolean(L,i)?"true":"false");
            break;
        default:
            printf("other type %s\n",lua_typename(L,type));
            break;
        }
    }
    printf("end dump lua stack %d\n", count);
}
int main01()
{
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    //    printluastack(L);

    lua_pushinteger(L,1);
    lua_pushinteger(L,2);
    lua_pushinteger(L,3);
    lua_pushinteger(L,4);
    printluastack(L);

    //    cout << lua_gettop(L) << endl;
    //    lua_settop(L,8);
    //    lua_settop(L,3);
    //    printluastack(L);

    //    lua_pop(L,3);
    //    lua_pop(L,6);

    //    lua_pushvalue(L,4);
    //    lua_pushvalue(L,1);
    //    lua_replace(L,1);

    //    lua_rotate(L,2,2);
    //    lua_rotate(L,2,-1);

    //    lua_remove(L,1);
    //    lua_remove(L,100);
    //    lua_insert(L,2);

    //    lua_settop(L,-1);
    //    lua_insert(L,-1);
    //    lua_replace(L,-1);
    //    lua_rotate(L,1,0);

    printluastack(L);
    cout << lua_gettop(L);



    lua_close(L);
    return 0;
}



int main02()
{
//    char str1[] = "abc";
//    char str2[] = "abc";
//    const char str3[] = "abc";
//    const char str4[] = "abc";
//    const char* str5 = "abc";
//    const char* str6 = "abc";
//    cout << boolalpha << ( str1==str2 ) << endl; // 输出什么？
//    cout << boolalpha << ( str3==str4 ) << endl; // 输出什么？
//    cout << boolalpha << ( str5==str6 ) << endl; // 输出什么？
//    cout << &str1 <<endl;
//    cout << &str2 <<endl;
//    cout << &str3 <<endl;
//    cout << &str4 <<endl;
//    cout << &str5 <<endl;
//    cout << &str6 <<endl;

//    cout << (true?"b":"1") << endl;

//    unsigned int const size1 = 2;
//    char str1[ size1 ];
//    unsigned int temp = 0;
//    cin >> temp;
//    unsigned int const size2 = temp;
//    char str2[ size2 ];
//    cout << sizeof(str2) << endl;

//    vector<int> array;
//    array.push_back( 1 );
//    array.push_back( 2 );
//    array.push_back( 3 );
//    for( vector<int>::value_type i=array.size()-1; i>=0; --i ) // 反向遍历array数组
//    {
//    cout << array[i] << endl;
//    }

    float a = 1.0f;
    cout << (int)a << endl;
    cout << (int&)a << endl;
    cout << boolalpha << ( (int)a == (int&)a ) << endl; // 输出什么？
    float b = 0.0f;
    cout << (int)b << endl;
    cout << (int&)b << endl;
    cout << boolalpha << ( (int)b == (int&)b ) << endl; // 输出什么？
}

void selectsort(vector<int> &v)
{
    int i=0;int j = 0;
    int size = v.size();
    if(size == 0)
    {
        return;
    }
    int k = 0;
    for(i = 0;i < size-1;++i)
    {
        k = i;
        for(j = k+1;j < size;++j)
        {
            if(v[k] > v[j])
            {
                k = j;
            }
        }
        if(k != i)
        {
            v[i] ^= v[k];
            v[k] ^= v[i];
            v[i] ^= v[k];
        }
    }

}
void writefile(const char* str,vector<int> &v)
{
    FILE *fp = fopen(str,"w");
    if (fp == NULL)
    {
        printf("fopen fail\n");
    }
    char ch;
    for(int i = 0;i < v.size();++i)
    {
        ch = v[i] + '0';
        printf("%c\n",ch);
        fputc(ch,fp);
    }
    fclose(fp);
}
void readfile(const char*str,vector<int> &v)
{
    FILE *fp = fopen("aa.txt","r");
    if (fp == NULL)
    {
        printf("fopen fail\n");
    }
    char ch;
    int d;
    while ((ch = fgetc(fp)) != EOF)
    {
        d = ch - '0';
        v.push_back(d);
    }
    fclose(fp);
}
void processfile(const char* str)
{
    vector<int> vi;
    readfile(str,vi);
    selectsort(vi);
    writefile("bb.txt",vi);
}
int main()
{
    processfile("aa.txt");


//    for(int i = 0;i < vi.size();++i)
//    {
//        cout << vi[i] << " ";
//    }


}

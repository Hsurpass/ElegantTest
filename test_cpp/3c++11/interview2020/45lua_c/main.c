#include <stdio.h>
#include"lua.h"
#include "lualib.h"
#include "lauxlib.h"

int foo(lua_State* L)
{
    printf("hi,lua\n");
}

int func_return_table(lua_State* L)
{
    lua_newtable(L);

    lua_pushstring(L,"key");
    lua_pushinteger(L,33);
    lua_settable(L,-3);

    lua_pushstring(L,"foo");
    lua_pushcfunction(L,foo);
    lua_settable(L,-3);

    return 1;
}

int main()
{
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    lua_pushcfunction(L,&func_return_table);
    lua_setglobal(L,"func_return_table");

    luaL_dofile(L,"yy.lua");
    lua_close(L);
    return 0;
}

//void func()
//{
//    printf("hello world\n");
//}
//int func(lua_State* L)
//{
//    printf("hello lua\n");
//    return 0;
//}
//int func(lua_State* L)
//{
//    char *str = lua_tostring(L,-1);
//    int num = lua_tointeger(L,-2);
//    printf("%s,%d\n",str,num);

//    printf("hello lua\n");
//    return 0;
//}
int add(lua_State* L)
{
    int sum=0;
    int avg = 0;
    printf("stack size:%d\n",lua_gettop(L));
    int n = lua_gettop(L);
    for(int i = 1;i <= n;++i)
    {
        sum += lua_tointeger(L,i);
    }

    lua_pushinteger(L,sum);
    lua_pushinteger(L,sum/n);

//    printf("%d,%d\n",sum,avg);

    return 2;
}

int main03()
{
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

//    lua_pushcfunction(L,func);
//    printf("stack size:%d\n",lua_gettop(L));
//    lua_setglobal(L,"func");
//    printf("stack size:%d\n",lua_gettop(L));

    lua_pushcfunction(L,&add);
    printf("stack size:%d\n",lua_gettop(L));
    lua_setglobal(L,"add");
    printf("stack size:%d\n",lua_gettop(L));


    luaL_dofile(L,"yy.lua");
    lua_close(L);
    return 0;
}

int main02()
{
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    lua_newtable(L);//创建一个表，并入栈，
    lua_pushstring(L,"age");
    lua_pushinteger(L,18);
    printf("stack size:%d\n",lua_gettop(L));
    lua_settable(L,-3);
    printf("stack size:%d\n",lua_gettop(L));

    lua_pushstring(L,"name");
    lua_pushstring(L,"peter");
    lua_settable(L,-3);

    lua_pushstring(L,"jam");
    lua_setfield(L,-2,"name");

    lua_setglobal(L,"tab");
    printf("stack size:%d\n",lua_gettop(L));


    luaL_dofile(L,"yy.lua");
    printf("stack size:%d\n",lua_gettop(L));
    return 0;
}

int main01()
{
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

//    lua_pushstring(L,"jim");
    lua_pushnumber(L,18);
//    lua_pushstring(L,"jim");
    printf("stack size:%d\n",lua_gettop(L));
    lua_setglobal(L,"age");
    printf("stack size:%d\n",lua_gettop(L));

    const char *teacher = "wgl";
    lua_pushstring(L,teacher);
//    lua_pushstring(L,"jim");
    printf("stack size:%d\n",lua_gettop(L));
    lua_setglobal(L,"name");
    printf("stack size:%d\n",lua_gettop(L));

    luaL_dofile(L,"yy.lua");
    printf("stack size:%d\n",lua_gettop(L));
    lua_close(L);
    return 0;
}

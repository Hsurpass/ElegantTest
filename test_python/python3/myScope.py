#!/usr/bin/python3

num = 1
def fun1():
    global num  # 修改全局变量需要使用 global 关键字声明
    print(num)  #1
    num = 123
    print(num)  #123

fun1()
print(num)  #123


def outer():
    num = 10
    def inner():
        #如果只访问不修改可以不用nonlocal
        # print(num)  #100
        nonlocal num   # 修改嵌套作用域中的变量需要nonlocal关键字声明
        num = 100
        print(num)  #100
    inner()
    print(num)

outer()


a = 10
def test():
    # a = a + 1   #UnboundLocalError: local variable 'a' referenced before assignment
    global a
    a = a + 1
    print(a)    #11
test()
print(a)    #11

int = 0
def fun1():
    int = 1
    def fun2():
        int = 2
        print(int)
    fun2()
fun1()  # 输出 2

int = 0
def fun1():
    int = 1
    def fun2():
        print(int)
    fun2()
fun1()  # 输出 1

int = 0
def fun1():
    def fun2():
        print(int)
    fun2()
fun1() # 输出 0

def fun1():
    def fun2():
        print(float)
    fun2()
fun1() # 输出 0
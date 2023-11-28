#!/usr/bin/python3

'''
在Python中，当一个函数返回一个闭包时，并不会在返回时拷贝外层函数内的变量。相反，闭包会保留对外层函数作用域的引用，以便在以后的调用中访问和修改这些变量。
当一个函数返回一个闭包时，闭包会捕获外层函数的环境，包括外层函数的局部变量、参数和自由变量。这意味着闭包可以访问外层函数的变量，并且在闭包中对这些变量进行修改时，会影响外层函数的状态。
也就是说：
在Python中，当一个函数返回一个闭包时，外层函数的作用域并不会立即被销毁。相反，Python会在需要时保留外层函数的作用域，以便闭包可以继续访问外层函数的变量。
这种行为使得闭包可以在以后的调用中继续访问和修改外层函数的变量，即使外层函数已经执行完毕。这也是闭包能够实现延迟绑定和保留状态的原因之一。

需要注意的是，如果闭包持有外层函数中大量的变量或者数据，这可能会导致内存占用过高。因此，在使用闭包时，需要注意对内存的合理管理，以避免出现不必要的内存占用。
'''

def lazy_sum(*args):
    def _sum():
        sum = 0
        for x in args:
            sum += x
        return sum
    return _sum

f = lazy_sum(1,2,3,4,5)
print(f())  #15
f1 = lazy_sum(1,2,3,4)
print(f1()) #15

def lazy_sum_nonlocal(*args):
    sum = 0
    def _sum():
        nonlocal sum  #如果修改外层函数的变量需要加nonlocal关键字
        for x in args:
            sum += x
        return sum
    return _sum

f = lazy_sum_nonlocal(1,2,3,4,5)
print(f())  #15

def count():
    fs = []
    for i in range(1, 4):   
        def f():  # 在for循环中的函数并不会执行
            return i * i
        fs.append(f)    #这里只是把f先添加到列表中（没有调用），还没进行i*i运算，最后f取得值是i=3
    return fs   #闭包引用外层函数的作用域(暂时不会释放)，i是在变的，所以取得i的值都是3

# print(count())
f1, f2, f3 = count()
print(f1())     #9  #所引用的栈中变量值都相同
print(f2())     #9
print(f3())     #9

#三层嵌套
def count():
    def f(i):   #向f传参涉及到拷贝
        def g():#闭包取得的值是i
            return i * i
        return g    #每个闭包引用一个外层函数的栈（不同的栈因为在append时调用了f），所以最后计算的值不一样。
    fs = []
    for i in range(1,4):
        fs.append(f(i)) # 在append时调用了f，每个闭包引用一个不同的栈。
    return fs

f1, f2, f3 = count()
print(f1()) #1
print(f2()) #4
print(f3()) #9


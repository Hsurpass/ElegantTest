#!/usr/bin/python3

def test_return_type(a, b):
    return a, b

#一般来说，函数的返回值一般为一个。
#而函数返回多个值的时候，是以元组的方式返回的
print(type(test_return_type(3, 4))) #<class 'tuple'>
#函数的参数为多个时，不一定是以元组的形式返回的，还是要看自己定义的返回形式是什么
def test_return_type(a, b):
    return [a, b]
print(type(test_return_type(3, 4))) #<class 'tuple'>

#加了星号 * 的参数会以元组(tuple)的形式导入，存放所有未命名的变量参数。
def test_variable_length_arg(*args):
    print(args) 
    print(type(args))   #<class 'tuple'>
    return args
print(type(test_variable_length_arg(3, "aaa", 20.22, True))) #<class 'tuple'>

#加了两个星号 ** 的参数会以字典的形式导入。
def test_dict_arg(arg, **args):
    # print(arg)
    print(args)
    print("test_dict_arg type:", type(args))

test_dict_arg('a', a=1, b=2)

#如果单独出现星号 *，则星号 * 后的参数必须用关键字传入
def test_single_star(a, b, *, c):
    print(type(a))
    print(type(b))
    print(c, type(c))

test_single_star(10, [1,2], c="bb")


def func1(a):
    print(id(a))    #9784864
    a = 10
    print(id(a))    #9785152

a=1
print(id(a))    #9784864
func1(a)

def func2(l):
    print(l)
    l.append([10,20,30])

l = [1,2,3,4]
func2(l)
print(l)

x = lambda a: a+10
print(x(6)) #16

sum = lambda x,y: x + y 
print(sum(10, 5))   #15
print(sum(11, 12))  #23

def greetPerson(*name):
    print('Hello', name)
  
greetPerson('Runoob', 'Google')



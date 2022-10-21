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

def test_variable_length_arg(*args):
    print(args) 
    print(type(args))   #<class 'tuple'>
    return args

print(type(test_variable_length_arg(3, "aaa", 20.22, True))) #<class 'tuple'>


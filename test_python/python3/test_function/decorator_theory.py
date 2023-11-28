#!/usr/bin/python3

def func():
    print('func')
    v = (1,2,3)
    return v

def outer(f):
    print("outer")
    def inner():
        print("inner")
        print("before origin, f.__name__: ", f.__name__)
        r = f()
        print("after origin, f.__name__: ", f.__name__)
        return r
    return inner

print("func.__name__:", func.__name__)
func = outer(func)
print("func.__name__: ", func.__name__)
r = func()
print(r)

print("##########################")

@outer # func1 = outer(func1)   
def func1():
    print('func1')
    v = (1,2,3,4)
    return v

print("func1.__name__: ", func1.__name__)
print(func1())
print("func1.__name__: ", func1.__name__)

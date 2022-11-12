#!/usr/bin/python3

from functools import wraps

def log1(*text):
    def log2(func):
        # @wraps(func)
        def inner(*args, **kvargs):
            print("%s %s start" % (func.__name__ , text))
            rs = func(*args, **kvargs)
            print("%s %s end" % (func.__name__, text))
            return rs
        return inner
    return log2


def log(func):
    # @wraps(func)
    def inner(*args, **kvargs):
        print("%s start" % func.__name__)
        rs = func(*args, **kvargs)
        print("%s end" % func.__name__)
        return rs
    return inner

# @log
@log1('log1')
def f1(x):
    return "***f1***"

# @log
# @log1('log1, "-')
@log1()
def f2(x,y):
    return "***f2***"

print(f1.__name__)
print(f1(1))
print(f2.__name__)
print(f2(1,2))

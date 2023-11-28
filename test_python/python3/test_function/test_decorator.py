#!/usr/bin/python3

#https://www.bilibili.com/video/BV1Vv411x7hj/?p=1

from functools import wraps

def log1(*text):
    print("<%s> %s log1 start" % (log1.__name__ , text))
    
    def log2(func):
        print("<%s> %s log2 start" % (func.__name__ , text))
        # @wraps(func)
        
        def log2inner(*args, **kvargs):
            print("<%s> %s log2 inner start" % (func.__name__ , text))
            a="xxx"
            rs = func(*args, **kvargs)
            print("<%s> %s log2 inner end return rs" % (func.__name__, text))
            return rs
        
        print("<%s> %s log2 end return log2 inner" % (func.__name__ , text))
        return log2inner
    
    print("<%s> %s log1 end return log2" % (log1.__name__ , text))
    return log2


def log(func):
    print("<%s> log start" % func.__name__)
    # @wraps(func)  #等同于 inner.__name = func.__name__  inner.__doc__ = func.__doc__
    def loginner(*args, **kvargs):
        print("<%s> log inner start" % func.__name__)
        rs = func(*args, **kvargs)
        print("<{0}> log inner end return rs".format(func.__name__))    
        return rs
    
    print("<%s> log end return log inner" % func.__name__)
    return loginner

# https://www.cnblogs.com/ludingchao/p/11851812.html
#叠加装饰器
#   装饰的顺序：由下到上
#   执行的顺序：由上往下

@log                    # loginner = log(log2inner)   再用log装饰
@log1('log1', 'log1xx') # log2inner = log2(f1) 先用log2装饰
def f1(x):              # log2 = log1('log1', 'log1xx') 返回log2
    print("f1(x)")      # 装饰顺序：从下到上
    str = "***f1***{0}".format(x)
    return str

print("##########################")
print(f1.__name__)      # loginner 
print(f1(1))    # 执行的时候从上往下
                # <log2inner> log inner start
                # <f1> ('log1', 'log1xx') log2 inner start
                # f1(x)
                # <f1> ('log1', 'log1xx') log2 inner end return rs
                # <log2inner> log inner end return rs
                # ***f1***1



#!/usr/bin/python3



def lazy_sum(*args):
    def _sum():
        sum = 0
        for x in args:
            sum += x
        return sum
    return _sum

# def lazy_sum(*args):
#     sum = 0
#     def _sum():
#         nonlocal sum
#         for x in args:
#             sum += x
#         return sum
#     return _sum

f = lazy_sum(1,2,3,4,5)
print(f())

def count():
    fs = []
    for i in range(1, 4):
        def f():
            return i * i
        fs.append(f)
    return fs

f1, f2, f3 = count()
print(f1())     #9
print(f2())     #9
print(f3())     #9

def count():
    def f(i):
        def g():
            return i * i
        return g
    fs = []
    for i in range(1,4):
        fs.append(f(i))
    return fs

f1, f2, f3 = count()
print(f1())
print(f2())
print(f3())


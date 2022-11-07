#!/usr/bin/python3


from functools import reduce

def f(x):
    return x * x
r = map(f, [1,2,3,4,5,6,7,8,9])
print(r)
print(list(r))

r = list(map(str, [1,2,3,4,5,6,7,8,9]))
print(r)

print("########################")

def add(x, y):
    return (x + y)
 
r = reduce(add, [1, 3, 5, 7, 9])
print(r)

def fn(x, y):
    return x * 10 + y
r = reduce(fn, [1,3,5])
print(r)

print("########################")
def is_odd(n):
    return n % 2 == 1
r = filter(is_odd, [1,2,3,4,5,6,7,8,9])
print(r)
print(list(r))

def not_empty(s):
    return s and s.strip()
r = filter(not_empty, ['A', "", 'B', None, 'C', ' '])
print(list(r))

print('@@@@@@@@@@@@@@@@@@@@@@@@')
print(sorted([1,-1,9,5,-2,8]))
#按照绝对值大小来排序
r = sorted([1,-1,9,5,-2,8], key=abs)
print(r)
#忽略大小写排序
r = sorted(['bob', 'about', 'Zoo', 'Credit'], key=str.lower)
print(r)
#忽略大小写反向排序
r = sorted(['bob', 'about', 'Zoo', 'Credit'], key=str.lower, reverse=True)
print(r)

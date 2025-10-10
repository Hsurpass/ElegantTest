#!/usr/bin/python3

import sys
from collections.abc import Iterable

list = [1, 2, 3, 4]
# it = iter(list) # == list.__iter__()
it = list.__iter__()
# print(next(it)) # 1 == it.__next__()
print(it.__next__()) # 1
print(next(it)) # 2
print(next(it)) # 3
print(next(it)) # 4
# print(next(it)) #StopIteration


it = iter(list)
for x in it:
    print(x, end=" ")
print()

it = iter(list)
while True:
    try:
        print(next(it), end=" ")
    except StopIteration: #直到捕获这个异常才退出循环
        # sys.exit()
        break
print()

for x in list:
    print(x, end=" ")
print()

print("len(list):", len(list))
for i in range(len(list)):
    print(list[i], end=" ")
print()

print("判断一个对象是否是可迭代对象")

my_str = "hello"
my_list = [1, 2, 3, 4]
my_int = 1
print(hasattr(my_str, '__iter__'))  # True
print(hasattr(my_list, '__iter__')) # True
print(hasattr(my_int, '__iter__'))  # False

#str是否可迭代
print(isinstance('abc', Iterable))     #True
#list是否可迭代
print(isinstance([1,2,3], Iterable))    #True
#整数是否可迭代
print(isinstance(123, Iterable))    #False
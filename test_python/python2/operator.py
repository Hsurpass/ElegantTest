#! /usr/bin/python2
# coding=utf-8

from xml.dom.minidom import Element


a=10
b=2
list = [1,2,3,4,5]

if (a in list):
    print "a in list";
else:
    print "a not in list"

if (b not in list):
    print "b not in list";
else:
    print "b in list"

if(a is b):
    print("&a == &b", id(a), id(b))
else:
    print("&a != &b", id(a), id(b))

b = 10
if(a is not b):
    print("&a != &b", id(a), id(b))
else:
    print("&a == &b", id(a), id(b))

list1 = list
print(list is list1, id(a), id(b))    # True
print(list == list1, id(a), id(b))    # True
list1 = list[:]
# list1 = list[]    # invalid syntax
print(list is list1, id(a), id(b))    # False
print(list == list1, id(a), id(b))    # True

print("$$$$$$$$$$$$$$$$$$$$$$$$$$$$")
#Python出于对性能的考虑，但凡是不可变对象，在同一个代码块中的对象，
# 只有是值相同的对象，就不会重复创建，而是直接引用已经存在的对象。
c = 10000000000000000000000000000000000000000
d = 10000000000000000000000000000000000000000
print("1.", c is d, id(c), id(d))       #True
print("1.", c is not d, id(c), id(d))   #False


# Python 中会实现创建一个小型的整型池，范围为 [-5,256]，
# 为这些整形开辟好内存空间，当代码中定义该范围内的整形时，不会再重新分配内存地址。

# 正整数最大到256
c = 2 ** 8
d = 2 ** 8
print("2.", c is d, id(c), id(d))       #True
print("2.", c is not d, id(c), id(d))   #False

c = 2 ** 8 + 1
d = 2 ** 8 + 1
print("7.", c is d, id(c), id(d))       #False
print("7.", c is not d, id(c), id(d))   #True

c = 2 ** 9
d = 2 ** 9
print("8.", c is d, id(c), id(d))       #False
print("8.", c is not d, id(c), id(d))   #True

# 小数的地址永不相等
c = 2 ** 8 - 0.1
d = 2 ** 8 - 0.1
print("3.", c is d, id(c), id(d))       #False
print("3.", c is not d, id(c), id(d))   #True

c = 2 ** 8 - 0.5
d = 2 ** 8 - 0.5
print("4.", c is d, id(c), id(d))       #False
print("4.", c is not d, id(c), id(d))   #True

c = 2 ** 8 + 0.0
d = 2 ** 8 + 0.0
print("5.", c is d, id(c), id(d))       #False
print("5.", c is not d, id(c), id(d))   #True

c = 2 ** 8 + 0.1
d = 2 ** 8 + 0.1
print("6.", c is d, id(c), id(d))       #False
print("6.", c is not d, id(c), id(d))   #True

print("####################")
#不可变对象引用同一个地址
e = 2000000000000000000000000000000000000000.0
f = 2000000000000000000000000000000000000000.0 
print("1.", e is f, id(e), id(f))       #True
print("1.", e is not f, id(e), id(f))   #False

e = -2000000000000000000000000000000000000000.0
f = -2000000000000000000000000000000000000000.0 
print("2.", e is f, id(e), id(f))       #True
print("2.", e is not f, id(e), id(f))   #False

# 小数的地址永不相等
e = 1.0 ** 1; f = 1.0 ** 1
print("3.", e is f, id(e), id(f))       #False
print("3.", e is not f, id(e), id(f))   #True

e = 2.0 ** 1; f = 2.0 ** 1
print("4.", e is f, id(e), id(f))       #False
print("4.", e is not f, id(e), id(f))   #True

e = -1.0 ** 1; f = -1.0 ** 1
print("5.", e is f, id(e), id(f))       #False
print("5.", e is not f, id(e), id(f))   #True

print("&&&&&&&&&&&&&&&&&&&&&&&&&&&")
# 负整数最小到-5
e = -2 ** 2
f = -2 ** 2
print("1.", e is f, id(e), id(f))       #True

e=-2 ** 2 -1
f=-2 ** 2 -1
print("2.", e is f, id(e), id(f))       #True

e=-2 ** 2 -2
f=-2 ** 2 -2
print("3.", e is f, id(e), id(f))       #False

e=-2 ** 3
f=-2 ** 3
print("4.", e is f, id(e), id(f))       #False

# 小数的地址永不相等
e=-2 ** 2 -1.0
f=-2 ** 2 -1.0
print("5.", e is f, id(e), id(f))       #False

e=-2 ** 2 -1.1
f=-2 ** 2 -1.1
print("6.", e is f, id(e), id(f))       #False

e=-2 ** 2 -1.1
f=-2 ** 2 -1.1
print("7.", e is f, id(e), id(f))       #False

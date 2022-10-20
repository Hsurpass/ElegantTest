#! /usr/bin/python2
# coding=utf-8

from cgi import print_directory
from pickle import TRUE


a = 29
a1 = 1000000000000000000000000000000
b = 5.5
c = True
d = 4+3j
e = "abc"
f = []
g = ()
h = {}

print("type(a):", type(a))      #('type(a):', <type 'int'>)
print("type(a1):", type(a1))    #('type(a1):', <type 'long'>)
print("type(b):", type(b))      #('type(b):', <type 'float'>)
print("type(c):", type(c))      #('type(c):', <type 'bool'>)
print("type(d):", type(d))      #('type(d):', <type 'complex'>)
print("type(e):", type(e))      #('type(e):', <type 'str'>)
print("type(f):", type(f))      #('type(f):', <type 'list'>)
print("type(g):", type(g))      #('type(g):', <type 'tuple'>)
print("type(h):", type(h))      #('type(h):', <type 'dict'>)

print("#######################")
print(isinstance(a, int))       #True
print(isinstance(a1, int))      #False
print(isinstance(a1, long))     #True
print(isinstance(b, float))     #True
print(isinstance(c, bool))      #True
print(isinstance(d, complex))   #True
print(isinstance(e, str))       #True
print(isinstance(f, list))      #True
print(isinstance(g, tuple))     #True
print(isinstance(h, dict))      #True

print("$$$$$$$$$$$$$$$$$$$$$$$")
print(issubclass(bool, int))   #True
print(True == 1)    #True
print(False == 0)   #True

print(1 is True)    #False
print(True is 1)    #False
print(0 is False)   #False
print(False is 0)   #False

print(True + 1)     #2
print(False + 1)    #1

print("--------------------------")
class A:
    pass
class B(A):
    pass

print(type(A))
print(type(B))
print(type(A()))
print(type(B()))

print(type(A()) == A) #False
print(type(B()) == A) #False

print(isinstance(A(), A))   #True
print(isinstance(B(), A))   #True


a = 1
print(a)
del a
print(a)



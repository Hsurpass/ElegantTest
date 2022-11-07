#!/usr/bin/python3

from cgi import print_environ
from collections.abc import Iterable

# print_environ()

#str是否可迭代
print(isinstance('abc', Iterable))     #True
#list是否可迭代
print(isinstance([1,2,3], Iterable))    #True
#整数是否可迭代
print(isinstance(123, Iterable))    #False



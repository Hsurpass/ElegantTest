#!/usr/bin/python2
# coding=utf-8

# from jwt import decode


print("hello, python2!")
print("你好，python2!")

s = "你好，python2!"
print(type(s))
print(s)

s1 = s.decode('utf-8')
print(type(s1))
print(s1)

s2 = s1.encode("GBK")
print(type(s2))
print(s2)

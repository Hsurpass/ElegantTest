#!/usr/bin/python2
#coding=utf-8

sites = {'Google', 'Taobao', 'Runoob', 'Baidu', 'Facebook', 'Zhihu', 'Baidu'}
print(sites)    #set(['Baidu', 'Google', 'Runoob', 'Facebook', 'Taobao', 'Zhihu'])
print(type(sites))  #<class 'set'>

if 'Runoob' in sites :
    print('Runoob in sites')
else :
    print('Runoob not in sites')

#类似于std::unordered_set 元素不重复且无序
print(set())    #set([])
a = set('abracadabra')
b = set('alacazam')
print(type(a), type(b)) #<class 'set'> <class 'set'>

print(a)    # a b r c d     #set(['a', 'r', 'b', 'c', 'd'])
print(b)    # a l c z m     #set(['a', 'c', 'z', 'm', 'l'])

print(a - b)    # a相对于b的差集 b r d  #set(['r', 'b', 'd'])
print(b - a)    # b相对于a的差集 l z m  #set(['z', 'm', 'l'])
print(a | b)    # a与b的并集 a b c d l r z m    #set(['a', 'c', 'b', 'd', 'm', 'l', 'r', 'z'])
print(a & b)    # a与b的交集 a c    #set(['a', 'c'])
print(a ^ b)    # a与b中不同时存在的元素 b d l r z m    #set(['b', 'd', 'm', 'l', 'r', 'z'])
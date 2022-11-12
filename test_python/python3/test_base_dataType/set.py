#!/usr/bin/python3

from inspect import cleandoc
import site
import this


sites = {'Google', 'Taobao', 'Runoob', 'Facebook', 'Baidu', 'Zhihu', 'Baidu'}
print(sites)    #{'Taobao', 'Runoob', 'Zhihu', 'Facebook', 'Baidu', 'Google'}
print(type(sites))  #<class 'set'>

if 'Runoob' in sites :
    print('Runoob in sites')
else :
    print('Runoob not in sites')

#类似于std::unordered_set 元素不重复且无序
print(set())    #set()
a = set('abracadabra')
b = set('alacazam')
print(type(a), type(b)) #<class 'set'> <class 'set'>
print(a)    # a b r c d     #{'c', 'd', 'b', 'r', 'a'}
print(b)    # a l c z m     #{'c', 'm', 'l', 'z', 'a'}

print(a - b)    # a相对于b的差集 b r d  #{'b', 'r', 'd'}
print(b - a)    # b相对于a的差集 l z m  #{'m', 'l', 'z'}
print(a | b)    # a与b的并集 a b c d l r z m  #{'z', 'c', 'd', 'b', 'l', 'r', 'm', 'a'}
print(a & b)    # a与b的交集 a c    #{'c', 'a'}
print(a ^ b)    # a与b中不同时存在的元素 b d l r z m    #{'d', 'm', 'l', 'r', 'b', 'z'}

print('###########################')
thisset = set(("Google", "Runoob", "Taobao"))
thisset.add("baidu")
print(thisset)  #{'Runoob', 'Taobao', 'baidu', 'Google'}
# thisset.add({"xinlang"})    #TypeError: unhashable type: 'set'
# thisset.update("xinlang")   #{'Taobao', 'l', 'i', 'n', 'a', 'x', 'baidu', 'Google', 'g', 'Runoob'}
thisset.update({"xinlang"})   #{'Runoob', 'Taobao', 'Google', 'baidu', 'xinlang'}
print(thisset)

# thisset.remove("a") #将元素 x 从集合 s 中移除，如果元素不存在，则会发生错误。
thisset.discard("a")
print(thisset)
print(thisset.pop())    #随机删除，每次删的不一样
print(thisset)
print(len(thisset)) # 4
# thisset.clear()
# print(len(thisset)) # 0
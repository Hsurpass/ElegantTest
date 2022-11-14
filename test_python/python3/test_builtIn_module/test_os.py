#! /usr/bin/python3

from genericpath import isdir
import os

print(os.name)
print(os.uname())

# print(os.environ)
# print(os.environ.get('PATH'))

print(os.path.abspath('.'))
p = os.path.join('.', 'test_moudle')
print(p)    #"./test_module"

print(os.path.split(p)) #'.' 'test_module'
p = os.path.join('.', "a.txt")
print(os.path.splitext(p))  # './a' .txt'

# os.mkdir(p)
# 删掉一个目录:
# os.rmdir(p)

#列出当前目录下的所有文件夹
print([x for x in os.listdir('.') if os.path.isdir(x)])
#列出当前目录下的所有文件
print([x for x in os.listdir('.') if os.path.isfile(x)])

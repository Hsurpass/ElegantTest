#! /usr/bin/python3

from datetime import datetime

str = '123456789'
print(str)          #123456789
print (str[2])    #3
# 左闭右开区间
print(str[0:-1])    #12345678
print(str[0:])      #123456789
print(str[2:5])     #345
print(str[2:])      #3456789
print(str * 2)      #123456789123456789
print(str + "你好")  #123456789你好
print(str[-9:-1])   #12345678
print(str[-9:])   #12345678
print(str[-3:])   #789

#Python 列表截取可以接收第三个参数，参数作用是截取的步长
print(str[1:5:2])   #24

print('----------------')
print('hello\npython2') # 使用反斜杠(\)+n转义特殊字符
print(r"hello\nrawpython2") # 在字符串前面添加一个 r，表示原始字符串，不会发生转义

# str[0] = 'm' #python中的字符串不可改变

print("hello, %s, 今年%d岁" %("小明", 10))

#python3.6
name = "xiaoming"
print(f'hello, {name}')
print(f'{1+2}')
w = {'name': 'Runoob', 'url': 'www.runoob.com'}
print(f'{w["name"]}:{w["url"]}')

#python3.8
x = 1
print(f'{x+1}')
print(f'{x+2=}')


now = datetime.now()
print(type(now))
print(now)
# print(str(now))
print(repr(now))


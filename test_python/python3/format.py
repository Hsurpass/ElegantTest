#!/usr/bin/python3

import math

if True:
    print ("Answer")
    print ("True")
else:
    print ("Answer")
#  print ("False")    # 缩进不一致，会导致运行错误

num = 10
print("八进制: %o" %num)        #八进制: 12
print("十六进制: %x" %num)      #十六进制: a
print('二进制: ', bin(num) )    #二进制:  0b1010
print("八进制: %#o" %num)       #八进制: 0o12
print("十六进制: %#x" %num)     #十六进制: 0xa

print('{0} and {1}' .format('google', "baidu"))
print('{1} and {0}' .format('google', "baidu"))
print('{name}网址, {site}' .format(name='百度', site='www.baidu.com'))
#位置及关键字参数可以任意的结合:
print('站点列表 {0}, {1}, 和 {other}。'.format('Google', 'Runoob', other='Taobao'))

print('常量 PI 的值近似为： {}。'.format(math.pi))  #3.141592653589793
print('常量 PI 的值近似为： {!a}。'.format(math.pi))#3.141592653589793
print('常量 PI 的值近似为： {!s}。'.format(math.pi))#3.141592653589793
print('常量 PI 的值近似为： {!r}。'.format(math.pi))#3.141592653589793
#可选项 : 和格式标识符可以跟着字段名。 这就允许对值进行更好的格式化。 
# 下面的例子将 Pi 保留到小数点后三位：
print('常量 PI 的值近似为： {0:.3f}。'.format(math.pi))#3.142
print('常量 PI 的值近似为： {0:.3}。'.format(math.pi))#3.14
print('常量 PI 的值近似为： %6.4f。' % math.pi)#3.1416

#在 : 后传入一个整数, 可以保证该域至少有这么多的宽度。 用于美化表格时很有用。
table = {'Google': 1, 'Runoob': 2, 'Taobao': 3}
for name, number in table.items():
    print('{0:10} ==> {1:10d}' .format(name, number))

#传入一个字典, 然后使用方括号 [] 来访问键值
# print('Runoob: {0[Runoob]:d}; Google: {0[Google]:d}; Taobao: {0[Taobao]:d}'.format(table))
# print('Runoob: {0[Runoob]}; Google: {0[Google]}; Taobao: {0[Taobao]}'.format(table))
#也可以通过在 table 变量前使用 ** 来实现相同的功能
# print('Runoob: {Runoob:d}; Google: {Google:d}; Taobao: {Taobao:d}' .format(**table))
print('Runoob: {Runoob}; Google: {Google}; Taobao: {Taobao}'.format(**table))



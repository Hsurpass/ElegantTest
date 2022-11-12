#!/usr/bin/python3

import math

print(math.ceil(4.1))   # 5
print(math.floor(4.9))  # 4
print(round(4.1))  # 4
print(round(4.9))  # 5

print(math.ceil(-4.1))   # -4
print(math.floor(-4.9))  # -5
print(round(-4.1))  # -4
print(round(-4.9))  # -5

#数学常量 pi（圆周率，一般以π来表示）
print(math.pi)
#数学常量 e，e即自然常数（自然常数）
print(math.e)
print(math.fabs(-10))   #-10

print("---------------内置函数：-------------------")
# [1,5) 从1到4,不包含5
for i in range(1,5): print(i, end=" ")   #[1,2,3,4]
print()
# [0,5)
for i in range(5): print(i, end=" ") #[0,1,2,3,4]
print()
# [1,5) 从1到4，间隔为2，所以输出是[1, 3]
for i in range(1, 5, 2): print(i, end=" ") #[1,3]
print()

#数字转换成ascii
print(chr(97))  #'a'
print(chr(65))  #'A'
#ascii转换成数字
print(ord("a")) #97
print(ord('b')) #98
print(ord('A')) #65

print(abs(-10))

#将整数转化为二进制字符串
print(bin(12))  #0b1100
print(bin(12).replace("0b", ""))    #1100
print("{0:b}".format(12))   #1100

print("^^^^^^^^^^^^^^^^^内置函数^^^^^^^^^^^^^^^^^^^")


print('---------------------------------')
import random

# 从0到9中随机挑选一个整数
print(random.choice(range(10)))
#从指定范围内，按指定基数递增的集合中获取一个随机数，基数默认值为1
print(random.randrange(0, 10, 8))
#随机生成一个实数，它在[0,1)范围内。
print(random.random())
#随机生成一个实数，它在[x,y]范围内。
print(random.uniform(10,10))




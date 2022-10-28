#! /usr/bin/python2
# coding=utf-8

a = 2 / 4
print(a)    #0

a = 2.0 / 4 # / 得到整数
print(a)    #0.5

a = 2.0 // 4    # // 得到整数部分
print(a)    #0.0

##python2里整数除整数只能得到整数
print(9 / 2)    # 4
print(9 // 2)   # 4
print(9.0 / 2)  # 4.5
print(9.0 // 2) # 4.0
print(-9 / 2)    # -5 (向下取整)
print(-9 // 2)   # -5 (向下取整)
print(-9.0 / 2)  # -4.5
print(-9.0 // 2) # -5.0(向下取整)
print(float(9) / 2)    # 4.5
print(float(9) // 2)   # 4.0
print(float(-9) / 2)    # -4.5
print(float(-9) // 2)   # -5.0

b = 17%3
print(b)

print(2 * 5)
print(2 ** 5)   #2的5次方

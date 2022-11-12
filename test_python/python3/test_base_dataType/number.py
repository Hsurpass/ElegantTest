#!/usr/bin/python3

a = 2 / 4
print(a)    #0.5

a = 2.0 / 4 # / 得到整数
print(a)    #0.5

a = 2.0 // 4    # // 得到整数部分
print(a)    #0.0

print("######################")
##python2里整数除整数只能得到整数, python3得到小数
print(9 / 2)    # 4.5
print(9 // 2)   # 4
print(9.0 / 2)  # 4.5
print(9.0 // 2) # 4.0
print(-9 / 2)    # -4.5 (向下取整)
print(-9 // 2)   # -5 (向下取整)
print(-9.0 / 2)  # -4.5
print(-9.0 // 2) # -5.0(向下取整)
print(float(9) / 2)    # 4.5
print(float(9) // 2)   # 4.0
print(float(-9) / 2)    # -4.5
print(float(-9) // 2)   # -5.0
print("$$$$$$$$$$$$$$$$$$$$$$")

b = 17%3
print(b)    # 2

print(2 * 5)    #10
print(2 ** 5)   #32 2的5次方

# a = 0
# a = 0.0
# a = 0L
# a = 0 + 0j
# a = 0.0 + 0.0j
# a = ''
# a = ""
# a = ''''''
# a = ()
# a = []
# a = {}
# a = None
# a = False
# a = set()   # False
# a = dict()  # False
# a = tuple() # False  
if a:
    print("a is True", type(a))
else:
    print("a is false", type(a))

for i in range(0, 10):
    print(i, end=" ")

print()

for i in range(0, 10):
    for j in range(0, 10):
        print('[{0}, {1}]'.format(i, j), end=" ")
    print()
print()
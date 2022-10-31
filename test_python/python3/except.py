#!/usr/bin/python3

import sys

try:
    f = open('myfile.txt')
    s = f.readline()
    i = int(s.strip())
except OSError as err:
    print("OS error: {0}".format(err))
except ValueError:
    print("Could not convert data to an integer.")
except:
    print("Unexpected error:", sys.exc_info()[0])
    raise
else:
    print("else")
finally:
    print('这句话，无论异常是否发生都会执行。')

print("----------------------------------")
#当在try块中抛出一个异常，立即执行finally块代码。
#finally块中的所有语句执行后，异常被再次触发，并执行except块代码。
try:
    fh = open("testfile", "r")
    try:
        fh.write("这是一个测试文件，用于测试异常!!")
    # except:
    #     print("write failed")
    finally:
        print("关闭文件")
        fh.close()
except IOError:
    print("Error: 没有找到文件或读取文件失败")

# x=int(input())
# if x > 5:
#     raise Exception('x 不能大于 5。x 的值为: {}'.format(x))

print("----------------------------------")
try:
    raise NameError('HiThere')
except NameError:
    print('An exception flew by!')
    # raise

print("----------------------------------")
#用户自定义异常
class MyError(Exception):
    def __init__(self, value):
        self.value = value
    def __str__(self):
        return repr(self.value)
try:
    raise MyError(10)
except MyError as e:
    print('My exception occurred, value:{0}'.format(e.value))



#!/usr/bin/python3

f = open("./testFile.txt", 'w+')
print(type(f))  #<class '_io.TextIOWrapper'>
print(f.tell()) #0

# value = ('www.runoob.com', 14)
# print(type(value))
# s = str(value)
# print(s)
# f.write(s)

re = f.write( "Python 是一个非常好的语言。\n是的，的确非常好!!\n" )
print(re)
x = f.tell()
print(x) #65

f.seek(0, 0)
print(f.tell()) #0

# s = f.read()
# s = f.readline()
s = f.readlines()
print(s)
print(f.readable())
print(f.tell())

f.close()
print(f.closed)
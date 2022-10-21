#!/usr/bin/python3

for i in range(1,5):   #左闭右开 
    print(i, end=" ")  
print()

x = ['A', 'B', 'C', 'D']
y = ['a', 'b', 'c', 'd']
for i, j in zip(x,y):
    print(i, j)

dic = {i:j for i, j in zip(x, y)}
print(dic)

dic = {x:x.strip() for x in ("he", "she", "I")}
print(dic)
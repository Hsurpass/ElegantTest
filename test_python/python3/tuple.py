#! /usr/bin/python3

tuple = ('hello', 786, 2.23, 'john', 70.2, [1, "abc", 22.11])
tinytuple = (123, 'world')

print(tuple)      #['hello', 786, 2.23, 'john', 70.2]
print(tuple[0])   #['hello']
print(tuple[1:3]) #[786, 2.23]
print(tuple[2:])  #[2.23, 'john', 70.2]
print(tinytuple * 2)  #[123, 'world', 123, 'world']
print(tuple + tinytuple)   #['hello', 786, 2.23, 'john', 70.2, 123, 'world']
print(tuple[0:-1]) #['hello', 786, 2.23, 'john']
print(tuple[2:-1]) #[2.23, 'john']
print(tuple[-1]) #[70.2]

print(tuple[:])
tuple[5][0] = 10    #tuple 中的list是可以改变的
print(tuple[:])
# tuple[1] = 789  #TypeError: 'tuple' object does not support item assignment
# print tuple

tup1 = ()
tup2 = (20)
print(tup1)
print(tup2)
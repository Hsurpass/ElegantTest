#! /usr/bin/python2
# coding=utf-8

from posix import listdir


list = ['hello', 786, 2.23, 'john', 70.2]
tinyList = [123, 'world']

print list      #['hello', 786, 2.23, 'john', 70.2]
print list[0]   #['hello']
print list[1:3] #[786, 2.23]
print list[2:]  #[2.23, 'john', 70.2]
print tinyList * 2;  #[123, 'world', 123, 'world']
print list + tinyList   #['hello', 786, 2.23, 'john', 70.2, 123, 'world']
print list[0:-1] #['hello', 786, 2.23, 'john']
print list[2:-1] #[2.23, 'john']
print list[-1] #[70.2]

list[1] = 789
print list

print list[:]
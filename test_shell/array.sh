#!/bin/bash

### 以空格分隔元素
array=(1, 2, 3, 4, 5)
echo ${array[0]}    #1,
echo ${array[1]}    #2,
echo ${array[@]}    #1, 2, 3, 4, 5 返回数组中的元素
echo ${array[*]}    #1, 2, 3, 4, 5 返回数组中的元素
echo ${#array[*]}   # 5 返回数组中元素的个数
echo ${#array[@]}   # 5 返回数组中元素的个数
echo ${#array[0]}   # 2 返回数组中第一个元素所占的字符数

echo "####################"
array=(1 2 3 4 5)
echo ${array[0]}    #1
echo ${array[1]}    #2
echo ${array[@]}    #1 2 3 4 5
echo ${array[*]}    #1 2 3 4 5
echo ${#array[*]}   # 5 返回数组中元素的个数
echo ${#array[@]}   # 5 返回数组中元素的个数
echo ${#array[0]}   # 1 返回数组中第一个元素所占的字符数

echo "########################"
array=("hello" "worl")
echo ${array[0]} # hello
echo ${array[1]} # worl

echo ${#array[0]} # 5 返回数组中第一个元素所占的字符数
echo ${#array[1]} # 4 返回数组中第一个元素所占的字符数

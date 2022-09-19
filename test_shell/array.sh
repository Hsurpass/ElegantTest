#!/bin/bash

### 以空格分隔元素
array=(1, 2, 3, 4, 5)
echo ${array[0]}    #1,
echo ${array[1]}    #2,
echo ${array[@]}    #1, 2, 3, 4, 5
echo ${array[*]}    #1, 2, 3, 4, 5
echo ${#array[*]}   # 5
echo ${#array[*]}   # 5
echo ${#array[0]}   # 2

echo "####################"
array=(1 2 3 4 5)
echo ${array[0]}    #1
echo ${array[1]}    #2
echo ${array[@]}    #1 2 3 4 5
echo ${array[*]}    #1 2 3 4 5
echo ${#array[*]}   # 5
echo ${#array[*]}   # 5
echo ${#array[0]}   # 1

#!/bin/bash

###########拼接字符串##########
name="wenong"
greeting="hello, "$name" !"
greeting_1="hello, ${name} !"
echo $greeting 
echo $greeting_1

###########字符串长度###########
str1="abcd"
echo ${#str1}   #4
str2=abcd
echo ${#str2}   #4

###########提取子字符串###########
str3="alibaba is a great company"
echo ${str3:1:4}    # liba
echo ${str3:2}      # ibaba is a great company

###########printf###############
printf "%d %s\n" 1 "abc"    # 1 abc
printf '%d %s\n' 1 "abc"    # 1 abc
printf %s abcddef   # abcddef
printf %s abc def   # abc def
printf "%s\n" abc def ghi   # abc 
                            # def
                            # ghi
printf "%s %s %s\n" a b c d e f g h i j
# a b c
# d e f
# g h i
#j
# 如果没有 arguments，那么 %s 用NULL代替，%d 用 0 代替
printf "%s and %d\n"    # and 0


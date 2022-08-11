#!/bin/bash

################################### 变量替换 ####################################
#var有值:
#   ${var:-word}、${var:=word}、${var:+word}:var有值的时候均不会被替换    
#   ${var:-word}、${var:=word}:var有值的时候均不会被替换,并返回var自身值
#   ${var:+word}:var有值的时候不会被替换，并返回word
#var无值:
#   ${var:­-word} 如果var为空或者已被删除(unset), 那么返回word, 但不改变var的值
#   ${var:=word} 如果var为空或者已被删除(unset)，那么返回word, 并将var的值设为word
#   ${var:+word} 如果var为空或者已被删除(unset)，那么返回为空, var的值还是为空


echo "***********\${var:-word}:******************"
# ${var:­-word} 如果var为空或者已被删除(unset),那么返回word, 但不改变var的值
tmp=${var:-../build}
echo ${tmp} # ../build
echo ${var} # " "

var=${var:-../}
echo ${var} # ../
echo "##############################"

# 如果var变量有值，则不会替换,并返回var自身值
var="hello"
tmp1=${var:-../}
echo ${tmp1}    #hello
echo ${var}     #hello

echo "**************\${var:=word}:***************"
#${var:=word} 如果var为空或者已被删除，那么返回word,并将var的值设为word
tmp2=${var1:=../build}
echo ${tmp2}    #../build
echo ${var1}    #../build

# ${var2:=../build}   #  ../build: No such file or directory
# echo ${var2}    #../build
echo "##############################"
# 如果var变量有值，则不会替换,并返回var自身值
var3="world"
tmp3=${var3:="hello"}
echo ${tmp3}    #world
echo ${var3}    #world

echo "***************\${var:+word}:**************"
#${var:+word} 如果var为空或者已被删除，那么返回为空, var的值还是为空
tmp4=${var4:+"cc"}
echo ${tmp4}    # cc
echo ${var4}    # cc
echo "##############################"
# 如果var变量有值，则不会替换,并返回word
var5="bb"
tmp5=${var5:+"cc"}
echo ${tmp5}    # cc
echo ${var5}    # bb

echo "***************\${var:?word}:**************"
# 如果变量 var 为空或已被删除(unset)，那么将消息 message 送到标准错误输出，可以用来检
# 测变量 var 是否可以被正常赋值。若此替换出现在Shell脚本中，那么脚本将停止运行。
var6="vv"
echo ${var6:?word}  # vv
echo ${var6}        # vv

echo ${var7:?word}  # ./variable.sh: line 77: var7: word
echo ${var7}        
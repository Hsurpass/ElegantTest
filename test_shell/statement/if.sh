#!/bin/bash

# if [ condition ]; then
#   要执行的语句
# elif [ condition ]; then
#   要执行的语句
# else
#   要执行的语句
# fi

# condition 可以是[], [[]], 或者(())
# [] 是最基本的条件测试表达式
# [[]]是扩展测试命令，提供了比[]更强大的功能
# (()) 是数学表达式，支持常见的+-*/等数学运算


read guess
if [ $guess -eq 2 ]; then # 中括号和条件之间必须有空格
    echo "猜对了"
elif [[ $guess -lt 2 ]]; then
    echo 猜小了
else 
    echo 猜大了
fi



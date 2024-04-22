#!/bin/bash
#./pass_commandLine_arg.sh 1 2 3

echo "可执行程序: $0" # ./pass_commandLine_arg.sh
echo "arg1: $1" # 1
echo "arg2: $2" # 2
echo "arg3: $3" # 3
echo "上一个命令的退出状态: $?" # 0 # 0代表成功，非0代表失败

echo "参数个数: $#" # 3
echo "所有参数：$@" # 1 2 3
echo "所有参数：$*" # 1 2 3

# using $@:
# 1
# 2
# 3
echo "using \$@:"
for arg in $@
do
    echo $arg
done

# using $*:
# 1
# 2
# 3
echo "using \$*:"
for arg in $*
do 
    echo $arg
done


# using "$@":
# 1
# 2
# 3
echo using \"\$@\":
for arg in "$@"
do
    echo $arg
done

# "$*"会把所有参数作为一整体，把所有返回
# using "$*":
# 1 2 3
echo "using \"\$*\":"
for arg in "$*"
do 
    echo $arg
done

echo "当前进程的PID:" $$ 

# $! 代表Shell最后运行的后台Process的PID（后台运行的最后一个进程的进程ID号）。
# 当你在脚本中启动一个后台进程（即在命令后加上&）时，$! 会返回该后台进程的进程ID。
# 这个值可以用来进一步控制或监视该后台进程。
# echo $! 
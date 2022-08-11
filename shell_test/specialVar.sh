#!/bin/bash

################# 命令行参数 ##############
## ./specialVar.sh 1 2 3 4
echo "File Name:$0"
echo "param1:$1"
echo "param2:${2}"
echo "param count:$#"
echo "All params: $@"
echo "All params: $*"

#########上一个命令的退出状态#########
echo $?


#!/bin/bash

# 可以使用`` 或 $() 做命令替换

DATE=`date`
USERS=`who | wc -l`

echo "today is ${DATE}"
echo "number of user are ${USERS}"

FREE=$(free -h)
echo `free -h`
echo $FREE
echo $(free -h)
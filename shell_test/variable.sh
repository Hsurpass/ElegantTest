#!/bin/bash

################### 只读 ###############
echo "************readonly:*****************"
name="peter"
readonly name
name="lili"
echo ${name}

################ 删除变量 ################
echo "************unset:*****************"
age=10
unset age
echo ${age}
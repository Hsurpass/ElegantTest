#!/bin/bash

func1()
{
    echo "hello world"
    return 5;
}

func1
echo $?

func2(){
    var=100 # 在函数中定义的变量在整个shell脚本中都能使用。
    echo "func2"
    func1
}
func2

echo ${var}
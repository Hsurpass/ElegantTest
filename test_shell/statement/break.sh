#!/bin/bash

for i in 1 2 3
do
    for j in 1 2 3
    do
        if [ $i -eq 1 -a $j -eq 2 ]
        then
            # break
            break 2 # 可以直接跳到最外层
        fi
    done
    echo "first loop"
done

echo "outside"

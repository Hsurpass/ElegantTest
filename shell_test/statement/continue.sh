#!/bin/bash

for i in 1 2 3 4
do
    if [ $i -eq 2 ]
    then
        continue
    fi
    echo -n "$i "
done
echo

for i in 1 2 3
do
    for j in 1 2 3
    do
        if [ $i -eq 1 -a $j -eq 2 ]
        then
            # continue 1
            continue 2
        fi
        echo "$i|$j"
    done
done

# continue 1:
# 1 1
# 1 3
# 2 1
# 2 2
# 2 3
# 3 1
# 3 2
# 3 3

# continue 2:
# 1 1
# 2 1
# 2 2
# 2 3
# 3 1
# 3 2
# 3 3
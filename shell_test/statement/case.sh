#!/bin/bash

################case##############
# echo "input a number:"
# read num
# case $num in
#     1) echo "select 1"
#     ;;
#     2) echo "select 2"
#     ;;
#     3) echo "select 3"
#     ;;
#     4|5) echo "select 4 or 5"
#     ;;
#     *) echo "default"
#     ;;
# esac

option=$1;
case ${option} in
    -f) echo "param is -f"
        ;;
    -d) echo "param is -d"
        ;;
    *) 
        echo "$0:usage: [-f] | [-d]"
        exit 1
    ;;
esac
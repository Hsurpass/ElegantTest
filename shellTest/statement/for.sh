#!/bin/bash

################# for ####################

for var in 1 2 3 4 5
do
    echo -n $var " "
done
echo 

for str in 'This is a string'
do 
    echo $str
done

# for var in ${HOME}/.bash*
for var in ${HOME}/*
do
    echo $var
done

# echo ${PATH}
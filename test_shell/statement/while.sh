#!/bin/bash

################# while ####################
count=0
while [ $count -lt 5 ]
do
    echo $count
    count=$(($count + 1))
done

echo "input film: "
while read FILM
do
    echo "great film the $FILM"
done
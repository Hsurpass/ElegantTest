#!/bin/bash

DATE=`date`
USERS=`who | wc -l`

echo "today is ${DATE}"
echo "number of user are ${USERS}"
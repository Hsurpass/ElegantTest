
echo $0
echo $1
echo $2
echo $3
echo $4
echo $5


# if [ -n $5 ] && [ $5 = "xx" ];then
mode=$5
echo $mode
if [ -n $mode ] && [ $mode = "xx" ];then
    echo "set xx"
    print
else
    echo "not set xx"
fi

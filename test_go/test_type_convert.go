package main

import (
	"fmt"
	"strconv"
)

func test_str_convert() {
	// 字符串转换成数字
	str := "123"
	num, err := strconv.Atoi(str)
	fmt.Println(num, err)

	// 数字转换成字符串
	str1 := strconv.Itoa(1234)
	fmt.Println(str1)

	// 字符串转换成浮点数
	f1, err := strconv.ParseFloat("3.14", 64)
	fmt.Println(f1, err)

	// 浮点数转换成字符串
	str2 := strconv.FormatFloat(3.1415926, 'f', -1, 64)
	fmt.Println(str2)
}

func main() {
	test_str_convert()
}

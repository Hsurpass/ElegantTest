package main

import "fmt"

// type-switch 来判断某个 interface 变量中实际存储的变量类型
func test_type_switch(x interface{}) {
	// var x interface {
	// }

	switch i := x.(type) {
	case nil:
		fmt.Printf(" x 的类型 :%T\n", i)
	case int:
		fmt.Println("x 是 int 型")
	case float64:
		fmt.Println("x 是 float64 型")
	case func(int) float64:
		fmt.Println("x 是 func(int) 型")
	case bool, string:
		fmt.Println("x 是 bool 或 string 型")
	default:
		fmt.Printf("未知型")

	}
}

// 使用 fallthrough 会强制执行后面的 case 语句，
// fallthrough 不会判断下一条 case 的表达式结果是否为 true。
func test_fallthrough() {
	switch {
	case false:
		fmt.Println("1、case 条件语句为 false")
		fallthrough
	case true:
		fmt.Println("2、case 条件语句为 true")
		fallthrough
	case false:
		fmt.Println("3、case 条件语句为 false")
		fallthrough
	case true:
		fmt.Println("4、case 条件语句为 true")
	case false:
		fmt.Println("5、case 条件语句为 false")
		fallthrough
	default:
		fmt.Println("6、默认 case")
	}
}

func main() {
	var i interface{}
	test_type_switch(i)
	test_type_switch(20)
	test_type_switch("hello")
	test_type_switch(true)
	test_type_switch(20.08)

	test_fallthrough()
}

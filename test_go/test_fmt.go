package main

// https://www.runoob.com/go/go-fmt-sprintf.html
// https://www.runoob.com/go/go-fmt-printf.html
import "fmt"

func test_array() {
	var v [][4]int // 二维数组

	row1 := [4]int{1, 2, 3, 4}
	var row2 = [4]int{5, 6, 7, 8}
	v = append(v, row1)
	v = append(v, row2)
	fmt.Println(v)
	fmt.Println(v[0])
	fmt.Println(v[1])

	// 遍历二维数组
	for idx, v := range v {
		fmt.Println(idx, v)
	}

	for range v {
		
	}

	v1 := [][]int{}
	row3 := []int{1, 2, 3, 4}
	var row4 = []int{5, 6, 7, 8}
	v1 = append(v1, row3)
	v1 = append(v1, row4)
	fmt.Println(v1)
	fmt.Println(v1[0])
	fmt.Println(v1[1])

	// 遍历二维数组
	for i, vi := range v1 {
		fmt.Printf("idx %d:\n", i)
		for j, vj := range vi {
			fmt.Printf(" %d, %d\n", j, vj)
		}
	}

}

func test_operator() {
	// var x int32 = 1
	// const pi float32 = 3.14

	// fmt.Println(x + pi) // 不同的类型不能运算
	// fmt.Println(pi / x)
}

// iota，特殊常量，可以认为是一个可以被编译器修改的常量。
// iota 在 const关键字出现时将被重置为 0(const 内部的第一行之前)，const 中每新增一行常量声明将使 iota 计数一次
// iota 可理解为 const 语句块中的行索引。
func test_iota() {
	const (
		a = iota
		b = iota
		c = iota
	)
	const (
		x = iota
		y
		z
	)
	fmt.Println(a, b, c, x, y, z)

	// iota 把它看成行索引
	const (
		a1 = iota //0
		b1        //1
		c1        //2
		d  = "ha" //独立值，iota += 1
		e         //"ha"   iota += 1
		f  = 100  //iota +=1
		g         //100  iota +=1
		h  = iota //7,恢复计数
		i         //8
	)
	fmt.Println(a1, b1, c1, d, e, f, g, h, i)

	const (
		i1 = 1 << iota
		j  = 3 << iota
		k
		l
	)
	fmt.Println(i1, j, k, l)
}

///////////////////////全局变量和局部变量////////////////////////////////

var x, y int
var ( // 这种因式分解关键字的写法一般用于声明全局变量
	a int
	b bool
)

var c, d int = 1, 2
var e, f = 123, "hello"

//这种不带声明格式的只能在函数体中出现 := 只能在函数体中使用
// g, h := 123, "hello"

// 全局变量是允许定义但不使用的
func test_globalvar() {
	fmt.Println(x, y, a, b, c, d, e, f)
}

// 测试 _ 标识符， 空白标识符 _ 也被用于抛弃值。_ 实际上是一个只写变量，你不能得到它的值
// 应用场景：当一个函数返回多个返回值时，但有时你并不需要使用从一个函数得到的所有返回值。
func f_() (int, int) {
	a, b := 2, 3
	return a, b
}
func test_() {
	// 如值 5 在：_, b = 5, 7 中被抛弃。
	_, b := 5, 7
	fmt.Println(b)

	_, y := f_()
	fmt.Println(y)
}

// 局部变量定义但不使用的，编译会报错
func test_localvar() {
	var i int
	var f float64
	var b bool
	var s string
	fmt.Printf("%v %v %v %q\n", i, f, b, s) // 0 0 false ""

	var a *int
	var a1 []int
	var a2 map[string]int
	var a3 chan int
	var a4 func(string) int
	var a5 error                                             // error 是接口
	fmt.Printf("%v %v %v %v %v %v\n", a, a1, a2, a3, a4, a5) // <nil> [] map[] <nil> <nil> <nil>

	// var intVal int
	// intVal := 1 // 这时候会产生编译错误，因为 intVal 已经声明，不需要重新声明

	// var intVal int; intVal = 1  === intVal := 1 (相当于c语言int a = 1)

	// 多变量声明
	//类型相同多个变量, 非全局变量
	// 方法1：
	// var vname1, vname2, vname3 int
	// vname1, vname2, vname3 = 1, 2, 3
	// 方法2：
	// var vname1, vname2, vname3 = 1, 2, 3 // 和 python 很像,不需要显示声明类型，自动推断
	// 方法3：
	// 这种方法只能声明局部变量
	vname1, vname2, vname3 := 1, 2, 3 // 出现在 := 左侧的变量不应该是已经被声明过的，否则会导致编译错误

	fmt.Println(vname1, vname2, vname3)
}

func test_fmt() {
	fmt.Print("hello world")       // 不自动换行
	fmt.Println("hello world")     // 自动换行
	fmt.Println("hello" + "world") // 自动换行

	// %d 表示整型数字，%s 表示字符串
	var stockcode = 123
	var enddate = "2020-12-31"
	var url = "Code=%d&endDate=%s"
	fmt.Printf(url, stockcode, enddate)
	fmt.Printf("Code=%d&endDate=%s\n", stockcode, enddate)

	var a int = 4
	var b int32
	var c float32
	var ptr *int

	/* 运算符实例 */
	fmt.Printf("第 1 行 - a 变量类型为 = %T\n", a) // int
	fmt.Printf("第 2 行 - b 变量类型为 = %T\n", b) // int32
	fmt.Printf("第 3 行 - c 变量类型为 = %T\n", c) // float32

	/*  & 和 * 运算符实例 */
	ptr = &a                        /* 'ptr' 包含了 'a' 变量的地址 */
	fmt.Printf("a 的值为  %d\n", a)    // 4
	fmt.Printf("*ptr 为 %d\n", *ptr) // 4
	fmt.Printf("a 的值为  %T\n", ptr)  // 4
	fmt.Printf("a 的值为  %v\n", ptr)  // 4

}

func main() {
	test_fmt()
	fmt.Println("------test_localvar---------------------")
	test_localvar()
	fmt.Println("------test_globalvar---------------------")
	test_globalvar()
	fmt.Println("------test_---------------------")
	test_()
	fmt.Println("------test_iota---------------------")
	test_iota()
	fmt.Println("------test_array---------------------")
	test_array()

	test_operator()
}

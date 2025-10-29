package main

import "fmt"

/*
	var slice1 []type = make([]type, len, capacity)
	or
	slice1 := make([]type, len, capacity)
*/

func test_slice_init() {
	// 切片初始化：
	// 方法1：
	s := []int{1, 2, 3}                             // 定义并初始化
	fmt.Println(s)                                  // [1 2 3]
	fmt.Println("s.len:", len(s), "s.cap:", cap(s)) // 3 3

	// 方法二：使用数组初始化
	arr := [4]int{1, 2, 3, 4}
	s1 := arr[:]
	fmt.Println(s1)                    // [1 2 3 4]
	fmt.Printf("arr addr: %p\n", &arr) // arr addr: 0xc000094000
	fmt.Printf("&arr[0]: %p\n", &arr[0]) // arr addr: 0xc000094000
	fmt.Printf("s1 addr: %p\n", &s1) // s1 addr: 0xc000094018

	// 左闭右开区间
	s2 := arr[1:]
	fmt.Println(s2) // [2 3 4]

	s3 := arr[:4]
	fmt.Println(s3) // [1 2 3 4]

	s4 := arr[1:2]
	fmt.Println(s4) // [2]

	// 方法3：使用另一个切片初始化
	s5 := s3
	fmt.Println(s5) // [1 2 3 4]
	fmt.Printf("s3 addr: %p\n", &s3)
	fmt.Printf("s5 addr: %p\n", &s5) //addr different

	s6 := s3[2:3]
	fmt.Println(s6)               // [3]
	fmt.Println(len(s6), cap(s6)) // 1 2

	// 方法4：使用make初始化
	s7 := make([]int, 3, 4)
	fmt.Println(s7)
	fmt.Println(len(s7), cap(s7)) // 3 4

}

func test_slice_nil() {
	var s []int

	fmt.Printf("len=%d, cap=%d, slice=%v\n", len(s), cap(s), s)
	fmt.Printf("%v\n", s == nil)
}

func test_copy_append() {
	var numbers []int
	printSlice(numbers)

	/* 允许追加空切片 */
	numbers = append(numbers, 0)
	printSlice(numbers)

	/* 向切片添加一个元素 */
	numbers = append(numbers, 1)
	printSlice(numbers)

	numbers = append(numbers, 1)
	printSlice(numbers)

	/* 同时添加多个元素 */
	numbers = append(numbers, 2, 3, 4)
	printSlice(numbers)

	/* 创建切片 numbers1 是之前切片的两倍容量*/
	numbers1 := make([]int, len(numbers), (cap(numbers))*2)

	/* 拷贝 numbers 的内容到 numbers1 */
	copy(numbers1, numbers)
	printSlice(numbers1)

	// 遍历slice
	for k, v := range numbers1 {
		fmt.Printf("%d, %d\n", k, v)
	}
}

func printSlice(x []int) {
	fmt.Printf("len=%d cap=%d slice=%v\n", len(x), cap(x), x)
}

func test_byte_slice() {
	s := []byte("This is a sample Page.")
	s1 := []byte{1, 2, 3, 4}
	s2 := []byte{1, 2, 3, 4}
	s3 := []rune{'你', '好', '世', '界'}
	// s3 := []rune("你好") // error

	fmt.Println(s)
	fmt.Println(s1)
	fmt.Println(s2)
	fmt.Println(s3)
}

func main() {
	test_slice_init()
	fmt.Println("-----------------------------")

	test_slice_nil()
	fmt.Println("-----------------------------")

	test_copy_append()
	fmt.Println("-----------------------------")

	test_byte_slice()
}

package main

import "fmt"

/*
	var slice1 []type = make([]type, len, capacity)
	or
	slice1 := make([]type, len, capacity)
*/

func test_slice_init() {
	// 切片初始化：
	fmt.Println("---------method 1----------")
	// 方法1：
	s := []int{1, 2, 3}                             // 定义并初始化
	fmt.Println(s)                                  // [1 2 3]
	fmt.Println("s.len:", len(s), "s.cap:", cap(s)) // 3 3

	fmt.Println("---------method 2----------")
	// 方法二：使用数组初始化
	arr := [4]int{1, 2, 3, 4}
	s1 := arr[:]
	fmt.Println(s1)                        // [1 2 3 4]
	fmt.Printf("arr addr: %p\n", &arr)     // arr addr: 0xc000094000
	fmt.Printf("&arr[0]: %p\n", &arr[0])   // arr addr: 0xc000094000
	fmt.Printf("s1 addr: %p\n", &s1)       // s1 addr: 0xc000094018
	fmt.Printf("s1[0] addr: %p\n", &s1[0]) // s1 addr: 0xc000094000 &s1[0] == &arr == &arr[0]

	// 左闭右开区间
	s2 := arr[1:]
	fmt.Println(s2) // [2 3 4]

	s3 := arr[:4]
	fmt.Println(s3) // [1 2 3 4]

	s4 := arr[1:2]
	fmt.Println(s4)                                            // [2]
	fmt.Printf("len(s4): %d, cap(s4): %d\n", len(s4), cap(s4)) // 1 3
	fmt.Printf("&arr[1]: %p\n", &arr[1])
	fmt.Printf("&s4[0]: %p\n", &s4[0]) // &s4[0] == &arr[1]
	fmt.Printf("&s4: %p\n", &s4)

	s4 = append(s4, 10)
	fmt.Println(s4)                                            // [2, 10]
	fmt.Printf("len(s4): %d, cap(s4): %d\n", len(s4), cap(s4)) // 2 3
	fmt.Printf("&arr[1]: %p\n", &arr[1])
	fmt.Printf("&s4[0]: %p\n", &s4[0]) // &s4[0] == &arr[1]
	fmt.Printf("&s4: %p\n", &s4)

	s4 = append(s4, 20)
	fmt.Println(s4)                                            // [2, 10, 20]
	fmt.Printf("len(s4): %d, cap(s4): %d\n", len(s4), cap(s4)) // 3 3
	fmt.Printf("&arr[1]: %p\n", &arr[1])
	fmt.Printf("&s4[0]: %p\n", &s4[0]) // &s4[0] == &arr[1]
	fmt.Printf("&s4: %p\n", &s4)

	s4 = append(s4, 30)
	fmt.Println(s4)                                            // [2, 10, 20, 30]
	fmt.Printf("len(s4): %d, cap(s4): %d\n", len(s4), cap(s4)) // 4 6
	fmt.Printf("&arr[1]: %p\n", &arr[1])
	fmt.Printf("&s4[0]: %p\n", &s4[0]) // &s4[0] != &arr[1]
	fmt.Printf("&s4: %p\n", &s4)       // not change s4的地址是固定的

	fmt.Println("---------method 3----------")
	// 方法3：使用另一个切片初始化
	s5 := s3
	fmt.Println(s5) // [1 2 3 4]
	fmt.Printf("s3 addr: %p\n", &s3)
	fmt.Printf("s5 addr: %p\n", &s5) //addr different

	s6 := s3[2:3]
	fmt.Println(s6)               // [3]
	fmt.Println(len(s6), cap(s6)) // 1 2

	s61 := []int{3, 2, 1}
	s62 := s61[2:]
	fmt.Printf("&s61[2]: %p\n", &s61[2])
	fmt.Printf("&s62: %p\n", &s62)
	fmt.Printf("&s62[0]: %p\n", &s62[0])                           // &s62[0] == &s61[2]
	fmt.Printf("len(s62): %d, cap(s62): %d\n", len(s62), cap(s62)) // 1 1
	s62 = append(s62, 5)
	fmt.Printf("&s62[0]: %p\n", &s62[0])                           // 自动扩容 &s62[0] != &s61[2]
	fmt.Printf("len(s62): %d, cap(s62): %d\n", len(s62), cap(s62)) // 2 2

	fmt.Println("---------method 4----------")

	// 方法4：使用make初始化
	s7 := make([]int, 3, 4)
	fmt.Println(s7)
	fmt.Println(len(s7), cap(s7)) // 3 4
	fmt.Printf("s7 addr: %p\n", &s7)
	s7 = append(s7, 5)
	fmt.Printf("s7 addr: %p\n", &s7)
	fmt.Println(len(s7), cap(s7)) // 4 4
	fmt.Println(s7)               // 0 0 0 5

	s71 := s7[1:3]
	fmt.Println(s71)
	fmt.Printf("s71 addr: %p\n", &s71)
	fmt.Printf("s7[1] addr: %p\n", &s7[1])
	fmt.Printf("s71[0] addr: %p\n", &s71[0]) // &s71[0] == &s7[1]

	p := &s71[0]
	*p += 100
	fmt.Println(s7)  // [0 100 0 5]
	fmt.Println(s71) // [100 0]

	s71[1] = 200
	fmt.Println(s7)                                                // [0 100 200 5]
	fmt.Println(s71)                                               // [100 200]
	fmt.Printf("len(s71): %d, cap(s71): %d\n", len(s71), cap(s71)) // 2 3

	s71 = append(s71, 300)
	fmt.Printf("len(s71): %d, cap(s71): %d\n", len(s71), cap(s71)) // 3 3
	s71[0] += 1000
	fmt.Println(s7)  // [0 1100 200 5]
	fmt.Println(s71) // [200 200 300]
	fmt.Printf("s7[1] addr: %p\n", &s7[1])
	fmt.Printf("s71[0] addr: %p\n", &s71[0]) // &s71[0] == &s7[1]
	fmt.Printf("&s71: %p\n", &s71)

	s71 = append(s71, 400)
	fmt.Printf("len(s71): %d, cap(s71): %d\n", len(s71), cap(s71)) // 4 6
	s71[0] += 1000
	fmt.Println(s7)  // [0 1100 200 5]
	fmt.Println(s71) // [2100 200 300]
	fmt.Printf("s7[1] addr: %p\n", &s7[1])
	fmt.Printf("s71[0] addr: %p\n", &s71[0]) // &s71[0] != &s7[1]
	fmt.Printf("&s71: %p\n", &s71)           // not change s71的地址是固定的
}

func test_slice_nil() {
	var s []int

	fmt.Printf("len=%d, cap=%d, slice=%v\n", len(s), cap(s), s)
	fmt.Printf("%v\n", s == nil)
}

func test_copy_append() {
	var numbers []int
	// printSlice(numbers)
	printSliceP(&numbers)

	/* 允许追加空切片 */
	numbers = append(numbers, 0)
	fmt.Printf("&numbers: %p\n", &numbers)
	// printSlice(numbers)
	printSliceP(&numbers)

	/* 向切片添加一个元素 */
	numbers = append(numbers, 1)
	fmt.Printf("&numbers: %p\n", &numbers)
	// printSlice(numbers)
	printSliceP(&numbers)

	numbers_n := append(numbers, 1)
	fmt.Printf("&numbers_n: %p\n", &numbers_n)
	// printSlice(numbers_n)
	printSliceP(&numbers)

	/* 同时添加多个元素 */
	numbers = append(numbers, 2, 3, 4)
	fmt.Printf("&numbers: %p\n", &numbers)
	// printSlice(numbers)
	printSliceP(&numbers)

	/* 创建切片 numbers1 是之前切片的两倍容量*/
	numbers1 := make([]int, len(numbers), (cap(numbers))*2)

	/* 拷贝 numbers 的内容到 numbers1 */
	copy(numbers1, numbers)
	// printSlice(numbers1)
	printSliceP(&numbers)

	// 遍历slice
	for k, v := range numbers1 {
		fmt.Printf("%d, %d\n", k, v)
	}
}

func printSlice(arr []int) {
	fmt.Printf("arr=%p len=%d cap=%d slice=%v\n", &arr, len(arr), cap(arr), arr)
}

func printSliceP(arr *[]int) {
	fmt.Printf("arr=%p len=%d cap=%d slice=%v\n", arr, len(*arr), cap(*arr), *arr)
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
	fmt.Println(string(s3))
}

func test_two_dimensional_slice() {
	// 二维切片
	var twoD [][]int
	for i := 0; i < 3; i++ {
		innerLen := i + 1
		innerSlice := make([]int, innerLen)
		for j := 0; j < innerLen; j++ {
			innerSlice[j] = i + j
		}
		twoD = append(twoD, innerSlice)
	}
	fmt.Println(twoD)

	b := [][]int{
		[]int{1},
		[]int{1, 2, 3},
		[]int{1, 2, 3, 4},
	}
	fmt.Println(b)

	for i, v1 := range b {
		for j, v2 := range v1 {
			fmt.Printf("b[%d][%d] = %d\n", i, j, v2)
		}
	}
}

func test_two_dimension_slice_struct() {
	arr := [5]struct {
		x int
	}{}
	fmt.Println(arr) // [{0} {0} {0} {0} {0}]
	arr[1].x = 10
	fmt.Println(arr) // [{0} {10} {0} {0} {0}]

	s := arr[:]
	s[3].x = 30
	fmt.Println(arr) // [{0} {10} {0} {30} {0}]
	fmt.Println(s)   // [{0} {10} {0} {30} {0}]
	fmt.Printf("&arr: %p\n", &arr)
	fmt.Printf("&s[0]: %p\n", &s[0]) // &s[0] == &arr

}

func main() {
	// test_slice_init()
	// fmt.Println("-----------------------------")

	// test_slice_nil()
	// fmt.Println("-----------------------------")

	// test_copy_append()
	// fmt.Println("-----------------------------")

	test_byte_slice()

	// test_two_dimensional_slice()
	// test_two_dimension_slice_struct()
}

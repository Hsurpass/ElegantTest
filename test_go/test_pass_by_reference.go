package main

import "fmt"

func pass_int_value(n int) {
	n = 100
}
func pass_int_pointer(n *int) {
	*n = 100
}
func test_pass_int() {
	num := 10

	pass_int_value(num)
	fmt.Println(num)

	pass_int_pointer(&num)
	fmt.Println(num)

}

func pass_string_value(s string) {
	s = "def"
}
func pass_string_pointer(s *string) {
	*s = "def"
}
func test_pass_string() {
	s := "abc"

	pass_string_value(s)
	fmt.Println(s)
	pass_string_pointer(&s)
	fmt.Println(s)
}

func pass_array_value(arr [3]int) {
	arr[2] = 60
}
func pass_array_ref(arr *[3]int) {
	arr[2] = 60
}
func test_pass_array() {
	arr := [3]int{4, 5, 6}

	pass_array_value(arr)
	fmt.Println(arr)
	pass_array_ref(&arr)
	fmt.Println(arr)

}

// slice、map、channel都是引用类型
func pass_slice_ref(s []int) {
	s[1] = 20
}
func test_pass_slice() {
	slice := []int{1, 2, 3}

	pass_slice_ref(slice)
	fmt.Println(slice)
}

func pass_map_ref(m map[string]int) {
	m["b"] = 20
}
func test_pass_map() {
	m := map[string]int{"a": 1, "b": 2}

	pass_map_ref(m)
	fmt.Println(m)
}

func pass_func_value(f func()) {
	f = func() {
		fmt.Println("world")
	}
}
func pass_func_ref(f *func()) {
	*f = func() {
		fmt.Println("world")
	}
}
func test_pass_func() {
	f := func() {
		fmt.Println("hello")
	}

	pass_func_value(f)
	f()
	pass_func_ref(&f)
	f()
}

type STU struct {
	a string
	b int
}

func pass_struct_value(stu STU) {
	stu.a = "world"
	stu.b = 20
}
func pass_struct_ref(stu *STU) {
	stu.a = "world"
	stu.b = 20
}
func test_pass_struct() {
	st := STU{"hello", 2}

	pass_struct_value(st)
	fmt.Println(st)
	pass_struct_ref(&st)
	fmt.Println(st)
}

func main() {
	test_pass_int()
	test_pass_string()
	test_pass_array()
	fmt.Println("-------------------------")
	test_pass_slice()
	test_pass_map()

	test_pass_func()
	test_pass_struct()
}

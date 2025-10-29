package main

import "fmt"

var arr0 [5]int = [5]int{1, 2, 3, 4, 5}
var arr1 = [3]string{"a", "b", "c"}
var arr2 = [...]float64{1.1, 2.2, 3.3, 4.4}
var arr3 = [...]byte{0x1, 0x2, 0x3, 0x4, 0x5}
var arr4 = [...]rune{'x', 'y', 'z'}
var arr5 = [...]bool{true, false, true, false}
var arr6 = [...]complex128{1 + 2i, 3 + 4i, 5 + 6i}
var arr7 = [...]uint{10, 20, 30, 40, 50}
var arr8 = [...]int8{-128, 0, 127}
var arr9 = []string{"hello", "world"}
var arr10 = [5]string{3: "hello", 4: "world"}
var arr11 = [...]struct {
	id   uint64
	name string
}{
	{id: 1, name: "Alice"},
	{id: 2, name: "Bob"},
	{id: 3, name: "Charlie"},
}

var arr12 [2][3]int = [2][3]int{{1, 2, 3}, {4, 5, 6}}
var arr13 [2][3]int = [...][3]int{{1, 2, 3}, {4, 5, 6}}

func print_array(arr [5]int) {
	fmt.Printf("print_array &arr: %p\n", &arr)
}

func print_array_p(arr *[5]int) {
	fmt.Printf("print_array &arr: %p\n", arr)
}


func main() {
	fmt.Println("Array 0:", arr0)
	fmt.Println("Array 1:", arr1)
	fmt.Println("Array 2:", arr2)
	fmt.Println("Array 3:", arr3)
	fmt.Println("Array 4:", arr4)
	fmt.Println("Array 5:", arr5)
	fmt.Println("Array 6:", arr6)
	fmt.Println("Array 7:", arr7)
	fmt.Println("Array 8:", arr8)
	fmt.Println("Array 9 (slice):", arr9)
	fmt.Println("Array 10:", arr10)
	fmt.Println("Array 11:", arr11)
	fmt.Println("Array 12:", arr12)
	fmt.Println("Array 13:", arr13)

	b := [...][2]int{{1, 1}, {2, 2}, {3, 3}} // 第 2 纬度不能用 "..."。
	fmt.Println("b:", b)

	for i, v := range b {
		for j, w := range v {
			fmt.Printf("b[%d][%d] = %d\n", i, j, w)
		}
	}

	fmt.Printf("arr0: %p\n", &arr0)
	print_array(arr0)
	print_array_p(&arr0)
}

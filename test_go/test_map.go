package main

import "fmt"

func test_map_init() {
	m := make(map[string]int)      // 创建一个空的map
	m1 := make(map[string]int, 10) // 创建一个容量为10的map
	m2 := map[string]int{          // 定义时初始化
		"apple":  1,
		"banana": 2,
		"orange": 3,
	}
	fmt.Println(len(m))  // 0
	fmt.Println(len(m1)) // 0
	fmt.Println(len(m2)) // 3
	fmt.Println(m2)
}

func test_crud_map() {
	m := make(map[string]int)

	// 增加元素
	m["apple"] = 0
	m["banana"] = 1
	fmt.Println(len(m)) // 2
	// 获取元素
	fmt.Println(m["apple"])  // 0
	fmt.Println(m["banana"]) // 1
	// 修改元素
	m["apple"] = 5
	fmt.Println(m["apple"])  // 5
	fmt.Println(m["banana"]) // 1
	// 遍历元素
	for k, v := range m {
		fmt.Println(k, v)
	}
	// 删除元素
	delete(m, "apple")
	fmt.Println(len(m))      // 1
	fmt.Println(m["apple"])  // 0
	fmt.Println(m["banana"]) // 1

	k1, v1 := m["apple"]
	fmt.Printf("k1:%v, v1:%v\n", k1, v1) // 0 false
	k2, v2 := m["banana"]
	fmt.Printf("k2:%v, v2:%v\n", k2, v2) // 1 true
}

func main() {
	test_map_init()
	fmt.Println("-------------------------------")
	test_crud_map()
}

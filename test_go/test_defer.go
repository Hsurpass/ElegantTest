package main

import (
	"fmt"
	"sync"
)

// defer 会将函数推迟到外层函数返回之后再执行
func test_defer_base() {
	defer fmt.Println("world")

	fmt.Println("hello")
}

// 推迟的函数调用会被压入栈中。当外层函数返回时，被推迟的函数会按照后进先出的顺序调用。
func test_defer_multi_func_call() {
	fmt.Println("counting")

	for i := 0; i < 3; i++ {
		defer fmt.Println(i)
	}

	fmt.Println("done")
}

var (
	m   = make(map[int]string, 3)
	mtx sync.Mutex
)

func set_value(key int, v string) {

	mtx.Lock()
	defer mtx.Unlock()
	m[key] = v

}
func read_value(key int) string {
	mtx.Lock()
	defer mtx.Unlock()

	return m[1]
}
func test_defer_lockguard() {
	set_value(1, "abc")

	fmt.Println(read_value(1))
}

func main() {
	test_defer_base()
	test_defer_multi_func_call()

	test_defer_lockguard()
}

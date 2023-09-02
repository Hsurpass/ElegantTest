package main

import (
	"fmt"
)

func sum(s []int, c chan int) {
	sum := 0
	for _, v := range s {
		sum += v
	}
	c <- sum
}

// channel是先进先出的，先运行的函数先返回结果 ???
func test_channel_fifo() {
	s := []int{1, 2, 3, 4, 5, 6}

	fmt.Println(s[:len(s)/2])
	fmt.Println(s[len(s)/2:])

	// c := make(chan int)
	c := make(chan int, 2)

	go sum(s[:len(s)/2], c)
	go sum(s[len(s)/2:], c)

	x, y := <-c, <-c // 从通道中接收数据

	fmt.Printf("x + y = %d + %d = %d\n", x, y, x+y) // 15 + 6 =21
}

func fibonacci(n int, c chan int) {
	x, y := 0, 1
	for i := 0; i < n; i++ {
		c <- x
		x, y = y, x+y
	}
	close(c)
}

func test_channel_block() {
	c := make(chan int, 10)
	go fibonacci(cap(c), c)
	// range 函数遍历每个从通道接收到的数据，因为 c 在发送完 10 个
	// 数据之后就关闭了通道，所以这里我们 range 函数在接收到 10 个数据
	// 之后就结束了。如果上面的 c 通道不关闭，那么 range 函数就不
	// 会结束，从而在接收第 11 个数据的时候就阻塞了。
	for i := range c {
		fmt.Println(i)
	}
}

func main() {
	// test_channel_fifo()
	test_channel_block()
}

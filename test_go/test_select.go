package main

import (
	"fmt"
	"time"
)

func test_select() {
	ch1 := make(chan string)
	ch2 := make(chan string)

	go func() {
		time.Sleep(1 * time.Second)
		ch1 <- "one"
	}()

	go func() {
		time.Sleep(1 * time.Second)
		ch2 <- "two"
	}()

	for i := 0; i < 2; i++ {
		select {
		case msg1 := <-ch1:
			fmt.Println("received", msg1)
		case msg2 := <-ch2:
			fmt.Println("received", msg2)
		}
	}
}

func test_select_nonblock() {
	// 定义两个通道
	ch1 := make(chan string)
	ch2 := make(chan string)

	// 启动两个 goroutine，分别从两个通道中获取数据
	go func() {
		for i := 0; i < 2; i++ {
			time.Sleep(1 * time.Second)
			ch1 <- "from 1"
		}
		// close(ch1)
	}()
	go func() {
		for i := 0; i < 2; i++ {
			time.Sleep(1 * time.Second)
			ch2 <- "from 2"
		}
		// close(ch2)
	}()

	// 使用 select 语句非阻塞地从两个通道中获取数据
	for {
		select {
		case msg1 := <-ch1:
			fmt.Println(msg1)
		case msg2 := <-ch2:
			fmt.Println(msg2)
		default:
			// 如果两个通道都没有可用的数据，则执行这里的语句
			fmt.Println("no message received")
		}
		time.Sleep(1 * time.Second)
	}
}

func test_random_select() {
	ch := make(chan int)

	go func() {
		for range time.Tick(1 * time.Second) {
			ch <- 0
		}
	}()

	for {
		select {
		case <-ch:
			fmt.Println("case1")

		case <-ch:
			fmt.Println("case2")
		}
	}
}

func main() {
	// test_random_select()
	// test_select()
	test_select_nonblock()
}

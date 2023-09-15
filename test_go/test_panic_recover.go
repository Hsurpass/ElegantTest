package main

import (
	"fmt"
	"time"
)

func test_panic_nest() {
	fmt.Println("start main")

	defer func() {
		defer func() {
			panic("panic again again")
		}()
		panic("panic again")
	}()
	panic("panic once")
}

func test_recover() {
	fmt.Println("外层开始")

	defer func() {
		fmt.Println("外层准备recover")
		if err := recover(); err != nil {
			fmt.Printf("%#v-%#v\n", "外层", err) // err已经在上一级的函数中捕获了，这里没有异常，只是例行先执行defer，然后执行后面的代码
		} else {
			fmt.Println("外层没做啥事")
		}
		fmt.Println("外层完成recover")
	}()

	fmt.Println("外层即将异常")

	f()

	fmt.Println("外层异常后")
	defer func() {
		fmt.Println("外层异常后defer")
	}()
}

func f() {
	fmt.Println("内层开始")
	defer func() {
		fmt.Println("内层recover前的defer")
	}()

	defer func() {
		fmt.Println("内层准备recover")
		if err := recover(); err != nil {
			fmt.Printf("%#v-%#v\n", "内层", err) // 这里err就是panic传入的内容
		}

		fmt.Println("内层完成recover")
	}()

	defer func() {
		fmt.Println("内层异常前recover后的defer")
	}()

	panic("异常信息")

	defer func() {
		fmt.Println("内层异常后的defer")
	}()

	fmt.Println("内层异常后语句") //recover捕获的一级或者完全不捕获这里开始下面代码不会再执行
}

func test_recover_2() {
	go func() {
		defer func() {
			if r := recover(); r != nil {
				fmt.Println("协程发生错误:", r)
			}
		}()

		fmt.Println("协程挂起")
		time.Sleep(2 * time.Second)
		panic("出现错误") // 引发恐慌
		time.Sleep(1 * time.Second)
		fmt.Println("协程恢复")
	}()

	fmt.Println("主程序继续执行")
	time.Sleep(3 * time.Second)
	fmt.Println("主程序执行完毕")
}

func main() {
	// test_panic_nest()
	// test_recover()
	test_recover_2()
}

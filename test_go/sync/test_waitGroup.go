package main

import (
	"fmt"
	"net/http"
	"sync"
)

func main() {
	var wg sync.WaitGroup

	var urls = []string{
		"http://www.github.com/",
		"http://www.qiniu.com/",
		"http://www.golangtc.com/",
	}

	for _, url := range urls {
		// 每增加一个任务，wg的计数加一
		wg.Add(1)

		// 开启一个协程任务
		go func(url string) {
			// 函数执行结束，wg计数减一
			defer wg.Done()

			// 访问url
			_, err := http.Get(url)

			// 访问完成后，打印地址url和错误
			fmt.Println(url, err)
		}(url)
	}

	// 等待所有任务完成
	wg.Wait()

	fmt.Println("finish")
}

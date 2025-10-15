// go run a.go b.go
// go run .
// go build .
// go build a.go b.go
// go build -o ab a.go b.go

/*
包名一致性：目录名和包声明要一致

导出函数：只有首字母大写的函数才能被其他包访问

模块名：确保导入路径与 go.mod 中的模块名匹配
*/
package main

import (
	"fmt"
	"init_main_import/packageC"
	// _ "init_main_import/packageE" // or
)
import _ "init_main_import/packageE" // blank identifier (only init function is needed

func init() {
	fmt.Println("a.go init")
}

func main() {
	fmt.Println("a.go main")
	funcB()
	packageC.FuncC()
	packageC.FuncD()
}

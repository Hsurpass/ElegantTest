package main

import (
	"fmt"
	lib1 "mainpro/dir1"        // 目录
	lib2xx "mainpro/dir1/dir2" // 目录
	_ "othermod1"              // go.mod中的package名

	// 包名/目录 "othermod1/othermod1lib"
	"utilxx"

	"github.com/bytedance/sonic"
)

func init() {
	fmt.Println("main init")

}

func main() {
	fmt.Println("main")

	// 导入同模块同目录同package的函数 go build main.go test1.go
	// 函数名首字母无需大写指定公有访问权限，无需导入路径，可直接调用相应函数
	Test1()
	test1()
	fmt.Println(Name)
	fmt.Println(age)

	// 导入同模块同目录不同package的函数
	// 同一个目录下的package名必须相同
	// test2.test2()	// error

	// 导入同模块不同目录不同package的函数
	lib1.Lib1() //以大写字母开头的函数是私有的，可调用
	// lib1.lib1()	//以小写字母开头的函数是私有的，不可调用
	lib2xx.Lib2()
	fmt.Println(lib1.Lib1name)
	// fmt.Println(lib1.lib1Age)	// 私有

	// 导入不同模块不同目录不同package的函数
	// 需要在当前模块的go.mod中添加require 和replace
	// othermod1.Othermod1()
	// othermod1libxx.Othermod1lib()	//私有
	// fmt.Println(othermod1.Othername)
	// fmt.Println(othermod1.otherAge) // 私有

	utilxx.Utilxx()
	fmt.Println(utilxx.UtilxxName)
	// fmt.Println(utilxx.utilxxage)	// 私有

	bytes, _ := sonic.Marshal("hello")
	fmt.Println(string(bytes))

}

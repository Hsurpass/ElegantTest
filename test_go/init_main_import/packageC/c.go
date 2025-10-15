/*
包名一致性：目录名和包声明要一致

导出函数：只有首字母大写的函数才能被其他包访问

模块名：确保导入路径与 go.mod 中的模块名匹配
*/

package packageC

import (
	"fmt"
	"init_main_import/packageD"
)

func init() {
	fmt.Println("c.go init")
}

func FuncC() {
	fmt.Println("FuncC in c.go")
}

func FuncD() {
	packageD.FuncD()
}

// func main() {
// 	fmt.Println("c.go main")
// }
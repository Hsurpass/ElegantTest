package main

import (
	"fmt"
)

func init() {
	fmt.Println("b.go init")
}

func funcB() {
	fmt.Println("funcB in b.go")
}

// func main() {
// 	fmt.Println("b.go main")
// }
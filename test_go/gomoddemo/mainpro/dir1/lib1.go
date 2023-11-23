package lib1

import "fmt"

var (
	Lib1name = "lib1name"
	lib1Age  = 30
)

func Lib1() {
	fmt.Println("Lib1")
}

func lib1() {
	fmt.Println("lib1")
}

func init() {
	fmt.Println("lib1 init")
}

func init() {
	fmt.Println("lib1 init xx")
}

package othermod1

import "fmt"

var (
	Othername="Othername"
	otherAge=20
)

func Othermod1() {
	fmt.Println("Othermod1")
}

func othermod1() {
	fmt.Println("othermod1")
}

func init() {
	fmt.Println("othermod1 init")
}

func init() {
	fmt.Println("othermod1 init xx")
}

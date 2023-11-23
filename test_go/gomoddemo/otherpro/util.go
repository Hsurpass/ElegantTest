package utilxx

import "fmt"

var (
	UtilxxName = "UtilxxName"
	utilxxage  = 50
)

func Utilxx() {
	fmt.Println("Utilxx")
}

func utilxx() {
	fmt.Println("utilxx")
}

func init() {
	fmt.Println("utilxx init")
}

func init() {
	fmt.Println("utilxx init xx")
}

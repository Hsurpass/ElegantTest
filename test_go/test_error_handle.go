package main

import (
	"errors"
	"fmt"
	"math"
)

func Sqrt(f float64) (float64, error) {
	if f < 0 {
		return 0, errors.New("math: square root of negative number")
	}

	return math.Sqrt(f), nil
}

func test_sqrt_error() {
	result, err := Sqrt(-1)

	fmt.Println(result, err)
	// if err != nil {
	// }
}

type error interface {
	Error() string
}

type DivideError struct {
	dividee int
	divider int
}

func (de *DivideError) Error() string {
	strFormat := `
    Cannot proceed, the divider is zero.
    dividee: %d
    divider: 0
`
	return fmt.Sprintf(strFormat, de.dividee)
}

func Divide(varDividee int, varDivider int) (r int, errmsg string) {
	if varDivider == 0 {
		err := DivideError{
			varDividee,
			varDivider,
		}
		errmsg = err.Error()
		return
		// return 0, err.Error()
	}

	return varDividee / varDivider, ""
}

func test_divide() {
	if result, errMsg := Divide(100, 10); errMsg == "" {
		fmt.Println("100/10 = ", result)
	}

	result, errMsg := Divide(100, 0)
	fmt.Printf("result:%d, errorMsg is: %s\n", result, errMsg)
}

func main() {
	// test_sqrt_error()
	test_divide()
}

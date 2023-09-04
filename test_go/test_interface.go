package main

import (
	"fmt"
	"math"
)

// Phone是个接口类型
type Phone interface {
	call()
}

type NokiaPhone struct {
}

func (nokiaPhone NokiaPhone) call() {
	fmt.Println("I am Nokia, I can call you!")
}

type IPhone struct {
}

func (iPhone IPhone) call() {
	fmt.Println("I am iPhone")
}

func test_phone() {
	var phone Phone

	phone = new(NokiaPhone)
	phone.call()

	phone = new(IPhone)
	phone.call()
}

// Shape是一个接口类型
type Shape interface {
	area() float64
}

type Rectangle struct {
	width  float64
	height float64
}

func (r Rectangle) area() float64 {
	return r.width * r.height
}

type Circle struct {
	radius float64
}

func (c Circle) area() float64 {
	return 3.14 * c.radius * c.radius
}

func test_area() {
	r := Rectangle{10, 20}
	fmt.Printf("矩形面积: %f\n", r.area())

	var shape Shape
	shape = Circle{radius: 3}
	fmt.Printf("圆形面积: %f\n", shape.area())
}

// //////////////////////////////////////////
type I interface {
	M()
}
type T struct {
	s string
}

func (t *T) M() {
	if t == nil { // 处理t是空值的情况
		fmt.Println("nil")
		return
	}
	fmt.Println(t.s)
}

type F float32

func (f F) M() {
	fmt.Println(f)
}
func describe(i I) {
	fmt.Printf("(%v, %T)\n", i, i)
}
func test_interface_pass() {
	var i I

	i = &T{"hello"}
	describe(i) // (&{hello}, *main.T)
	i.M()

	i = F(math.Pi)
	describe(i) // (3.1415927, main.F)
	i.M()

	// var t *T = nil
	var t *T
	i = t
	describe(i) // (<nil>, *main.T)
	i.M()       // nil

	var i1 I
	describe(i1) // (<nil>, <nil>)
	i1.M()       // panic: runtime error: invalid memory address or nil pointer dereference
	// [signal SIGSEGV: segmentation violation code=0x1 addr=0x0 pc=0x47c994]
}

func describe_nil(i interface{}) {
	fmt.Printf("(%v, %T)\n", i, i)
}
func test_nil_interface() {
	var i interface{}
	describe_nil(i) // (<nil>, <nil>)

	i = 42
	describe_nil(i) // (42, int)

	i = "abc"
	describe_nil(i) // (abc, string)
}

func test_type_assert() {
	var i interface{} = "hello"

	s := i.(string)
	fmt.Println(s)

	s, ok := i.(string)
	fmt.Println(s, ok)

	f, ok := i.(float32)
	fmt.Println(f, ok)

	f = i.(float32)
	fmt.Println(f) // panic: interface conversion: interface {} is string, not float32
	// goroutine 1 [running]: main.test_type_assert()

}

/*
Stringer
fmt 包中定义的 Stringer 是最普遍的接口之一。

	type Stringer interface {
	    String() string
	}

Stringer 是一个可以用字符串描述自己的类型。fmt 包（还有很多包）都通过此接口来打印值。
*/
type IPAddr [4]byte

// TODO: 给 IPAddr 添加一个 "String() string" 方法
func (ip IPAddr) String() string {
	return fmt.Sprintf("\"%d.%d.%d.%d\"", ip[0], ip[1], ip[2], ip[3])
}
func test_ip_to_string() {
	hosts := map[string]IPAddr{
		"loopback":  {127, 0, 0, 1},
		"googleDNS": {8, 8, 8, 8},
	}
	for name, ip := range hosts {
		fmt.Printf("%v: %v\n", name, ip)
	}
}

func main() {
	test_phone()
	test_area()

	// test_interface_pass()
	test_nil_interface()
	// test_type_assert()
	test_ip_to_string()
}

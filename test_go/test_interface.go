package main

import "fmt"

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

func main() {
	test_phone()
	test_area()
}

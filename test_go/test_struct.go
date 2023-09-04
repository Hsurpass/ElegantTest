package main

import "fmt"

type BOOK struct {
	title   string
	author  string
	subject string
	book_id int
}

func test_struct() {
	var book1 BOOK
	book1.title = "Go 语言"
	book1.author = "www.runoob.com"
	book1.subject = "Go 语言教程"
	book1.book_id = 6495407

	fmt.Printf("Book 1 title : %s\n", book1.title)
	fmt.Printf("Book 1 author : %s\n", book1.author)
	fmt.Printf("Book 1 subject : %s\n", book1.subject)
	fmt.Printf("Book 1 book_id : %d\n", book1.book_id)

	// var book2 *BOOK = &book1
	book2 := &book1

	fmt.Printf("Book 2 title : %s\n", book2.title)
	fmt.Printf("Book 2 author : %s\n", book2.author)
	fmt.Printf("Book 2 subject : %s\n", book2.subject)
	fmt.Printf("Book 2 book_id : %d\n", book2.book_id)

}

// 带接收者参数 (b BOOK) 的函数作为结构体的方法，可以直接调用, 不用传参
func (b BOOK) printTitle() {
	fmt.Println(b.title)
}
func (b *BOOK) printSubject() {
	fmt.Println(b.subject)
}

// 普通函数 需要传参
func printAuthor(b BOOK) {
	fmt.Println(b.author)
}
func test_func_call() {
	b := BOOK{"a", "b", "c", 10}

	b.printTitle()
	b.printSubject() // 值和指针都能调用接收者方法
	b1 := &b
	b1.printTitle() // 值和指针都能调用接收者方法

	printAuthor(b)
}

func main() {
	test_struct()
	test_func_call()
}

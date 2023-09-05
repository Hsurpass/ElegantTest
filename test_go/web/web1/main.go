package main

import (
	"fmt"
	"io/ioutil"
	"log"
	"net/http"
)

func main() {
	http.HandleFunc("/", index) // index 为向 url发送请求时，调用的函数
	http.HandleFunc("/index", index_) // index 为向 url发送请求时，调用的函数

	log.Fatal(http.ListenAndServe("192.168.244.34:8000", nil))
	// log.Fatal(http.ListenAndServe("localhost:8000", nil))
}

func index(w http.ResponseWriter, r *http.Request) {
	fmt.Fprintf(w, "C语言中文网")
}

func index_(w http.ResponseWriter, r *http.Request) {
	content, _ := ioutil.ReadFile("./index.html")
	w.Write(content)
}

package main

import (
	"fmt"
	"github.com/google/uuid"
)

func main() {
	fmt.Println("hello")
	id := uuid.New()
	fmt.Println("Generated UUID:", id)
}


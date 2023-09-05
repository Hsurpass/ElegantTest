package demo

import (
	"fmt"
	"testing"
)

// 单元测试：go test -v
func Test_getArea(t *testing.T) {
	area := getArea(4, 5)
	if area != 20 {
		t.Error(" test fail!!")
	}
}

// 压力测试：go test -bench="."
func Benchmark_getArea(t *testing.B) {
	fmt.Printf("t.N:%d\n", t.N)
	for i := 0; i < t.N / 100000000; i++ {
		getArea(4, 5)
	}
}

// 覆盖率测试：go test -cover

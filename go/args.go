//不定参数

package main

import "fmt"

func v1(args ...int) {         //...type语法糖，简化代码
    for _, x := range args {
        fmt.Print(" ", x, ";" )
    }
    fmt.Print("\n")
}

func v2(args []int) {
    for _, x := range args {
        fmt.Print(" ", x, ";" )
    }
    fmt.Print("\n")
}

func v3(args ...interface{}) {          //...interface{}接受任何类型数据
    for _, x := range args {
        fmt.Print(" ", x, ";" )
    }
    fmt.Print("\n")
}

func main() {
//    v1(1, 2, 3, 4)
//
//    v2([]int{9, 8, 7, 6})

//    args := []int{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 }
//    v1(args...)
//    v1(args[5:]...)

    v3(1, "hello", 1.23, []int{1, 2, 3})

}

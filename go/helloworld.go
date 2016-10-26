package main

import (
    "fmt"
    "errors"
)

func Compute(value1 int, value2 int)(result int, err error) {
    result = value1 + value2
    err = errors.New("success")
    return result, err
//    err = "add"
}

func main() {
    fmt.Println("hello world!")

    result, err := Compute(1, 2)
    fmt.Printf("result:%d    err:%v \n", result, err)
    fmt.Println("result:", result, "      err:", err)

}



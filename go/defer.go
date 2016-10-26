//defer  释放资源
package main

import (
    "fmt"
    "os"
)

func main() {
    file, err := os.Open("heilloworld.go")
    defer file.Close()         //运行结束时自动关闭文件
    if(err == nil) {
       fmt.Print(file, "\n")
    } else {
        fmt.Print(err.Error(), "\n")
    }
}

//闭包

package main

import "fmt"


func main() {
    var j int = 5
    a := func()(func()) {
        i := 10         //保护参数i的安全性，只有匿名函数才能访问
        return func() {
            i = i + 10
            fmt.Print("i : ", i, " ; j : ", j, "\n" )
        }
    }()

    a()
    
    j = 10

    a()
    a()
}

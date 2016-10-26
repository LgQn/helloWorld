package main

import "fmt"
import "os"
import "strconv"

import "simplemath"

func main() {
    args := os.Args[0:]
    fmt.Println("输入的指令为：\n")
    for i:= 0; i < len(args); i ++ {
        fmt.Println("Args[", i, "]:", args[i])
    }
    fmt.Println("==========\n")

    switch args[1] {
    case "add":
        if len(args) != 4 {
            fmt.Println("WARN:parameter err!!")
        }
        v1, err1 := strconv.Atoi(args[2])
        v2, err2 := strconv.Atoi(args[3])
        if err1 != nil || err2 != nil {
            fmt.Println("WARN:parameter err!!")
            return
        }
        ret := simplemath.Add(v1, v2)
        fmt.Println("result:", ret)
    default:
        fmt.Println("eg...")
    }
}

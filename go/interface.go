package main

import (
    "fmt"
)

type inter interface {
    Console() int
}

type a struct {
    key int
    val string
}

func (p *a)Console() int {
    fmt.Println(p.key)
    fmt.Println(p.val)
    return 1
}

func (p *a)Console1() int {
    fmt.Println(p.key)
    fmt.Println(p.val)
    return 1
}

func measu(ww inter) {
    ww.Console()
}

func main() {

    b := &a{key: 1, val: "dsadw"}

    measu(b)


//    b.Console()

}

package main

import (
    "fmt"
 //   "reflect"
)

func printf ( arry ...int) {

    fmt.Println("len:",len(arry))
    fmt.Println("cap:",cap(arry))

    fmt.Print(":")
    for _, x := range arry {
        fmt.Print(x, " ")
    }
    fmt.Print("\n\n")
}

func main() {

//    Myarry := make([]int, 1)
//    printf(Myarry)

//    Myarry2 := make([]int, 5, 10)
//    printf(Myarry2)

    Myarry1 := []int{ 1, 2, 3, 4, 5, 6}
//    fmt.Println(reflect.TypeOf(Myarry1))
    printf(Myarry1...)

//    Myarry3 := Myarry1[:4]
//    printf(Myarry3)

//    Myarry4 := append(Myarry, Myarry1...)
//    printf(Myarry4)
}

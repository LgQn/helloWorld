
package main

import (
    "fmt"
    "flag"        //读取命令行
    "io"
    "bufio"
    "os"
    "strconv"

    quick "quicksort"
    bubble "bubblesort"
)


func readValues(infile string)(values []int, err error) {
    file, err := os.Open(infile)
    if err != nil {
        fmt.Println("Faile read file")
        return
    }
    defer file.Close()

    br := bufio.NewReader(file)

    values = make([]int, 0)

    for {
        line, isPrefix, err1 := br.ReadLine()

        if err1 != nil {
            if err1 != io.EOF {
                err = err1
            }
            break
        }

       if isPrefix {
           fmt.Println("A too long line!")
           return
       }

       str := string(line)

       value, err1 := strconv.Atoi(str)

       if err1 != nil {
           err = err1
           return
       }

       values = append(values, value)
    }

    return
}

func writeValues(values []int, outfile string) error {
    fmt.Println(values)
    file, err := os.Create(outfile)
    if err != nil {
        fmt.Println("Faile to create outfile")
        return err
    }
    defer file.Close()

    for _, value := range values {
        str := strconv.Itoa(value)
        file.WriteString(str + "\n")
    }
    return nil
}

var infile *string = flag.String("i", "", "File for input")
var outfile *string = flag.String("o", "", "File for output")
var algorithm *string = flag.String("a", "", "Sort algorithm")

func main() {
    flag.Parse()

    if *infile != "" && *outfile != "" {
        fmt.Println("infile=", *infile, "; outfile=", *outfile, "; algorithm=", *algorithm)
        fmt.Println("Starting...")
    } else {
        return
    }

    value, err := readValues(*infile)
    if err == nil {
        fmt.Println("Success read file ! values = ", value)

       switch *algorithm {
        case "quicksort":
            quick.Quicksort(value)
        case "bubblesort":
            bubble.Bubblesort(value)
        default:
            fmt.Println("Unknow sort!")
            return
        }

        err1 := writeValues(value, *outfile)
        if err1 != nil {
            fmt.Println(err1)
        } else {
            fmt.Println("Success write file!")
        }
    } else {
        fmt.Println(err)
    }

}

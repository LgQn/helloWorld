package main
import "fmt"
func main() {
        messages := make(chan string, 1)
//        signals := make(chan bool)

        select {
        case msg := <- messages:
            fmt.Println("received message", msg)
        default:
            fmt.Println("no message received")
        }

        select {
        case messages <- "hi":
            fmt.Println("seng message hi")
        default:
            fmt.Println("no message send")
        }

        <-messages
    }



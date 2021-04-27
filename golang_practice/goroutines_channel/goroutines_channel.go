package main
import (
	"fmt"
	"time"
)

func partenza(ch1 chan int) {
	fmt.Print("partenza\n")
	time.Sleep(3*1e9)
	ch1 <- 100
	fmt.Print("sent\n")
}

func arrivo(ch1 chan int) {
	fmt.Print("arrivo\n")
	x := <-ch1
	fmt.Printf("received %d from ch1\n", x)
}

func main() {
	fmt.Print("Start main program\n")
	var ch1 = make(chan int)
	go arrivo(ch1)
	go partenza(ch1)
	time.Sleep(6*1e9)
	fmt.Print("End main program\n")
}

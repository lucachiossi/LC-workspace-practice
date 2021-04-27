package main
import "fmt"
func main() {
	// with not defer
	for i := 0; i <= 3; i++ {
		fmt.Println(i)
	}

	// with defer
	for i := 0; i <= 3; i++ {
		defer fmt.Println(i)
	}
}

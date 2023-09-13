package main

import (
	"fmt"
	"time"
)

func main() {

	c1 := make(chan string)
	c2 := make(chan string)

	go listen(c1, c2)

	go send(c1, "Kate")

	go send(c2, "Aksenova")
	for {

	}
}
func listen(c1 chan string, c2 chan string) {
	fmt.Println("Начало прослушивания:", time.Now())
	for {
		select {
		case msg1 := <-c1:
			fmt.Println("mesage is:", msg1, "time", time.Now(), "\n")
		case msg2 := <-c2:
			fmt.Println("mesage is:", msg2, "time", time.Now(), "\n")
		default:
			//fmt.Println("Ожидание сообщений", "time", time.Now())
		}
	}
}

func send(ch chan string, msg string) {
	i := 0
	for i < 10 {
		ch <- msg
		time.Sleep(30)
		i++
	}
}


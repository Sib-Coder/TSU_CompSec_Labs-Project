package main

import (
	"fmt"
	"math"
	"math/rand"
	"strconv"
)

type BF struct {
	n  int
	nw int
	f  []uint32
}

func NewBF(vars, typeVal int) *BF {
	bf := &BF{n: vars}
	if bf.n <= 5 {
		bf.nw = 1
	} else {
		bf.nw = 1 << (bf.n - 5)
	}
	bf.f = make([]uint32, bf.nw)
	if typeVal == 0 {
		for i := 0; i < bf.nw; i++ {
			bf.f[i] = 0
		}
	} else if typeVal == 1 {
		if bf.n <= 4 {
			bf.f[0] = (1 << (1 << bf.n)) - 1
		} else {
			for i := 0; i < bf.nw; i++ {
				bf.f[i] = ^uint32(0)
			}
		}
	} else if typeVal == 2 {
		for i := 0; i < bf.nw; i++ {
			bf.f[i] = uint32(rand.Int())<<1 ^ uint32(rand.Int())
		}
		if bf.n < 5 {
			bf.f[0] &= (1 << (1 << bf.n)) - 1
		}
	} else {
		panic("Invalid type.")
	}
	return bf
}

func NewBFFromString(binaryArray string) *BF {
	len := len(binaryArray)
	if len > 0 && len&(len-1) != 0 {
		panic("Invalid string length.")
	}
	n := int(math.Log2(float64(len)))
	bf := &BF{n: n}
	if bf.n <= 5 {
		bf.nw = 1
	} else {
		bf.nw = 1 << (bf.n - 5)
	}
	bf.f = make([]uint32, bf.nw)
	for i := 0; i < bf.nw; i++ {
		bf.f[i] = 0
		for j := 0; j < 32; j++ {
			if i*32+j < len && binaryArray[i*32+j] == '1' {
				bf.f[i] |= 1 << j
			}
		}
	}
	return bf
}

func (bf *BF) Equal(bFun *BF) bool {
	if bf.n != bFun.n {
		return false
	}
	for i := 0; i < bf.nw; i++ {
		if bf.f[i] != bFun.f[i] {
			fmt.Println(bf.f[i], bFun.f[i])
			return false
		}
	}
	return true
}
func (bf *BF) Weigth() int {
	w := 0
	var x uint32
	fmt.Println(bf.nw)
	for i := 0; i < bf.nw; i++ {
		x = bf.f[i]
		x = x - ((x >> 1) & 0x55555555) // ∧ - конънк
		x = (x & 0x33333333) + ((x >> 2) & 0x33333333)
		x = (x + (x >> 4)) & 0x0F0F0F0F
		x = x + (x >> 8)
		x = x + (x >> 16)

		w += int(x & 0x3F)
	}
	return w
}

func Halving_mask(i int) uint32 {
	var val uint32
	switch i {
	case 0:
		val = 0xAAAAAAAA
	case 1:
		val = 0xCCCCCCCC
	case 2:
		val = 0xF0F0F0F0
	case 3:
		val = 0xFF00FF00
	case 4:
		val = 0xFFFF0000
	default:
		// по умолчанию val останется нулевым
	}
	return val
}

func (bf *BF) MU() *BF { // проходит тесты , но работает плохо
	g := bf
	var iterator int
	if bf.n <= 5 {
		iterator = bf.n
	} else {
		iterator = 5
	}
	for i := 0; i < bf.nw; i++ {
		for j := 0; j < iterator; j++ {
			g.f[i] ^= ((g.f[i] << (1 << j)) & (Halving_mask(j)))
		}
	}
	for k := 1; k < bf.nw; k <<= 1 {
		for j := 0; j < bf.nw; j += k << 1 {
			for s := j; s < j+k; s++ {
				g.f[s+k] ^= g.f[s]
			}
		}
	}
	return g
}

func TestMU() {
	for n := 1; n < 30; n++ {
		a := NewBF(n, 2)
		tester := a.MU()
		tester2 := tester.MU()
		if a == tester2 {
			fmt.Println(a.Equal(tester2))
		} else {
			fmt.Println("Error")
			return
		}

	}
}

func (bf *BF) ANF() string {
	//mobius := bf.MU()
	//mobius := bf.Mebius()
	//mobius := constr_Copy(bf)
	mobius := constr_Copy(bf).MU()

	if mobius.Weigth() == 0 {
		return "0"
	}

	anf_str := ""
	if mobius.f[0]&1 == 1 { //посмотри
		anf_str += "1"
	}
	for args := 1; args < (1 << bf.n); args++ {
		if (mobius.f[int(args>>5)]>>(args&31))&1 == 1 { //посмотри
			if anf_str != "" {
				anf_str += " + "
			}
			for i := bf.n - 1; i > -1; i-- {
				if (args>>i)&1 == 1 {
					anf_str += "x" + strconv.Itoa(bf.n-i)
				}
			}
		}
	}
	return anf_str
}

func (bf *BF) Deg() int {
	//mobius := bf.MU()
	//mobius := bf.Mebius()
	mobius := constr_Copy(bf).MU()

	if ((mobius.f[bf.nw-1])>>(((1<<bf.n)-1)&31))&1 == 1 {
		return bf.n
	}
	deg := 0
	for args := ((1 << bf.n) - 1); args > -1; args-- {
		if (mobius.f[args>>5]>>(args&31))&1 == 1 {
			bits_val := bits(args)
			if int(bits_val) > deg {
				deg = int(bits_val)
			}
		}
	}

	return deg
}

func bits(n int) uint {
	var bits_count uint = 0
	for n != 0 {
		n = n & (n - 1)
		bits_count++
	}
	return bits_count
}

func constr_Copy(bf *BF) *BF {
	newBF := &BF{}

	newBF.n = bf.n
	newBF.nw = bf.nw

	newBF.f = make([]uint32, bf.nw)

	for i := 0; i < bf.nw; i++ {
		newBF.f[i] = bf.f[i]
	}

	return newBF
}
func main() {
	//TestMU()
	bf3 := NewBFFromString("01010011")
	//bf3 := NewBFFromString("00000000")

	mobius := constr_Copy(bf3).MU()
	fmt.Println(mobius)
	fmt.Println(bf3.ANF())
	fmt.Println(bf3.Deg())
}

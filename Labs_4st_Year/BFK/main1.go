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
	//fmt.Println(bf.nw)
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
// Balanced проверяет уравновешенность булевой функции
func (bf *BF) Balanced() bool {
    // Подсчитаем вес (количество единиц)
    weight := bf.Weigth()

    // Общее количество значений: 2^n
    total := 1 << bf.n

    // Функция уравновешена, если количество единиц равно половине общего количества значений
    return weight == total/2
}

func (bf *BF) MU() *BF {
	g := bf
	var iterator int
	if bf.n <= 5 {
		iterator = bf.n
	} else {
		iterator = 5
	}
	//преобразуем по известным нам маскам
	for i := 0; i < bf.nw; i++ {
		for j := 0; j < iterator; j++ {
			g.f[i] ^= ((g.f[i] << (1 << j)) & (Halving_mask(j)))
		}
	}
	//перобразуем по большим исходя из таблицы в учебнике
	for k := 41; k < bf.nw; k <<= 1 {
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
		tester := constr_Copy(a).MU()
		tester2 := constr_Copy(tester).MU()
		if a.Equal(tester2) {
			fmt.Println(a.Equal(tester2))
		} else {
			fmt.Println("Error")
			return
		}

	}
}

// из результатов мёбиуса смотрим где у нас единицы и переписываем члены (x1 x2 ...)
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

// исходя из АНФ смотрим на её результат и ищём самый большой номер строки (так как номер == заполненность элементов)
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

func DegProbNOT(bf BF) int {
	mobius := bf.MU()
	//mobius := bf.Mebius()
	//mobius := constr_Copy(bf).MU()

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
func (bf *BF) Walsh_Hadamard() []int {
	cf := make([]int, 1<<bf.n) //размер результата
	var mask, size_j uint32 = 1, 0

	if bf.n > 5 { // для того чтобы чтобы определить кочичество бит в ячейки если количество перменных меньше  или равно 5(4. 8. 16. 32), а если перменных больше 5 то бит в ячейки всегда 32
		size_j = 32
	} else {
		size_j = 1 << bf.n
	}

	for i := uint32(0); i < uint32(bf.nw); i++ {
		for j := uint32(0); j < size_j; j++ {
			if bf.f[i]&mask == 0 {
				cf[j+i*32] = 1
				//j - это номер бита в этой ячейке
				//count - номер ячейки содержашей 32 бита
				//если 0т то пишем 1
			} else {
				cf[j+i*32] = -1
				//если 1 т то пишем -1
			}
			mask = mask << 1
		}
		mask = 1
	}

	step := 1
	// пробегаемся и подсчитываем вектор суммируем и разность
	for step < len(cf) {
		for i := 0; i < len(cf); i += step * 2 {
			for j := i; j < i+step; j++ {
				a := cf[j]
				b := cf[j+step]
				cf[j] = a + b
				cf[j+step] = a - b
			}
		}
		step *= 2
	}
	// fmt.Println(cf, len(cf))
	return cf
}
func (bf *BF) cor() int {
	walsh_hadamard := constr_Copy(bf).Walsh_Hadamard()
	var res int = 0
	for k := 1; k < bf.n+1; k++ { //k это вес
		a := ((1 << k) - 1) << (bf.n - k) //начальный вектор
		end := ((1 << k) - 1)             //конечный вектор

		for a != end {
			if walsh_hadamard[a] != 0 {
				return res
			}
			b := (a + 1) & a //3 сочетания из книги
			c := bits((b-1)^a) - 2
			a = (((((a + 1) ^ a) << 1) + 1) << c) ^ b
		}
		if walsh_hadamard[a] != 0 {
			return res
		}
		res++
	}
	return res
}

func (bf *BF) NF() int { //нелинейность функции 34 страница
	F := constr_Copy(bf).Walsh_Hadamard()
	//fmt.Println("wa: ", F)

	maxAbs := 0
	for _, val := range F {
		absVal := int(math.Abs(float64(val))) //взятие по модулю

		if absVal > maxAbs { //поиск максимального
			maxAbs = absVal
		}
	}
	return (1 << (bf.n - 1)) - (maxAbs / 2) //формула из книжки на странице 34

}

func (bf *BF) BAA() {
	F := constr_Copy(bf).Walsh_Hadamard()
	fmt.Println("wa: ", F)

	maxAbs := 0
	flag := false
	id := 0

	for i := 1; i < (1 << bf.n); i++ {
		if int(math.Abs(float64(F[i]))) > maxAbs {
			maxAbs = int(math.Abs(float64(F[i])))
			if F[i] < 0 {
				flag = true
			} else {
				flag = false
			}
			id = i
		}
	}
	baa_str := ""
	if flag {
		baa_str += "1"
	}
	for i := bf.n - 1; i > -1; i-- {
		if (id>>i)&1 != 0 {
			if baa_str != "" {
				baa_str += " + "
			}
			baa_str += "x" + strconv.Itoa(bf.n-i)
		}
	}

	fmt.Println("|f^(a)|: ", maxAbs)
	fmt.Println(baa_str)

}

func (bf * BF) Autocor() []int{
	vul := 1<<bf.n
	F := constr_Copy(bf).Walsh_Hadamard()

	for  i := 0; i < vul; i++ { 
	 F[i] *= F[i]; 
	} 

	for i:=1;i<vul;i<<=1{
		for j:=i; j<vul;j +=(i<<1){
			for k:=j;k<j+i;k++{
				var buf int
				buf = F[k-i]+F[k]
				F[k]= F[k - i] - F[k]
				F[k-i]=buf

			}
		}
	}
	for  i := 0; i < vul; i++ { 
	F[i] >>= bf.n 
	} 
	return F 
}

func (bf *BF) CN_f()int{
	f := constr_Copy(bf).Walsh_Hadamard()
	max := int(math.Abs(float64(f[1])))
	for i := 1; i < 1<<bf.n; i++ { 
	ab := int(math.Abs(float64(f[i]))) 
	 if ab > max { max = ab} 
	} 
	CNf := (1 << (bf.n - 2)) - (max>>2); 
	fmt.Println("cn_f", CNf) 
	return CNf
}
// DummyVars возвращает список фиктивных переменных (незначимых для функции)
func (bf *BF) DummyVars() []int {
    dummyVars := []int{}
    
    // Проходим по каждой переменной x_i
    for varIndex := 0; varIndex < bf.n; varIndex++ {
        isDummy := true
        
        // Проверяем все возможные наборы значений переменных
        for mask := 0; mask < (1 << bf.n); mask++ {
            // Два значения функции для одинаковых наборов переменных, но с разными значениями x_i
            originalValue := (bf.f[mask>>5] >> (mask & 31)) & 1
            toggledMask := mask ^ (1 << varIndex)
            toggledValue := (bf.f[toggledMask>>5] >> (toggledMask & 31)) & 1
            
            // Если при изменении x_i значение функции изменяется, переменная не фиктивная
            if originalValue != toggledValue {
                isDummy = false
                break
            }
        }
        
        // Если переменная фиктивная, добавляем её в список
        if isDummy {
            dummyVars = append(dummyVars, varIndex+1) // Нумерация переменных от 1
        }
    }
    
    return dummyVars
}

// SAC проверяет выполнение строгого лавинного критерия для булевой функции
func (bf *BF) SAC() bool {
    // Общее количество наборов переменных
    totalCombinations := 1 << bf.n
    expectedFlips := totalCombinations / 2  // Ожидаемое количество изменений функции при изменении переменной
    
    // Для каждой переменной проверяем лавинный эффект
    for varIndex := 0; varIndex < bf.n; varIndex++ {
        flips := 0 // Считаем количество изменений функции при изменении переменной varIndex
        
        // Проходим по всем возможным входным наборам
        for mask := 0; mask < totalCombinations; mask++ {
            originalValue := (bf.f[mask>>5] >> (mask & 31)) & 1
            toggledMask := mask ^ (1 << varIndex) // Изменяем только одну переменную varIndex
            toggledValue := (bf.f[toggledMask>>5] >> (toggledMask & 31)) & 1
            
            // Если значение функции изменилось, увеличиваем счетчик изменений
            if originalValue != toggledValue {
                flips++
            }
        }
        
        // Если количество изменений не равно половине общего количества входных наборов, SAC нарушен
        if flips != expectedFlips {
            return false
        }
    }
    
    // Если для всех переменных лавинный критерий выполнен, возвращаем true
    return true
}


func main() {
	//TestMU()
	//var input string
	//fmt.Println("vector:  ")
	//fmt.Scanln(&input)
	//bf3 := NewBFFromString(input)
	//mobius := constr_Copy(bf3).MU()
	// fmt.Println(bf3.Walsh_Hadamard())

	bf3 := NewBFFromString("1001110110010010")
	fmt.Println("Степень функции: ",bf3.Deg())
	fmt.Println("Кореляционно имуммунность: ",bf3.cor())
	fmt.Println("Нелинейность: ", bf3.NF())
	fmt.Println("Наличие фиктивных переменных: ", bf3.DummyVars())

	// Проверка на уравновешенность
    if bf3.Balanced() {
        fmt.Println("Функция уравновешена.")
    } else {
        fmt.Println("Функция не уравновешена.")
    }
	fmt.Println("Строгий лавинный критерий: ", bf3.SAC())
	//fmt.Println(bf3.ANF())
	//bf3.BAA()


}

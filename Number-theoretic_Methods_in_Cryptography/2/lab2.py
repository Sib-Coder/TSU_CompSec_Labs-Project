import time

def algor(x, y):#справа налево
    z = x
    for i in range(y.bit_length() - 2, -1, -1):
        z = z ** 2
        if (y >> i) & 1:
            z *= x #вот тут разница  
    return z


def standart(x,y):
    res = 1
    for i in range(0,y):
        res *= x
    return res

def test(x,y):
    start = time.time_ns()
    result_1 = algor(x, y)
    print(f'{time.time_ns() - start} ns')
    
    start = time.time_ns()
    result_2 = standart(x, y)
    print(f'{time.time_ns() - start} ns')
    
    if (result_1  == result_2):
        print('Result Normal')
    else:
        print('Result not Normal')


if __name__ == '__main__':
    x = int(input("Введите x:  "))
    y = int(input("Введите y:  "))
    test(x, y)

   
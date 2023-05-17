import random

#функция Эйлера
def fi(n):
    f = n;
    if n%2 == 0:
        while n%2 == 0:
            n = n // 2;
        f = f // 2;
    i = 3
    while i*i <= n:
        if n%i == 0:
            while n%i == 0:
                n = n // i;
            f = f // i;
            f = f * (i-1);
        i = i + 2;
    if n > 1:
        f = f // n;
        f = f * (n-1);
    return f;

def error_f(n,t):
    i = (fi(n)/n)**t
    print(f'Вероятность ошибки = {i}')

def test_ferma(n, t):
    for i in range(1,t):
        a = random.randint(2, n-2)
        #r = (a**(n-1))%n
        r = pow(a,n-1,n)
        if r != 1:
            return 1


def wrapper_test_ferma(n,t):
    if n <= 3:
        print("Число не подходит под условия\n")
    else:

        res = test_ferma(n, t)
        if res == 1:
            print("составное")
        else:
            print("простое")
            #error_f(n, t)

def test():
    test_data=[ 2, 3, 5, 7, 11, 1, 9, 10, 12, 14, 1, 561, 8911, 10585, 15841, 29341, 41041]
    t = 12
    #после измениения параметра надёжности выше 3 последние 2 числа Кармайкла определяются
    for i in test_data:
        wrapper_test_ferma(i, t)


def main():
    print("Hello Ferma Test")
    #n = int(input("Введите число для проверки "))
    #t = int(input("Введите параметр надёжности "))
    #print(n, t)
    wrapper_test_ferma(348251240609926627320927902551,5)
    #test()

if __name__ == "__main__":
    main()

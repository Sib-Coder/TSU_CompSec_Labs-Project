import random
def test_ferma(n, t):
    for i in range(1,t):
        a = random.randint(2, n-2)
        #r = (a**(n-1))%n
        r = pow(a,n-1,n)
        if r != 1:
            return 1


def main():
    print("Hello Ferma Test")
    n = int(input("Введите число для проверки "))
    t = int(input("Введите параметр надёжности "))
    #print(n, t)
    if n < 3:
        print("Число не подходит под условия")
    else:
        res = test_ferma(n, t)
        if res == 1:
            print("составное")
        else:
            print("простое")


if __name__ == "__main__":
    main()

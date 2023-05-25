import random


def TestMillerRabin(n, t):
    if n <= 3:
        print("Число не подходит под условия")
        return None
    r = n - 1
    s = 0
    while r % 2 == 0:
        r //= 2
        s += 1
    b = 1
    for _ in range(t):
        b = random.randint(2, n-2)
        y = pow(b, r, n)
        if y != 1 and y != (n - 1):

            j = 1
            while j < s and y != n - 1:
                y = pow(y, 2, n)
                if y == 1:
                    return False
                j += 1
            if y != n - 1:
                return False
    return True

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
    i = (fi(n) / (4 * n)) ** t
    return i

def test():
    test_data=[ 2, 3, 5, 7, 11, 1, 9, 10, 12, 14, 1, 561, 8911, 10585, 15841, 29341, 41041, 59283834566841846300814233552512955601, 9904788899632347103]
    t = 2

    for i in test_data:
        res = TestMillerRabin(int(i), int(t))
        if res == True:
            print(f"Число {i} простое. Вероятность ошибки = {error_f(i,t)}.")
        elif res == False:
            print(f"Число {i} составное.")
        


def main():
    test()

if __name__ == "__main__":
    main()
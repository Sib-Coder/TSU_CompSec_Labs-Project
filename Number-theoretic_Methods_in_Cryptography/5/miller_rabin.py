import random
from sympy import totient, nextprime, randprime
from decimal import *


def error_f(n,t):
    i = (Decimal(totient(n)) / (4 * Decimal(n))) ** Decimal(t)
    return i

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


def test():
    test_data=[2, 3, 5, 7, 11, 1, 9, 10, 12, 14]

    for _ in range(50):
        n = randprime(1000000, 9999999999999999999)
        if random.randint(0, 1) == 1:
            n *= randprime(1000000, 9999999999999999999)
        test_data.append(n)
    
    test_data.append(26641259752490421121)
    test_data.append(6553130926752006031481761)
    

    t = 5

    for i in test_data:
        res = TestMillerRabin(i, t)
        if res == True:
            print(f"Число {i} простое. Вероятность ошибки = {error_f(i, t)}.")
        elif res == False:
            print(f"Число {i} составное.")
        


def main():
    test()

if __name__ == "__main__":
    main()
from Crypto.Util import number
import random

def gordon_method():
    s = number.getPrime(128)
    t = number.getPrime(128)
    i = random.randint(1, 100)
    r = 2*i*t + 1
    while not number.isPrime(r):
        i += 1
        r = 2*i*t + 1
    p_0 = 2 * pow(s, r-2, r) * s - 1

    j = random.randint(1, 100)
    p = 2*j*r*s + p_0
    while not number.isPrime(p):
        j += 1
        p = 2*j*r*s + p_0
    return p

def main():
    print(gordon_method())

if __name__ == "__main__":
    main()
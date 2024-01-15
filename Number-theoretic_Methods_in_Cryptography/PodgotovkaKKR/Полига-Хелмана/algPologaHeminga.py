import math 


def egcd(a, b):
    if a == 0:
        return (b, 0, 1)
    else:
        g, x, y = egcd(b % a, a)
        return (g, y - (b // a) * x, x)
 
def reversed_in_pole(b, n):
    g, x, _ = egcd(b, n)
    if g == 1:
        return x % n
        

def prime_factors(num): 
    listfactors=[]
    while num % 2 == 0:  
        listfactors.append(2)
        num = num / 2 
    for i in range(3, int(math.sqrt(num)) + 1, 2): 
        while num % i == 0: 
            listfactors.append(i)
            num = num / i 
    if num > 2: 
        listfactors.append(int(num))
    return listfactors

def create_table(n, g, p, num_mod):
    #убрал g заменив на 2 так чтобы считалось как в примере Пахомовой
    # надо 2 в строке ниже заменить на g - тогда будет ок считать
    a = (g **(int(n/p)))%num_mod
    print(f"a = {a}")
    print(f"p = {p}")
    print("Table Params: ")
    # словарь для значений
    listJY ={}
    for j in range(0,p):
        print(f" J: {j} , Y: {(a**j)%num_mod} mod {num_mod} ")
        listJY[j]=(a**j)%num_mod

    print("\nПроверь что степень p = 1!!!")
    #Поиск J 
    res = counting_degree_1(g,n,p,num_mod)
    keys = [key for key in listJY if listJY[key] == res]
    print("Значение J:", keys)
    print(f"!!! x ={keys} mod {p} !!! обрати внивание на степень p")


def counting_degree_1(a,n,p,num_mod):
    b0 = a**(int(n/p))%num_mod
    print(f"b0 =a^n/p mod {num_mod} = {b0} mod {num_mod}")
    return b0


def Chinese_theorem():
    a1 = int(input("Введите a1: "))
    m1 = int(input("Введите m1: "))

    a2 = int(input("Введите a2: "))
    m2 = int(input("Введите m2: "))

    # a3 = int(input("Введите a3: "))
    # m3 = int(input("Введите m3: "))

    M = m1*m2
    print(f"M = {M} \n M_1 = {int(M/m1)} \n M_2 = {int(M/m2)} ")
    z1 = counting_z(M,m1, a1)
    z2 = counting_z(M,m2, a2)
    # z3 = counting_z(M,m3)
    print(int(M/m1)*z1*a1)
    print(int(M/m2)*z2*a2)
    resAll = (int(M/m1)*z1*a1 + int(M/m2)*z2*a2) % M
    print(f"Ответ Итоговый:{resAll} mod {M}")



def counting_z(M, mi, ai):
    M_i=int(M/mi)

    # print(M_i)
    # print(mi)
    print(reversed_in_pole(M_i,mi))
    
    zi = (ai * reversed_in_pole(M_i, mi))%mi

    print (f"Zi = {zi}")
    return zi


def main():
    n = int (input("Введите n: "))
    g = int (input("Введите g: "))
    num_mod= n
    n -=1
    print(f"N = {n}")
    print(f"Разложение по множителям {prime_factors(n)} \n")
    list_factor = set(prime_factors(n))
    for i in list_factor:
        print(f"new table for new p {i}")
        create_table(n, g, i, num_mod)
        print("\n")

    print("На этом этапе проверьте все степени p чтобы не было ошибок и если надо пересчитайте)")
    Chinese_theorem()




if __name__=="__main__":
    main()

    # print(reversed_in_pole(49, 4))
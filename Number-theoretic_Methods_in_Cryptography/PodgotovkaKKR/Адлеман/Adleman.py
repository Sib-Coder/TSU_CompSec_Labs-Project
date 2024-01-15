FB=[2,3,5]
log_osn= 5
os_group=73

def primfacs(n):
   i = 2
   primfac = []
   while i * i <= n:
       while n % i == 0:
           primfac.append(i)
           n = n / i
       i = i + 1
   if n > 1:
       primfac.append(n)
   return primfac

def main():
    k =1
    while k <12:
        number=(log_osn**k)%os_group
        print("k = ",k,"res= ",number, "razlog= ", primfacs(number))
        k+=1

main()
print(primfacs(24))
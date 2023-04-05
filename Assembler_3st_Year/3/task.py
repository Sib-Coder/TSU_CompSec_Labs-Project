n = int(input())
q = 2
while (q**3) <= n:
    if (n%(q**2)==0 and n%(q**3)!=0):
        print(q)
    else: print("not namber")
    q+=1

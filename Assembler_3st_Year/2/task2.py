sib = int(input())
sot = int(sib / 100)
des = int((sib % 100) / 10)
ed = sib % 10

#print(f"sot {sot}, des {des}, ed {ed}")

if sot == des:
    print("True")
elif sot == ed:
    print("True")
elif des == ed:
    print("True")
else:
    print("False")

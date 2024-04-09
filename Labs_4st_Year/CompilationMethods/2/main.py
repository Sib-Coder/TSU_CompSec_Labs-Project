from algorithm import algorithm


def test():
    mas_test = ["!a+b!", "!a*b!","!(a+b)*(b+a)!", "!b*a+a*b!", "!(a+b)*a+b*a!", "!(a+b*a)*(b*b+a*(a+b+a))!", "!a+*b!", "a+b*a+b","a!b", "!a(b+a()!"]
    for i in mas_test:
        print("String: ",i)
        print("Result: ",algorithm(i))
        print("-----------------------------------------------------------------------------------------------------------------------------------")

def unicumString():
    i = input("Give String: ")
    print("String: ",i)
    print("Result: ",algorithm(i))
    print("-----------------------------------------------------------------------------------------------------------------------------------")

def main():
    test()
    #unicumString()

if __name__=="__main__":
    main()
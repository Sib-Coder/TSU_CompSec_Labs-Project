Alt = {# правила грамматики
    "A1": "!B!",
    "B1": "T",
    "B2": "T+B",
    "T1": "M",
    "T2": "M*T",
    "M1": "a",
    "M2": "b",
    "M3": "(B)",
}
Alt_idx = {#номерация правил
    "A1": "1",
    "B1": "2",
    "B2": "3",
    "T1": "4",
    "T2": "5",
    "M1": "6",
    "M2": "7",
    "M3": "8",
}
#допустимые символы 
T = ["a", "b", "(", ")", "!", "+", "*"]

def process_state_q(res, l1, l2, i, n, state):
    if l2[0] in T:
        if l2[0] == res[i]:
            l1.append(l2[0])
            l2 = l2[1:]
            i += 1
            if i == n:
                if len(l2) == 0:
                    state = "t"
                else:
                    state = "b"
            else:
                if len(l2) == 0:
                    state = "b"
        else:
            state = "b"
    else:
        alt_l1 = l2[0] + "1"
        l1.append(alt_l1)
        l2 = l2.replace(alt_l1[0], Alt.get(alt_l1), 1)
    return l1, l2, i, state

def process_state_b(res, l1, l2, i, state):
    if l1[len(l1) - 1] in T:
        l2 = l1[len(l1) - 1] + l2
        l1 = l1[: len(l1) - 1]
        i -= 1
    else:
        alt_idx_l1 = l1[len(l1) - 1]
        new_alt_idx_l1 = alt_idx_l1[0] + chr(ord(alt_idx_l1[1]) + 1)
        if Alt.get(new_alt_idx_l1) != None:
            l1 = l1[: len(l1) - 1]
            l1.append(new_alt_idx_l1)
            l2 = l2.replace(Alt.get(alt_idx_l1), Alt.get(new_alt_idx_l1), 1)
            state = "q"
        else:
            if (new_alt_idx_l1 == "A2") and (i == 0):
                return l1, l2, i, "break"
            l2 = l2.replace(Alt.get(alt_idx_l1), alt_idx_l1[0], 1)
            l1 = l1[: len(l1) - 1]
    return l1, l2, i, state

def process_state_t(l1):
    res_res = ""
    for x in l1:
        if Alt_idx.get(x) != None:
            res_res += " " + Alt_idx.get(x)
    return res_res

def start_work(res):
    l1 = []
    l2 = str("A")
    res_res = ""
    n = len(res)
    i = 0
    state = "q"
    while True:
        if state == "q":
            l1, l2, i, state = process_state_q(res, l1, l2, i, n, state)
        elif state == "b":
            l1, l2, i, state = process_state_b(res, l1, l2, i, state)
            if state == "break":
                break
        elif state == "t":
            res_res = process_state_t(l1)
            break
    result_deteils(res_res)

def result_deteils(res_res):
    #вывод последовательности построения грамматики
    if res_res != "":
        res_res = res_res[1:]
        print("Нисходящий: ",res_res)
    else:
        print("Введенная строка не может быть выведена с помощью граматики")    

def test():
    mas_test = ["!a+b!", "!a*b!","!(a+b)*(b+a)!", "!b*a+a*b!", "!(a+b)*a+b*a!", "!(a+b*a)*(b*b+a*(a+b+a))!", "!a+*b!", "a+b*a+b","a!b", "!a(b+a()!"]
    for i in mas_test:
        print(i)
        start_work(i)

def main():
    string=input('Введите строку: ')
    start_work(string)
    

if __name__=="__main__":
    test()
    #main()
import os
global write_bit
global bit_len
write_bit = 0
bit_len = 8


def indexForSymbol(sin, irgum):
    j = 0
    for i in sin:
        if irgum == i:
            return j + 2
        j += 1
    print("Developer is Idiot")


def outPutBit(bit, outputfile):
    global write_bit
    global bit_len
    write_bit >>= 1
    if bit & 1:
        write_bit |= 0x80
    bit_len -= 1
    #print(bit_len)
    if bit_len == 0:
        bit_len = 8
        outputfile.write(write_bit.to_bytes(1, "little"))


def bitPlusFollow(bit, bittofollow, outputfile):
    outPutBit(bit, outputfile)
    for _ in range(bittofollow):
        outPutBit(~bit, outputfile)

#читаем из нашего файла данные и работаем с ними
sum_slovar = 0
with open('in.txt', 'r') as fp:
    test_sum = 0
    chunk = fp.read(1)
    slovar = {}
    while chunk:
        test_sum += 1
        if slovar.get(chunk) == None:
            slovar.update({chunk: 1})
        else:
            #
            slovar[chunk] = slovar[chunk] + 1

        chunk = fp.read(1)
        # print(chunk)
    # print(slovar)

    for _, val in slovar.items():
        sum_slovar = sum_slovar + val
    if test_sum == sum_slovar:
        print("Ok")
    else:
        print("not Ok")
#sorted_slovar содержит нашу шапку
sorted_slovar = dict(sorted(slovar.items(), key=lambda item: item[1], reverse=True))

#slovar_mas массив нужный в нашем алгоритме ( массив накоплений)
slovar_mas = [0, 1]
for i in sorted_slovar:
    slovar_mas.append(sorted_slovar[i] + slovar_mas[-1])

# заносим шапку
f = open("out.txt", "wb+")
print(len(sorted_slovar))
f.write(len(sorted_slovar).to_bytes(1, "little"))
for i in sorted_slovar:
    f.write(i.encode("ascii"))
    f.write(sorted_slovar[i].to_bytes(4, "little"))
print(sorted_slovar)
# алгоритм кодирования
with open('in.txt', 'r') as fp:
    low_v = 0
    high_v = (1<<16)-1  # 2^16 интервал
    delete = slovar_mas[-1]
    diff = high_v - low_v + 1
    first_q = int(int(high_v + 1) / 4)
    half_q = first_q * 2
    third_q = first_q * 3
    bit_to_follow = 0

    chip = fp.read(1)
    while chip:
        j = indexForSymbol(sorted_slovar, chip)
        high_v = int(low_v + slovar_mas[j] * diff / delete - 1)
        low_v = int(low_v + slovar_mas[j - 1] * diff / delete)

        while True:
            if high_v < half_q:
                bitPlusFollow(0, bit_to_follow, f)
                bit_to_follow=0
            elif low_v >= half_q:
                bitPlusFollow(1, bit_to_follow, f)
                bit_to_follow=0
                low_v -= half_q
                high_v -= half_q
            elif low_v >= first_q and high_v < third_q:
                bit_to_follow += 1
                low_v -= first_q
                high_v -= first_q
            else:
                break
            low_v += low_v
            high_v += high_v + 1

        diff = high_v - low_v + 1
        chip = fp.read(1)

    high_v = int(low_v + slovar_mas[1] * diff / delete - 1)
    low_v = int(low_v + slovar_mas[0] * diff / delete)

    while True:
        if high_v < half_q:
            bitPlusFollow(0, bit_to_follow, f)
            bit_to_follow=0
        elif low_v >= half_q:
            bitPlusFollow(1, bit_to_follow, f)
            bit_to_follow=0
            low_v -= half_q
            high_v -= half_q
        elif low_v >= first_q and high_v < third_q:
            bit_to_follow += 1
            low_v -= first_q
            high_v -= first_q
        else:
            break
        low_v += low_v
        high_v += high_v + 1
    bit_to_follow += 1
    if low_v < first_q:
        bitPlusFollow(0, bit_to_follow, f)
        bit_to_follow=0
    else:
        bitPlusFollow(1, bit_to_follow, f)
        bit_to_follow=0

    write_bit >>= bit_len
    f.write(write_bit.to_bytes(1, "little"))

f.close()
#подсчёт сжатия
sid = os.stat("in.txt").st_size
sib = os.stat("out.txt").st_size

print(f"szatie= {(sib/sid)*100}%")
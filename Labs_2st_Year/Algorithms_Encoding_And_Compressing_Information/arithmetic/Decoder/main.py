global read_bit
global bit_len
global garbage_bit
read_bit = 0
bit_len = 0
garbage_bit = 0


def inPutBit(input_file):  # читаем бит
    global read_bit
    global bit_len
    global garbage_bit
    if bit_len == 0:
        sid_bit = input_file.read(1)
        read_bit = int.from_bytes(sid_bit, "little")
        if sid_bit == b"":
            garbage_bit += 1
            read_bit = 255
            if garbage_bit > 14:
                print("Developer is Idiot")
                exit(1)
        bit_len = 8

    t = read_bit & 1
    read_bit >>= 1
    bit_len -= 1
    return t


with open("out.txt", "rb") as file_in:
    #считываем шапку
    chunk = ord(file_in.read(1))
    # print(chunk)
    rasp_slovar = {}
    for i in range(chunk):
        key_hat = file_in.read(1).decode('ascii')
        #print(key_hat)
        val_hat = int.from_bytes(file_in.read(4), "little")
        #print(val_hat)
        rasp_slovar[key_hat] = val_hat
    # print(rasp_slovar)
    #делаем алгоритмический массив
    slovar_mas = [0, 1]
    for i in rasp_slovar:
        slovar_mas.append(rasp_slovar[i] + slovar_mas[-1])
    # print(slovar_mas)

    #алгоритм раскодирования
    with open("out_final.txt", "wb+") as file_out:
        low_v = 0
        high_v = (1 << 16) - 1  # 2^16
        delete = slovar_mas[-1]
        diff = high_v - low_v + 1
        first_q = int(int(high_v + 1) / 4)
        half_q = first_q * 2
        third_q = first_q * 3
        val = 0

        for i in range(16):
            k = inPutBit(file_in)
            val += val + k
        while True:
            freq = int(((val - low_v + 1) * delete - 1) / diff)
            j = 1
            while slovar_mas[j] <= freq:
                j += 1
            high_v = int(low_v + slovar_mas[j] * diff / delete - 1)
            low_v = int(low_v + slovar_mas[j - 1] * diff / delete)

            while True:
                if high_v < half_q:
                    pass
                elif low_v >= half_q:
                    low_v -= half_q
                    high_v -= half_q
                    val -= half_q
                elif low_v >= first_q and high_v < third_q:
                    low_v -= first_q
                    high_v -= first_q
                    val -= first_q
                else:
                    break
                low_v += low_v
                high_v += high_v + 1
                k = inPutBit(file_in)
                val += val + k
            if j == 1:
                break
            file_out.write(list(rasp_slovar.keys())[j - 2].encode('ascii'))
            diff = high_v - low_v + 1

with open("in.txt","rb") as test:
    sin=test.read()
with open("out_final.txt","rb") as test_o:
    sib=test_o.read()
if sin == sib :
    print("Billi Harrington is Alive")
else: print("gachi mems")
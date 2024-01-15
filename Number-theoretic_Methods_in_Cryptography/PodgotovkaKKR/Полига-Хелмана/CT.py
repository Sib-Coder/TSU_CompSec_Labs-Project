import math
def chinese_remainder_theorem(congruences):
    # Проверка, что все модули в системе сравнений взаимно просты
    for i in range(len(congruences)):
        for j in range(i + 1, len(congruences)):
            if math.gcd(congruences[i][1], congruences[j][1]) != 1:
                raise ValueError("Модули должны быть взаимно простыми")

    # Решение системы сравнений с помощью Китайской теоремы об остатках
    N = 1
    for _, modulus in congruences:
        N *= modulus

    result = 0
    for a, modulus in congruences:
        Ni = N // modulus
        Mi = pow(Ni, -1, modulus)
        result += a * Ni * Mi

    return result % N

# Пример использования
#congruences = [(2, 3), (3, 5), (2, 7)]  # Замените на вашу систему сравнений 1 число - остаток, 2 - модуль
congruences = [(1, 4), (1, 3), (4, 5)]#x=1mod4; x=1mod3;x=4mod5
solution = chinese_remainder_theorem(congruences)
print(f"Решение системы сравнений: x = {solution}")

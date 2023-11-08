// Copyright 2022 Stormtrooperroman
#ifndef _HOME_LIDER_PROJECTS_NTINCRYPTO_BIGNUM_H_
#define _HOME_LIDER_PROJECTS_NTINCRYPTO_BIGNUM_H_

#include<bits/stdc++.h>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <string>

typedef unsigned short BASE;
typedef unsigned int DBASE;
#define BASE_SIZE sizeof(BASE)*8


using namespace std;


class BN {
 public:
    int len;
    int maxlen;
    BASE *coef;

    explicit BN(int ml = 1, int t = 0);
    BN(const BN&);
    ~BN() {
        if (coef){
            delete[] coef;
            coef = NULL;
        }
    };

    BN& operator = (const BN&);
    BN& operator = (const BASE&);

    bool operator == (const BN&);
    bool operator >= (const BN&);
    bool operator <= (const BN&);
    bool operator < (const BN&);
    bool operator > (const BN&);
    bool operator != (const BN&);

    BN operator + (const BN&);
    BN&  operator += (const BN&);
    BN operator - (const BN&);
    BN&  operator -= (const BN&);
    BN operator * (const BASE&);
    BN&  operator *= (const BASE&);
    BN  operator * (const BN&);
    BN&  operator *= (const BN&);
    BN operator / (const BASE&);
    BN operator % (const BASE&);
    BN operator / (const BN&);
    BN operator % (const BN&);

    void cout_base10();
    void cin_base10();

    BN square();
    BN pow_BN(int);
    BN pow_BN(BN);
    int log(int);
    BN root(int);
    bool isPrime(int);
    BN gcd(BN);

    friend BN operator*(BASE num, BN bNum) {  return bNum*num; }

    friend ostream& operator << (ostream &, const BN &);
    friend istream& operator >> (istream &, BN &);
};

BN::BN(int ml, int t){
    maxlen = ml;
    coef = new BASE[maxlen];
    len = 1;

    for (int i = 0; i < ml; i++) {
        coef[i] = 0;
    }

    if (t == 1) {
        len = ml;
        unsigned int b = BASE_SIZE;
        // srand(time(0));
        for (int i = 0; i < len; i++) {
            for (int j = 0; j * 12 < b; j++) {
                coef[i] = coef[i] << (j * 12) | rand();
            }
        }
        while (len > 1 && coef[len-1] == 0) {
            len--;
        }
    } else if (t != 0) {
        throw invalid_argument("Invalid arguments.");
    }
};

BN::BN(const BN& bNum){
    maxlen = bNum.maxlen;
    len = bNum.len;
    coef = new BASE[maxlen];
    for (int i = 0; i < maxlen; i++) {
        coef[i] = bNum.coef[i];
    }
};

BN& BN::operator = (const BN& bNum) {
    if (this != &bNum) {
        maxlen = bNum.maxlen;
        len = bNum.len;
        coef = new BASE[maxlen];
        for (int i = 0; i < maxlen; i++) {
            coef[i] = bNum.coef[i];
        }
    }
    return *this;
};

BN& BN::operator = (const BASE& num) {
    if (len == 1 && coef[0] != num) {
        delete[]coef;
        maxlen = 1;
        len = 1;
        coef = new BASE[maxlen];
        coef[0] = num;
    }
    return *this;
};

ostream& operator<<(ostream& out, const BN& bNum) {
    int b = BASE_SIZE;
    int k = b - 4;
    int j = bNum.len - 1;

    while (j > -1) {
        unsigned int tmp = (bNum.coef[j] >> k) & (0xf);

        if (0 <= tmp && tmp < 10) {
            out << static_cast<char>(tmp + '0');
        } else if (tmp > 9 && tmp < 16) {
            out << static_cast<char>(tmp - 10 + 'a');
        }
        k -= 4;
        // k = k - 4;
        if (k < 0) {
            k = b - 4;
            j--;
            out << " ";
        }
    }
    return out;
}

istream& operator >> (istream &in, BN & bNum) {
    char* s = new char[1000];
    int b = BASE_SIZE;
    int j = 0;
    int k = 0;
    unsigned int tmp = 0;

    in.getline(s, 1000);
    bNum.len = (strlen(s)-1)/(b/4)+1;
    bNum.maxlen = bNum.len;
    bNum.coef = new BASE[bNum.maxlen];
    for (int i = strlen(s) - 1; i > -1; i--) {
        if ('0' <= s[i] && s[i] <= '9') {
            tmp = s[i] - '0';
        } else if ('a' <= s[i] && s[i] <= 'f') {
            tmp = s[i] - 'a' + 10;
        } else if ('A' <= s[i] && s[i] <= 'F') {
            tmp = s[i] - 'A' + 10;
        } else {
            throw invalid_argument("Invalid arguments.");
        }

        bNum.coef[j] |= tmp << (k * 4);
        k++;
        if (k >= b / 4) {
            k = 0;
            j++;
        }
    }
    return in;
}

bool BN::operator==(const BN& bNum) {
    if (len != bNum.len) {
        return false;
    }

    for (int i = 0; i < len; i++) {
        if (coef[i] != bNum.coef[i]) {
            return false;
        }
    }
    return true;
}

bool BN::operator!=(const BN& bNum) {
    if (len != bNum.len) {
        return true;
    }

    for (int i = 0; i < len; i++) {
        if (coef[i] != bNum.coef[i]) {
            return true;
        }
    }
    return false;
}

bool BN::operator <(const BN& bNum) {
    if (len < bNum.len) {
        return true;
    } else if (len > bNum.len) {
        return false;
    }
    for (int i = len - 1; i > -1; i--) {
        if (coef[i] > bNum.coef[i]) {
            return false;
        } else if (coef[i] < bNum.coef[i]) {
            return true;
        }
    }
    return false;
}

bool BN::operator > (const BN& bNum) {
    if (len > bNum.len) {
        return true;
    } else if (len < bNum.len) {
        return false;
    }
    for (int i = len - 1; i > -1; i--) {
        if (coef[i] < bNum.coef[i]) {
            return false;
        } else if (coef[i] > bNum.coef[i]) {
            return true;
        }
    }
    return false;
}

bool BN::operator >= (const BN& bNum) {
    if (len > bNum.len) {
        return true;
    } else if (len < bNum.len) {
        return false;
    }
    for (int i = len - 1; i > -1; i--) {
        if (coef[i] < bNum.coef[i]) {
            return false;
        } else if (coef[i] > bNum.coef[i]) {
            return true;
        }
    }
    return true;
}

bool BN::operator <=(const BN& bNum) {
    if (len < bNum.len) {
        return true;
    } else if (len > bNum.len) {
        return false;
    }
    for (int i = len - 1; i > -1; i--) {
        if (coef[i] > bNum.coef[i]) {
            return false;
        } else if (coef[i] < bNum.coef[i]) {
            return true;
        }
    }
    return true;
}

BN BN::operator + (const BN& bNum) {
    int l = max(len, bNum.len) + 1;
    int t = min(len, bNum.len);
    BN newNum(l);
    DBASE tmp;
    int j = 0;
    int k = 0;
    int b = BASE_SIZE;
    while (j < t) {
        tmp = static_cast<DBASE>(coef[j]) +
        static_cast<DBASE>(bNum.coef[j]) + static_cast<DBASE>(k);
        newNum.coef[j] = static_cast<BASE>(tmp);
        k = static_cast<BASE>(tmp >> b);
        j++;
    }
    while (j < len) {
        tmp = coef[j] + k;
        newNum.coef[j] = static_cast<BASE>(tmp);
        k = static_cast<BASE>(tmp >> b);
        j++;
    }

    while (j < bNum.len) {
        tmp = static_cast<DBASE>(bNum.coef[j]) + static_cast<DBASE>(k);
        newNum.coef[j] = static_cast<BASE>(tmp);
        k = static_cast<BASE>(tmp >> b);
        j++;
    }
    newNum.coef[j] = k;
    newNum.len = j+1;
    while (newNum.len > 1 && newNum.coef[newNum.len-1] == 0) {
        newNum.len--;
    }
    return newNum;
}

BN& BN::operator += (const BN& bNum) {
    *this = *this + bNum;
    return *this;
}

BN BN::operator - (const BN& bNum) {
    if (*this < bNum) {
        throw invalid_argument("Invalid arguments.");
    }

    int j = 0;
    DBASE k = 0;
    DBASE tmp;
    int b = BASE_SIZE;
    BN newNum(len);
    while (j < bNum.len) {
        tmp = static_cast<DBASE>((static_cast<DBASE>(1) << (b)) |
        static_cast<DBASE>(coef[j]));
        tmp = static_cast<DBASE>(static_cast<DBASE>(tmp) -
        static_cast<DBASE>(bNum.coef[j]) - static_cast<DBASE>(k));
        newNum.coef[j] = static_cast<BASE>(tmp);
        k = !(tmp >> b);

        j++;
    }
    while (j < len) {
        tmp = (static_cast<DBASE>(1) << (b)) | static_cast<DBASE>(coef[j]);
        tmp -= static_cast<DBASE>(k);
        newNum.coef[j] = static_cast<BASE>(tmp);
        k = !(tmp >> b);
        j++;
    }

    newNum.len = len;
    while (newNum.len > 1 && newNum.coef[newNum.len-1] == 0) {
        newNum.len--;
    }
    return newNum;
}

BN& BN::operator -= (const BN& bNum) {
    *this = *this - bNum;
    return *this;
}

BN BN::operator * (const BASE& num) {
    int j = 0;
    BASE k = 0;

    BN newNum(len+1);
    DBASE tmp;
    int b = BASE_SIZE;

    while (j < len) {
        tmp = static_cast<DBASE>(static_cast<DBASE>(coef[j]) *
        static_cast<DBASE>(num) + static_cast<DBASE>(k));
        newNum.coef[j] = static_cast<BASE>(tmp);
        k = static_cast<BASE>((tmp) >> (b));
        j++;
    }
    newNum.coef[j] = k;
    newNum.len = len + 1;
    while (newNum.len > 1 && newNum.coef[newNum.len-1] == 0) {
        newNum.len--;
    }
    return newNum;
}

BN& BN::operator *= (const BASE& num) {
    *this = *this * num;
    return *this;
}

BN BN::operator * (const BN& bNum) {
    int j = 0;

    BN newNum(len + bNum.len);
    DBASE tmp;

    int b = BASE_SIZE;

    while (j < bNum.len) {
        if (bNum.coef[j] != 0) {
            BASE k = 0;
            int i = 0;
            while (i < len) {
                tmp = static_cast<DBASE>(static_cast<DBASE>(
                    static_cast<DBASE>(coef[i]) *
                    static_cast<DBASE>(bNum.coef[j])) +
                    static_cast<DBASE>(newNum.coef[i+j]) +
                    static_cast<DBASE>(k));
                newNum.coef[i+j] = static_cast<BASE>(tmp);
                k = static_cast<BASE>(tmp >> (b));
                i++;
            }
            newNum.coef[len+j] = k;
        }
        j++;
    }
    newNum.len = len + bNum.len;
    while (newNum.len > 1 && newNum.coef[newNum.len-1] == 0) {
        newNum.len--;
    }
    return newNum;
}

BN& BN::operator *= (const BN& bNum) {
    *this = *this * bNum;
    return *this;
}

BN BN::operator / (const BASE& num) {
    int j = 0;
    DBASE tmp = 0;
    BN newNum(len);

    BASE r = 0;
    int b = BASE_SIZE;

    while (j < len) {
        tmp = static_cast<DBASE>((static_cast<DBASE>(r) << (b)) +
        static_cast<DBASE>(coef[len-1-j]));

        newNum.coef[len-1-j] = static_cast<BASE>(static_cast<DBASE>(tmp) /
        static_cast<DBASE>(num));
        r = static_cast<BASE>(static_cast<DBASE>(tmp) %
        static_cast<DBASE>(num));
        j++;
    }

    newNum.len = len;
    while (newNum.len > 1 && newNum.coef[newNum.len-1] == 0) {
        newNum.len--;
    }

    return newNum;
}

BN BN::operator % (const BASE& num) {
    int j = 0;

    DBASE tmp = 0;

    BASE r = 0;
    int b = BASE_SIZE;
    BN newNum(1);
    while (j < len) {
        tmp = ((static_cast<DBASE>(r) << b) +
        static_cast<DBASE>(coef[len-1-j]));
        r = static_cast<BASE>(tmp % static_cast<DBASE>(num));
        j++;
    }

    newNum.coef[0] = r;
    return newNum;
}

void BN::cout_base10() {
    BN newNun = *this;
    BN zero(newNun.len);
    if (newNun == zero) {
        cout << "Base10: 0";
        return;
    }
    string s;
    zero.len = newNun.len;
    while (newNun != zero) {
        BN t = newNun%10;
        s.push_back(t.coef[0] + '0');

        newNun = newNun / 10;
        zero.len = newNun.len;
    }
    reverse(s.begin(), s.end());
    cout << "Base10: " << s;
}

void BN::cin_base10() {
    int j = 0;
    string s;
    cout << "Base10: ";
    getline(cin, s);
    int k = s.length();
    BASE t = 0;
    DBASE tmp = 0;

    int b = BASE_SIZE;

    BN bNum((k - 1)/(b/4)+1);

    while (j < k) {
        if ('0'  > s[j] || s[j] > '9') {
            throw invalid_argument("Invalid arguments.");
        }

        t = s[j] - '0';
        bNum = bNum*(static_cast<BASE>(10));

        BN newNum;
        newNum.coef[0] = static_cast<BASE>(t);
        bNum += newNum;
        j++;
    }

    bNum.len = bNum.maxlen;
    while (bNum.len > 1 && bNum.coef[bNum.len-1] == 0) {
        bNum.len--;
    }
    *this = bNum;
}

BN BN::operator / (const BN& num) {
    if (num.len == 1 && num.coef[0] == 0) {
        throw invalid_argument("Invalid arguments1.");
    }
    if (*this < num) {
        BN finNum(1);
        return finNum;
    }

    if (num.len == 1) {
        return *this / num.coef[0];
    }

    int m = len - num.len;
    int base_size = BASE_SIZE;
    DBASE b = (static_cast<DBASE>(1) << base_size);
    BASE d = static_cast<BASE>(static_cast<DBASE>(b) /
    static_cast<DBASE>((num.coef[num.len-1]) + static_cast<BASE>(1)));
    int j = m;
    int k = 0;

    BN newNum = *this;
    newNum *= d;
    BN delNum = num;
    delNum *= d;

    BN finNum(m+1);
    finNum.len = m+1;

    if (newNum.len == len) {
        newNum.maxlen++;
        newNum.len = maxlen;
        newNum.coef = new BASE[maxlen];
        for (int i = 0; i <  len; i++) {
            newNum.coef[i] = coef[i];
        }
        newNum *= d;
        newNum.len++;
        newNum.coef[newNum.len-1] = 0;
    }

    while (j > -1) {
        DBASE q = static_cast<DBASE>(static_cast<DBASE>(static_cast<DBASE>(
            static_cast<DBASE>(newNum.coef[j + delNum.len]) *
            static_cast<DBASE>(b)) +
            static_cast<DBASE>(newNum.coef[j + delNum.len - 1])) /
            static_cast<DBASE>(delNum.coef[delNum.len - 1]));
        DBASE r = static_cast<DBASE>(static_cast<DBASE>(static_cast<DBASE>
        (static_cast<DBASE>(newNum.coef[j + delNum.len]) *
        static_cast<DBASE>(b)) + static_cast<DBASE>(
            newNum.coef[j + delNum.len - 1])) %
            static_cast<DBASE>(delNum.coef[delNum.len - 1]));

        if (q == b || static_cast<DBASE>(static_cast<DBASE>(q) *
        static_cast<DBASE>(delNum.coef[delNum.len-2])) >
        static_cast<DBASE>(static_cast<DBASE>(static_cast<DBASE>(b) *
        static_cast<DBASE>(r)) +
        static_cast<DBASE>(newNum.coef[j+delNum.len-2]))) {
            q--;
            r = static_cast<DBASE>(r) +
            static_cast<DBASE>(delNum.coef[delNum.len - 1]);
            if (static_cast<DBASE>(r) < b) {
                if (q == b || static_cast<DBASE>(static_cast<DBASE>(q) *
                static_cast<DBASE>(delNum.coef[delNum.len-2])) >
                static_cast<DBASE>(static_cast<DBASE>(static_cast<DBASE>(b) *
                static_cast<DBASE>(r)) +
                static_cast<DBASE>(newNum.coef[j+delNum.len-2]))) {
                    q--;
                }
            }
        }

        BN u(delNum.len + 1);
        u.len = delNum.len + 1;
        for (int i = 0; i < delNum.len + 1; i++) {
            u.coef[i] = newNum.coef[j+i];
        }

        if (u < static_cast<BASE>(q) * delNum) {
            q--;
        }

        u = u - static_cast<BASE>(q) * delNum;
        finNum.coef[j] = static_cast<BASE>(q);

        for (int i = 0; i < delNum.len + 1; i++) {
            newNum.coef[j+i] = u.coef[i];
        }

        j--;
    }

    while (finNum.len > 1 && finNum.coef[finNum.len-1] == 0) {
        finNum.len--;
    }

    return finNum;
}

BN BN::operator % (const BN& num) {
    if (num.len == 1 && num.coef[0] == 0) {
        throw invalid_argument("Invalid arguments.");
    }
    if (*this < num) {
        return *this;
    }

    if (num.len == 1) {
        return *this % num.coef[0];
    }

    int m = len-num.len;
    int base_size = BASE_SIZE;
    DBASE b = (static_cast<DBASE>(1) << (base_size));
    BASE d =  static_cast<BASE>(static_cast<DBASE>(b) /
    static_cast<DBASE>((num.coef[num.len-1]) + static_cast<BASE>(1)));
    int j = m;
    int k = 0;

    BN newNum = *this;
    newNum *= d;
    BN delNum = num;
    delNum *= d;
    if (newNum.len == len) {
        newNum.maxlen++;
        newNum.len = maxlen;
        newNum.coef = new BASE[maxlen];
        for (int i = 0; i <  len; i++) {
            newNum.coef[i] = coef[i];
        }
        newNum *= d;
        newNum.len++;
        newNum.coef[newNum.len-1] = 0;
    }

    while (j > -1) {
        DBASE q = static_cast<DBASE>(static_cast<DBASE>(static_cast<DBASE>(
            static_cast<DBASE>(newNum.coef[j + delNum.len]) *
            static_cast<DBASE>(b)) +
            static_cast<DBASE>(newNum.coef[j + delNum.len - 1])) /
            static_cast<DBASE>(delNum.coef[delNum.len - 1]));
        DBASE r = static_cast<DBASE>(static_cast<DBASE>(static_cast<DBASE>(
            static_cast<DBASE>(newNum.coef[j + delNum.len]) *
            static_cast<DBASE>(b)) +
            static_cast<DBASE>(newNum.coef[j + delNum.len - 1])) %
            static_cast<DBASE>(delNum.coef[delNum.len - 1]));
        if (q == b || static_cast<DBASE>(static_cast<DBASE>(q) *
        static_cast<DBASE>(delNum.coef[delNum.len-2])) >
        static_cast<DBASE>(static_cast<DBASE>(static_cast<DBASE>(b) *
        static_cast<DBASE>(r)) +
        static_cast<DBASE>(newNum.coef[j+delNum.len-2]))) {
            q--;
            r = static_cast<DBASE>(r) +
            static_cast<DBASE>(delNum.coef[delNum.len - 1]);
            if (static_cast<DBASE>(r) < b) {
                if (q == b || static_cast<DBASE>(static_cast<DBASE>(q) *
                static_cast<DBASE>(delNum.coef[delNum.len-2])) >
                static_cast<DBASE>(static_cast<DBASE>(static_cast<DBASE>(b) *
                static_cast<DBASE>(r)) +
                static_cast<DBASE>(newNum.coef[j+delNum.len-2]))) {
                    q--;
                }
            }
        }
        BN u(delNum.len + 1);
        u.len = delNum.len + 1;
        for (int i = 0; i < delNum.len + 1; i++) {
            u.coef[i] = newNum.coef[j+i];
        }

        if (u < static_cast<BASE>(q) * delNum) {
            q--;
        }

        u = u - (static_cast<BASE>(q) * delNum);

        for (int i = 0; i < delNum.len + 1; i++) {
            newNum.coef[j+i] = u.coef[i];
        }

        j--;
    }
    while (newNum.len > 1 && newNum.coef[newNum.len-1] == 0) {
        newNum.len--;
    }
    return newNum / d;
}

void test() {
    int M = 1000;
    int T = 1000;
    srand(time(NULL));
    BN A;
    BN B;
    BN C;
    BN D;
    do {
        int n = rand()%M + 1;
        int m = rand()%M + 1;
        BN E(n, 1);
        BN G(m, 1);
        A = E;
        B = G;
        C = A / B;
        D = A % B;
        cout << "m: " << m << " ";
        cout << "n: " << n << " ";
        cout << "T: " << T << endl;
    }
    while (A == C * B + D && A - D == C*B && D < B && --T);
    cout << T << endl;
}



BN BN::square() {
    BN res(2 * len);
    int j;
    DBASE cu = 0;
    DBASE uv = 0;
    BASE v = 0;
    DBASE tmp = 0;
    res.len = res.maxlen;
    for (int i = 0; i < len; i++) {
        uv = (DBASE)res.coef[2 * i] + (DBASE)coef[i] * (DBASE)coef[i];
        res.coef[2 * i] = (BASE)uv;
        cu = (uv >> BASE_SIZE);
        for (j = i + 1; j < len; j++) {
            tmp = static_cast<DBASE>(static_cast<DBASE>(static_cast<BASE>(res.coef[i + j]))
            + static_cast<DBASE>(static_cast<BASE>(static_cast<DBASE>(coef[i])
            * static_cast<DBASE>(coef[j])) << 1)
            + static_cast<DBASE>(static_cast<BASE>(cu)));

            v = static_cast<BASE>(tmp);

            cu = static_cast<DBASE>(static_cast<DBASE>((
            static_cast<DBASE>(static_cast<DBASE>(coef[i])
            * static_cast<DBASE>(coef[j])) >> BASE_SIZE)
            * static_cast<DBASE>(2))
            + static_cast<DBASE>(static_cast<DBASE>(cu) >> BASE_SIZE)
            + static_cast<DBASE>(static_cast<DBASE>(tmp) >> BASE_SIZE));

            res.coef[i + j] = v;
        }
        res.coef[i + len] += static_cast<BASE>(cu);
        res.coef[i + len + 1] += static_cast<BASE>(cu >> BASE_SIZE);
    }

    res.len = res.maxlen;
    for (int i = 2*len-1; i > -1; i--) {
        if (res.coef[i] == 0) {
            res.len--;
        } else {
            break;
        }
    }
    return res;
}


int numberOfDigit(int y) {
    int n = 0;
    while (y != 0) {
        y = y >> 1;
        n++;
    }
    return n;
}

BN BN::pow_BN(int y) {
    BN z;
    if (y == 0) {
        z = 1;
        return z;
    }
    int n = numberOfDigit(y),
    mask = 1 << n-2;
    z = *this;
    for (int i = n - 2; i > -1; i--) {
        z = z.square();
        if (mask & y) {
            z = z * *this;
        }
        mask >>= 1;
    }
    return z;
}

BN BN::pow_BN(BN y) {
    BN zero, one, res;
    one = 1;
    res = 1;
    for(BN power = y; power > zero; power = power - one){
        res = res * *this;
    }
    return res;
}

BN shift(BN num, int k) {
    if (k >= num.len) {
        BN shift_num(k);
        return shift_num;
    }
    BN shift_num(num.len-k);
    shift_num.len = shift_num.maxlen;
    for (int i = 0; i < num.len - k; i++)
        shift_num.coef[i] = num.coef[i+k];
    return shift_num;
}

BN rem(BN number, int k) {
    if (k >= number.len) {
        return number;
    }
    BN rem(k);
    rem.len = rem.maxlen;
    for (int i = 0; i < rem.len; i++) {
        rem.coef[i] = number.coef[i];
    }
    for (int i = rem.maxlen - 1; i > -1; i--) {
        if (rem.coef[i] == 0) {
            rem.len--;
        } else {
            break;
        }
    }
    return rem;
}

BN BarrettReduction(BN num, BN m, BN z) {
    if (num.len > 2 * m.len) {
        throw invalid_argument("Invalid arguments. Module too small.");
    }
    BN q1, b(2), r1, r2, rm;
    b.len = b.maxlen;
    b.coef[1] = 1;
    q1 = (shift(num, m.len - 1) * z);
    q1 = shift(q1,  m.len + 1);
    r1 = rem(num, m.len+1);
    r2 = rem((q1*m), m.len+1);
    if (r1 >= r2) {
        rm = r1-r2;
    } else {
        BN new_b(2 * m.len +1 + b.len - 1);
        new_b.len = new_b.maxlen;
        new_b.coef[2 * m.len + 2] = 1;
        rm = new_b + r1 - r2;
    }
    while (rm >= m) {
        rm -= m;
    }
    return rm;
}

BN ret_z(BN m) {
    BN b(2), z;
    b.len = b.maxlen;
    b.coef[1] = 1;
    BN new_b(((m.len) << 1) + b.len - 1);
    new_b.len = new_b.maxlen;
    new_b.coef[(m.len << 1)] = 1;
    z = new_b / m;
    return z;
}


BN BN::root(int n) {
    BN a = *this;
    BN x0, x1 = a;
    do {
        x0 = x1;
        x1 = (x0 * (n - 1) + a/x0.pow_BN(n-1)) * 1/n;
    }
    while (x0 > x1);
    return x0;
}


BN random_bound(BN lower, BN higher){
    BN random(higher.maxlen, 1);
    if (higher > lower) {
        random = random % (higher - lower);
        random = random + lower;
    } else {
        random = lower;
    }
    return random;    
} 

bool BN::isPrime(int t = 5) {
    BN n = *this;
    BN zero, two, one;
    one = 1;
    two = 2;
    if((n.coef[0] > 3) || (n.len != 1)){
        if(n%2 != zero){
            BN r = n - one;
            int s = 0;
            while(r%2 == zero){
                r = r / 2;
                s++;
            }
            BN b;
            for(int i = 0; i < t; i++){
                b = random_bound(two, n-two);
                
                BN y = b.pow_BN(r) % n;
                
                if((y != one) && (y != (n-one))){
                    int j = 1;
                    while((j < s) && (y != (n-one))){
                        y = y.square();
                        y = y % n;

                        if(y == one)
                            return false;
                        j++;
                    }
                    if(y != (n-one))
                        return false;
                }
            }
        } else {
            return false;
        }
    }
    return true;
}

BN BN::gcd(BN num){
    BN a = *this;
    BN b = num;
    BN zero;
    BN two;
    two = 2;
    BN c;
    int i = 0, j = 0, k;
    while(a%2 == zero){
        a = a / 2;
        i++;
    }
    while(b%2 == zero){
        b = b / 2;
        j++;
    }
    if(i > j)
        k = j;
    else
        k = i;
    while(a != b){
        if(a > b){
            c = a - b;
            while(c%2 == zero)
                c = c / 2;
            a = c;      
        }
        else{
            c = b - a;
            while(c%2 == zero)
                c = c / 2;
            b = c;      
        }
    }
    return two.pow_BN(k) * a;
}

int BN::log(int a){
    BN b = *this;
    BN res;
    res = 1;
    int power = 0;
    while(res != b && res < b){
        res = res * a;
        power++;
    }
    return power;
}

BN fastPow(BN b, int n, BN m) {
    BN c;
    c = 1;

    for (int i = 0; i < n; i++) {
        c = (b * c) % m;
    }
    return c;
}


#endif  // _HOME_LIDER_PROJECTS_NTINCRYPTO_BIGNUM_H_

#include <iostream>
#include <vector>
#include "BigNum.h"


using namespace std;

BN Alway_method(BN n, BN d) {
    BN zero, two, one, four;
    two = 2;
    one = 1;
    four = 4;
    if(n % 2 != zero){
        n.root(3).cout_base10();
        cout << " root 3\n";
        if((d >= n.root(3)*2+one) && (d % 2 != zero)){
            BN r_1 = n % d;
            BN r_2 = n % (d - two);
            BN q = ((n / (d - two)) - (n / d)) * 4;
            BN s = n.root(2);
            while(d < s){
                d += two;
                BN r;
                if((r_1 * 2) + q < r_2){
                    //Когда у нас r будет меньше 0? Когда 2*r1 + q < r2, потому что r2 мы вычитаем.
                    r = ((r_1 * 2) + q + d) - r_2;
                    r_2 = r_1;
                    r_1 = r;
                    q += four;
                } else {
                    r = ((r_1 * 2) + q) - r_2;
                    r_2 = r_1;
                    r_1 = r;
                }
                while(r_1 >= d){
                    r_1 -= d;
                    q -= four;
                }
                if(r_1 == zero)
                    return d;
            }
            cout << "there is no any divider\n";
            return zero;
        }
        else{
            cout << "d is wrong\n";
            return zero;
        }
    }
    else{
        cout << "n is wrong\n";
        return zero;
    }
}


BN* Fermat_algorithm(BN n){
    BN x = n.root(2);
    BN *d = new BN[2];
    BN one, y, z;
    one = 1;
    if(x.square() == n){
        d[0] = x;
        d[1] = x;
        return d;
    }
    while(y.square() != z){
        x = x + one;
        if(x == (n+one)/2){
            cout << "n is prime\n";
            return d;
        }
        z = x.square() - n;
        y = z.root(2);
    }
    d[0] = x + y;
    d[1] = x - y;
    return d;
}

BN Pollard_function(BN x, BN n) {
    BN result = x;
    BN one;
    one = 1;
    result.square();
    result = (result + one) % n;
    return result;
}

BN P0_Pollard_method(BN n) {
    BN a, b, d, one, zero;
    a = 2;
    b = 2;
    one = 1;
    do {
        a = Pollard_function(a, n);
        b = Pollard_function(Pollard_function(b, n), n);
        if (a == b) {
            cout << "No result\n";
            return zero;
        }
        if (a > b)
            d = n.gcd(a-b);
        else
            d = n.gcd(b-a);
    }
    while (d == one);
    return d;
}



BN P_1_Pollard_method(BN n){ //если не выводит значит не угадали
    
    int B = 100;
    BN a, two, one, zero;
    one = 1;
    two = 2;
    a = random_bound(two, (n-two));
    BN d = a.gcd(n);
    if(d > one)
        return d;
    int q = 2;
    while(q < B){
        BN check;
        check = q;
        if(check.isPrime(3)){
            int e = n.log(q);
            a = fastPow(a, pow(q, e), n);
        }
        q++;
    }
    if(a == one){
        cout << "Denied soft\n";
        return zero;
    }
    else{
        d = n.gcd(a-one);
        if(d == one){
            cout << "Denied hard\n";
            return zero;
        }
        else
            return d;
    }
}

// 97825

int main() {
//    BN num;
//    num.cin_base10();
//    P0_Pollard_method(num).cout_base10();

//
    srand(time(NULL));
    BN num;
    num.cin_base10();
    P_1_Pollard_method(num).cout_base10();
    cout << endl;
}


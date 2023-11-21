#include <iostream>
#include "cmake-build-debug/MyBN.h"
#include <cmath>
#include <map>

using namespace std;

BN* trial_division_method(BN &n) {
    BN prey = n;
    BN *d = new BN[1000];
    d[0] = 3;
    d[1] = 5;
    d[2] = 7;
    BN *p = new BN[100];
    int t = -1;
    int k = 0;
    BN one, zero, six;
    one = 1;
    zero = 0;
    six = 6;
    while (prey != one) {
        if (prey % 2 != zero) {
            BN r = prey % d[k];
            BN q = prey / d[k];
            if (r == zero) {
                t++;
                p[t] = d[k];
                prey = q;
            }
            else {
                if (q > d[k]){
                    k++;
                    if (k > 2){
                        d[k] = d[k-2] + six;
                    }
                }
                else {
                    t++;
                    p[t] = prey;
                    return p;
                }
            }
        }
        else {
            t++;
            p[t] = 2;
            prey = prey / 2;
        }
    }
    return p;
}

BN Alway_method(BN n, BN d) {
    BN zero, two, one, four;
    two = 2;
    one = 1;
    four = 4;
    if(n % 2 != zero){
        if((d >= n.root(3)*2+one) && (d % 2 != zero)){
            BN r_1 = n % d;
            BN r_2 = n % (d - two);
            BN q = (n / (d - two) - n / d) * 4;
            BN s = n.root(2);
            while(d < s){
                d += two;
                BN r;
                if((r_1 * 2) + q < r_2){
                    r = ((r_1 * 2) + q + d) - r_2;
                    r_2 = r_1;
                    r_1 = r;
                    q += four;
                } 
                else {
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

BN Pollard_function(BN x, BN n){
    BN result = x;
    BN one;
    one = 1;
    result.square();
    result = (result + one) % n;
    return result;
}

BN ro_Pollard_method(BN n){
    BN a, b, d, one, zero;
    a = 2;
    b = 2;
    one = 1;
    do{
        a = Pollard_function(a, n);
        b = Pollard_function(Pollard_function(b, n), n);
        if(a == b){
            cout << "No result\n";
            return zero;
        }
        if(a > b)
            d = n.gcd(a-b);
        else
            d = n.gcd(b-a);
    }
    while(d == one);
    return d;
}

BN p1_Pollard_method(BN n){
    int B = 100;
    BN a, two, one, zero;
    one = 1;
    two = 2;
    a.random_bound(two, (n-two));
    BN d = a.gcd(n);
    if(d > one)
        return d;
    int q = 2;
    while(q < B){
        BN check;
        check = q;
        if(check.Miller_Rabin_test(3)){
            int e = n.log(q);
            a = a.fastPow(pow(q, e), n);
        }
        q++;
    }
    if(a == one){
        cout << "Denied (not scary)\n";
        return zero;
    }
    else{
        d = n.gcd(a-one);
        if(d == one){
            cout << "Denied (scary)\n";
            return zero;
        }
        else
            return d;
    }
}

int Gelfonds_algorithm(BN g, BN p, int n, BN a){
    int h = sqrt(n) + 1;
    BN b = g.pow_int(h) % p;
    map<BN, int> giant_step;
    for(int u = 1; u <= h; u++){
        BN key = b.pow_int(u) % p;
        if(giant_step[key] == 0)
            giant_step[key] = u;
    }
    map<int, BN> small_step;
    for(int v = 1; v <= h; v++){
        small_step[v] = (a * g.pow_int(v)) % p; 
        if(giant_step.find(small_step[v]) != giant_step.end())
            return (h * giant_step[small_step[v]] - v) % n;
    }
    cout << "WTF C++ Why??? :/";
    return 0;
}

int main() {
    BN g, p, a;
    int n;
    cout << "Enter g:\n";
    g.cin_base10();
    cout << "Enter p:\n";
    p.cin_base10();
    cout << "Enter a:\n";
    a.cin_base10();
    cout << "Enter n: ";
    cin >> n;
    cout << Gelfonds_algorithm(g, p, n, a) << "\n";
}

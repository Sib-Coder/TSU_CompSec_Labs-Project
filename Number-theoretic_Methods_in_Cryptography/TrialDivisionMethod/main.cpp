#include <iostream>
#include <vector>
#include "BigNum.h"
#include <cmath>

using namespace std;

BN* trial_division_method(const BN &n) {
    BN check_num = n;
    vector<BN> d(3);
    BN temp;
    temp = 3;
    d[0]=temp;
    temp = 5;
    d[1] = temp;
    temp = 7;
    d[2] = temp;
    BN *p = new BN[100];
    int t = -1;
    int k = 0;
    BN one, zero, six;
    one = 1;
    zero = 0;
    six = 6;
    while (check_num != one) {
        if (check_num % 2 != zero) {
            BN r = check_num % d[k];
            BN q = check_num / d[k];
            if (r == zero) {
                t++;
                p[t] = d[k];
                check_num = q;
            } else {
                if (q > d[k]) {
                    k++;
                    if (k > 2) {
                        temp = d[k-2] + six;
                        d.push_back(temp);
                    }
                } else {
                    t++;
                    p[t] = check_num;
                    return p;
                }
            }
        } else {
            t++;
            p[t] = 2;
            check_num = check_num / 2;
        }
    }
    return p;
}




int main() {
    BN num;
    num.cin_base10();
    BN *p = new BN[100];

    p = trial_division_method(num);
    int i = 0;
    BN zero;
    while (p[i] != zero) {
        p[i].cout_base10();
        i++;
    }
}

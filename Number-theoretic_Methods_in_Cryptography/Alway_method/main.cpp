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

int main() {

    BN num, d;
    BN one;
    one = 1;
    num.cin_base10();
    BN result;
    d = num.root(3)*2+one;
    result = Alway_method(num, d);
    result.cout_base10();

}


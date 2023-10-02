#include <iostream>
#include <vector>
#include "BigNum.h"


using namespace std;

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

int main() {

//    BN num, d;
//    BN one;
//    one = 1;
//    num.cin_base10();
//    BN result;
//    d = num.root(3)*2+one;
//    result = Alway_method(num, d);
//    result.cout_base10();

BN number;
number.cin_base10();
    BN *d;
    d = Fermat_algorithm(number);
    d->cout_base10();
}
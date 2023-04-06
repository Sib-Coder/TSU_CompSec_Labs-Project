
#include <iostream>
#include <chrono>
#include "BigNum.h"

using namespace std;
using namespace std::chrono;

BN square(BN num) {
    BN res(2 * num.len);// первый пункт алгоритма
    int j;
    DBASE cu = 0;
    DBASE uv = 0;
    BASE v = 0;
    DBASE tmp =0;
    res.len = res.maxlen;
    for (int i = 0; i < num.len; i++)// 2 пункт
    {
        uv = (DBASE)res.coef[2 * i] + (DBASE)num.coef[i] * (DBASE)num.coef[i];// вычисляем uv пункт 2.1
        res.coef[2 * i] = (BASE)uv;
        cu = (uv >> BASE_SIZE); //c=0 u=u
        for (j = i + 1; j < num.len; j++)// пункт 2.2
        {
            tmp = static_cast<DBASE>(static_cast<DBASE>(static_cast<BASE>(res.coef[i + j]))
            + static_cast<DBASE>(static_cast<BASE>(static_cast<DBASE>(num.coef[i])
            * static_cast<DBASE>(num.coef[j])) * 2)
            + static_cast<DBASE>(static_cast<BASE>(cu)));

            v = static_cast<BASE>(tmp);

            cu = static_cast<DBASE>(static_cast<DBASE>((
            static_cast<DBASE>(static_cast<DBASE>(num.coef[i])
            * static_cast<DBASE>(num.coef[j])) >> BASE_SIZE)
            * static_cast<DBASE>(2))
            + static_cast<DBASE>(static_cast<DBASE>(cu) >> BASE_SIZE)
            + static_cast<DBASE>(static_cast<DBASE>(tmp) >> BASE_SIZE));

            res.coef[i + j] = v;// y =v
        }
        res.coef[i + num.len] += static_cast<BASE>(cu);// добавляем u

        res.coef[i + num.len + 1] += static_cast<BASE>(cu >> BASE_SIZE);//  пункт 2.3 lj добавляем с
    }

    res.len = res.maxlen;
    for (int i = 2*num.len-1; i > -1; i--) { //нормализация длины
        if (res.coef[i] == 0) {
            res.len--;
        } else {
            break;
        }
    }
    return res;
}


int main() {

    BN bn1(6);
    cout << "Enter a number: " << endl;
    cin >> bn1;
     cout << bn1 << endl;
     time_point begin1 = system_clock::now();
     BN bn2 = bn1*bn1;
     cout << bn2 << endl;
     time_point end1 = system_clock::now();
     auto diff1 = end1 - begin1;
     cout << duration <double, milli> (diff1).count() << " ms" << endl;

    
     time_point begin2 = system_clock::now();
     BN bn3 = square(bn1);
     time_point end2 = system_clock::now();
     auto diff2 = end2 - begin2;

     cout << duration <double, milli> (diff2).count() << " ms" << endl;

     if (bn2 == bn3) {
         cout << "Values are equals" << endl;
     } else {
         cout << "Values are not equal" << endl;
     }


}

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <cstring>
#include <math.h>
#include <algorithm>
typedef unsigned  char BASE;
typedef unsigned   short  DBASE;
#define BASE_SIZE (sizeof(BASE)*8);
using namespace std;

class BN {
    BASE *coef;
    int len;
    int maxlen;
public:
    BN(int ml = 1, int d = 0);
    BN(const BN &);
    ~BN() {
        if (coef) delete[]coef;
        coef = NULL;
    };
    BN operator=(const BN &);
    bool operator==(const BN &);
    bool operator<=(const BN &);
    bool operator>=(const BN &);
    bool operator<(const BN &);
    bool operator>(const BN &);
    bool operator!=(const BN &);


    BN operator+(const BN &);

    BN &operator+=(const BN &);

    BN operator-(const BN &);

    BN &operator-=(const BN &);

    BN operator * (const BASE&);

    BN operator *(const BN&);
    BN &operator *=(const BASE&);

    BN operator / (const BASE&);
    BN operator % (const BASE&);
    BN operator / (const BN&);
    BN operator % (const BN&);

    void cout_10();
    void cin_10();
    friend ostream& operator << (ostream &, const BN &);
    friend istream& operator >> (istream &, BN &);

};

BN::BN(int ml, int d) {
    coef = new BASE[ml];
    int size=BASE_SIZE;
    maxlen = ml;
    len = ml;
    for (int i = 0; i < maxlen; i++)
        coef[i] = 0;
    if (d != 0) {
        for (int i = 0; i < maxlen; i++) {
            coef[i] = rand();
            if (size > 12)
                for (int j = 1; j < ceil(size / 12); j++)
                    coef[i] = coef[i] << (j * 12) | rand();
        }
        while (len > 1 && coef[len - 1] == 0)
            len--;
    }
}

BN::BN(const BN &num) {
    maxlen = num.maxlen;
    len = num.len;
    coef = new BASE[maxlen];
    for (int i = 0; i < maxlen; i++)
        coef[i] = num.coef[i];
}

BN BN::operator=(const BN &num) {
    if (this != &num) {
        delete[]coef;
        maxlen = num.maxlen;
        len = num.len;
        coef = new BASE[maxlen];
        for (int i = 0; i < maxlen; i++)
            coef[i] = num.coef[i];
    }
    return *this;
}
bool BN::operator==(const BN &d) {
    if (len != d.len){
        return false;
    }
    for (int i=0;i<len;i++){
        if (coef[i]!=d.coef[i]){
            return false;
        }
    }
    return true;
}

bool BN::operator!=(const BN &d) {
    if (len != d.len){
        return true;
    }
    for (int i=0;i<len;i++){
        if (coef[i]!=d.coef[i]){
            return true;
        }
    }
    return false;
}

bool BN::operator <(const BN& d){
    if(len < d.len){
        return true;
    }
    else if(len > d.len){
        return false;
    }
    for(int i = len-1; i>-1; i--){
        if (coef[i] > d.coef[i])
        {
            return false;
        }
        else if (coef[i] < d.coef[i])
        {
            return true;
        }
    }
    return false;
}

bool BN::operator > (const BN& d){
    if(len > d.len){
        return true;
    }
    else if(len < d.len){
        return false;
    }
    for(int i = len-1; i>-1; i--){
        if (coef[i] < d.coef[i])
        {
            return false;
        }
        else if (coef[i] > d.coef[i])
        {
            return true;
        }
    }
    return false;
}
bool BN::operator >= (const BN& d){
    if(len > d.len){
        return true;
    }
    else if(len < d.len){
        return false;
    }
    for(int i = len-1; i>-1; i--){
        if (coef[i] < d.coef[i])
        {
            return false;
        }
        else if (coef[i] > d.coef[i])
        {
            return true;
        }
    }
    return true;
}

bool BN::operator <= (const BN& d){
    if(len < d.len){
        return true;
    }
    else if(len > d.len){
        return false;
    }
    for(int i = len-1; i>-1; i--){
        if (coef[i] > d.coef[i])
        {
            return false;
        }
        else if (coef[i] < d.coef[i])
        {
            return true;
        }
    }
    return true;
}
BN BN::operator + (const BN& bNum){
    int l = max(len, bNum.len)+1;//максимальная длина
    int t = min(len, bNum.len);//колличество общих разрядов
    BN newNum(l);
    DBASE tmp;
    int j =0;
    int k = 0;//перенос
    int b = BASE_SIZE;
    while (j<t)
    {
        tmp = (DBASE) coef[j] + (DBASE) bNum.coef[j] + (DBASE)k;
        newNum.coef[j] = (BASE)tmp;
        k = (BASE)(tmp >> b);//сдвигаю есть ли единица в старщих разрядах
        j++;
    }
    while(j < len){
        tmp = coef[j] + k;//складываем числа с переносом
        newNum.coef[j] = (BASE)tmp;
        k = (BASE)(tmp >> b);
        j++;
    }

    while(j < bNum.len){
        tmp = (DBASE) bNum.coef[j] + (DBASE) k;
        newNum.coef[j] = (BASE)tmp;
        k = (BASE)(tmp >> b);
        j++;
    }
    newNum.coef[j] = k;//самый последний коэфициент в него кладём перенос
    newNum.len = j+1;
    if(k==0){
        newNum.len = j;
    }
    return newNum;
}

BN& BN:: operator += (const BN & bNum) {
    *this = *this + bNum;
    return *this;
}
BN BN ::operator-(const BN &bNum) {
    if (*this <bNum){
        throw invalid_argument("Invalid argument");//можно ли их отнять чтобы не было отриц знач
    }
    int j=0;
    int k=0;//коэф.заёма
    DBASE tmp;
    int b=BASE_SIZE;
    BN newNum(len);
    while(j<bNum.len){//c двумя коэфами
        tmp=((DBASE)1<<b) | coef[j];//учитываем заём
        tmp=tmp-bNum.coef[j]-k;//отняли нужное и заём

        newNum.coef[j]=(BASE)tmp;//заносим значение разности
        k = !(tmp>>b);//считаю заём ( работаем с 1 из 233)

        j++;
    }
    while(j< len){//забираю заём
        tmp = ((DBASE)1<<b)| coef[j];
        tmp-=k;//вычитаем К
        newNum.coef[j]=(BASE)tmp;
        k = !(tmp>>b);
        j++;
    }
    newNum.len=len;
    while(newNum.len>1&& newNum.coef[newNum.len-1]==0){//приводим фактическую длину
        newNum.len--;
    }
    return newNum;// возвращаем красоту

}

BN& BN::operator-=(const BN &bNum) {
    *this=*this -bNum;
    return *this;
}

BN BN::operator*(const BASE& num) {
    int j=0;
    BASE k=0;
    BN newNum(len+1);
    DBASE tmp;
    int b =BASE_SIZE;
    while (j<len){
        tmp =(DBASE)coef[j]*(DBASE)num+(DBASE)k;
        newNum.coef[j]=(BASE)tmp;
        k=(BASE)(tmp>>b);
        j++;
    }
    newNum.coef[j]=k;
    newNum.len=len+1;//установили длину
    while (newNum.len>1&&newNum.coef[newNum.len-1]==0){
        newNum.len--;//нормализуем длину
    }
    return newNum;
}
BN& BN::operator*=(const BASE &num) {
    *this =*this * num;
    return *this;
}
BN BN::operator*(const BN &bNum) {
    int j = 0;

    BN newNum(len + bNum.len);
    DBASE tmp;

    int b = BASE_SIZE;

    while(j<bNum.len){
        if(bNum.coef[j]!=0){
            BASE k = 0;
            int i = 0;
            while (i<len)
            {
                tmp = ((DBASE)coef[i]*bNum.coef[j] + (DBASE)newNum.coef[i+j] + (DBASE)k);
                newNum.coef[i+j] = (BASE)tmp;
                k=(BASE)(tmp>>b);
                i++;
            }
            newNum.coef[len+j] = k;
        }
        j++;
    }
    newNum.len = len + bNum.len;
    while(newNum.len>1 && newNum.coef[newNum.len-1]==0){
        newNum.len--;
    }

    return newNum;

}
BN BN:: operator / (const BASE& num){
    int j =0;
    DBASE tmp =0;
    BN newNum(len);

    BASE r =0;
    int b =BASE_SIZE;
    while (j<len){
        tmp= (((DBASE)r<<b)+(DBASE)coef[len-1-j]);
        newNum.coef[len-1-j]=(BASE)(tmp/(DBASE)num);
        r =(BASE)(tmp%(DBASE)num);
        j++;

    }
    newNum.len=len;
    while(newNum.len>1&&newNum.coef[newNum.len-1]==0){
        newNum.len--;
    }
    return newNum;
}
BN BN::operator%(const BASE &num) {
    int j=0;
    DBASE tmp=0;
    BASE r=0;
    int b =BASE_SIZE;
    BN newNum (1);
    while(j<len){
        tmp=(((DBASE)r<<b)+(DBASE)coef[len-1-j]);
        r =(BASE)(tmp % (DBASE)num);
        j++;
    }
    newNum.coef[0]=r;
    return newNum;
}
void BN::cout_10() {
    BN newNum =*this;
    BN zero(newNum.len);
    string s;
    zero.len=newNum.len;
    while(newNum != zero){
        BN t=newNum%10;
        s.push_back(t.coef[0]+'0');
        newNum=newNum/10;
        zero.len=newNum.len;
    }
    reverse(s.begin(),s.end());
    cout<<"Base10= "<<s<< endl;
}
void BN::cin_10() {
    int j =0;
    string s;
    cout <<"Base10: ";
    getline(cin,s);
    int k=s.length();///длина строки пользователя
    BASE t=0;
    DBASE tmp =0;

    int b = BASE_SIZE;

    BN bNum((k-1)/(b/4)+1);

    while (j<k){
        if ('0'>s[j] || s[j]>'9'){
            throw invalid_argument("Invalid arguments");
        }
        t =s[j] -'0';///преобразование из строки в число
        bNum=bNum*((BASE)10);

        BN newNum;
        newNum.coef[0]=(BASE)t;
        bNum+=newNum;
        j++;
    }

    bNum.len=bNum.maxlen;
    while (bNum.len>1 && bNum.coef[bNum.len-1]==0){
        bNum.len--;

    }
    *this=bNum;
}

BN BN::operator/(const BN &num) {

    if(num.len == 1 && num.coef[0] == 0){
        throw invalid_argument("Invalid arguments1.");
    }
    if(*this < num){///маленькое делим на большое
        BN finNum(1);
        return finNum;
    }

    if(num.len == 1){
        return *this / num.coef[0];
    }

    int m = len-num.len;/// длина ответа
    int base_size = BASE_SIZE;
    DBASE b = ((DBASE)1<<base_size);///основание числа
    DBASE d = b/(DBASE)(num.coef[num.len-1] + (BASE)1);///для нормализации
    int j = m;
    int k = 0;///перенос

    BN newNum = *this;
    newNum *= d;
    BN delNum = num;
    delNum *= d;

    BN finNum(m+1);
    finNum.len = m+1;

    if(newNum.len == len){/// сравниваем длину нормализованного с исходным
        newNum.maxlen++;
        newNum.len = maxlen;
        delete []newNum.coef;
        newNum.coef = new BASE[maxlen];
        for (int i = 0; i <  len; i++){
            newNum.coef[i] = coef[i];
        }
        newNum *= d;
        newNum.len++;
        newNum.coef[newNum.len-1] = 0;
    }

    while (j>-1){
        DBASE q = (DBASE)( (DBASE)( (DBASE)( (DBASE)(newNum.coef[j + delNum.len]) * (DBASE)(b) ) + (DBASE)( newNum.coef[j + delNum.len - 1] ) ) / (DBASE)( delNum.coef[delNum.len - 1] ) );
        DBASE r = (DBASE)( (DBASE)( (DBASE)( (DBASE)(newNum.coef[j + delNum.len]) * (DBASE)(b) ) + (DBASE)( newNum.coef[j + delNum.len - 1] ) ) % (DBASE)( delNum.coef[delNum.len - 1] ) );

        if(q == b || (DBASE)( (DBASE)(q) * (DBASE)( delNum.coef[delNum.len-2] ) ) > (DBASE)( (DBASE)( (DBASE)(b) * (DBASE)(r) ) + (DBASE)( newNum.coef[j+delNum.len-2] ) )){
            q--;
            r = (DBASE)(r) + (DBASE)(delNum.coef[delNum.len - 1]);
            if((DBASE)(r)<b){
                if(q == b || (DBASE)( (DBASE)(q) * (DBASE)(delNum.coef[delNum.len-2]) ) > (DBASE)( (DBASE)( (DBASE)(b) * (DBASE)(r) ) + (DBASE)( newNum.coef[j+delNum.len-2] ) )){
                    q--;
                }
            }
        }

        BN u(delNum.len + 1);
        u.len = delNum.len + 1;
        for(int i = 0; i < delNum.len + 1; i++){
            u.coef[i] = newNum.coef[j+i];///кусок делимого длины делителя
        }

        if(u <  delNum*(BASE)(q)){///проверка
            q--;
        }

        u = u -  delNum*(BASE)(q);///отнимаем делитель на q
        finNum.coef[j] = (BASE)(q);

        for(int i = 0; i < delNum.len + 1; i++){
            newNum.coef[j+i] = u.coef[i];
        }

        j--;
    }

    while(finNum.len>1 && finNum.coef[finNum.len-1]==0){
        finNum.len--;
    }

    return finNum;
}

BN BN:: operator %(const BN& num){
    if(num.len == 1 && num.coef[0] == 0){
        throw invalid_argument("Invalid arguments.");
    }
    if(*this < num){
        return *this;
    }

    if(num.len == 1){
        return *this % num.coef[0];
    }

    int m = len-num.len;
    int base_size = BASE_SIZE;
    DBASE b = ((DBASE)( 1 )<<( base_size) );
    BASE d = (BASE)( (DBASE)( b ) / (DBASE)( ( num.coef[num.len-1] ) + (BASE)( 1 ) ) );
    int j = m;
    int k = 0;

    BN newNum = *this;
    newNum *= d;
    BN delNum = num;
    delNum *= d;
    if(newNum.len == len){
        newNum.maxlen++;
        newNum.len = maxlen;
        newNum.coef = new BASE[maxlen];
        for (int i = 0; i <  len; i++){
            newNum.coef[i] = coef[i];
        }
        newNum *= d;
        newNum.len++;
        newNum.coef[newNum.len-1] = 0;
    }

    while (j>-1){
        DBASE q = (DBASE)( (DBASE)( (DBASE)( (DBASE)(newNum.coef[j + delNum.len]) * (DBASE)(b) ) + (DBASE)( newNum.coef[j + delNum.len - 1] ) ) / (DBASE)( delNum.coef[delNum.len - 1] ) );
        DBASE r = (DBASE)( (DBASE)( (DBASE)( (DBASE)(newNum.coef[j + delNum.len]) * (DBASE)(b) ) + (DBASE)( newNum.coef[j + delNum.len - 1] ) ) % (DBASE)( delNum.coef[delNum.len - 1] ) );
        if(q == b || (DBASE)( (DBASE)(q) * (DBASE)( delNum.coef[delNum.len-2] ) ) > (DBASE)( (DBASE)( (DBASE)(b) * (DBASE)(r) ) + (DBASE)( newNum.coef[j+delNum.len-2] ) )){
            q--;
            r = (DBASE)(r) + (DBASE)(delNum.coef[delNum.len - 1]);
            if((DBASE)(r)<b){
                if(q == b || (DBASE)( (DBASE)(q) * (DBASE)( delNum.coef[delNum.len-2]) ) > (DBASE)( (DBASE)( (DBASE)(b) * (DBASE)(r) ) + (DBASE)( newNum.coef[j+delNum.len-2] ) )){
                    q--;
                }
            }
        }
        BN u(delNum.len + 1);
        u.len = delNum.len + 1;
        for(int i = 0; i < delNum.len + 1; i++){
            u.coef[i] = newNum.coef[j+i];
        }

        if(u < delNum*(BASE)(q)){

            q--;
        }

        u = u - (  delNum * (BASE)(q));


        for(int i = 0; i < delNum.len + 1; i++){
            newNum.coef[j+i] = u.coef[i];
        }


        j--;
    }
    while(newNum.len>1 && newNum.coef[newNum.len-1]==0){
        newNum.len--;
    }

    return newNum / d;
}
istream& operator >> (istream &in, BN & bNum){
    char* s = new char[1000];
    int b = BASE_SIZE
    int j = 0;
    int k = 0;
    unsigned int tmp = 0;

    in.getline(s, 1000);
    bNum.len = (strlen(s)-1)/(b/4)+1;
    bNum.maxlen = bNum.len;
    bNum.coef = new BASE[bNum.maxlen];
    for (int i=0; i<bNum.len;i++){
        bNum.coef[i]=0;
    }
    for(int i = strlen(s)-1; i>-1; i--){
        if('0'<=s[i] && s[i]<='9'){
            tmp = s[i] - '0';
        }
        else if('a'<=s[i] && s[i]<='f'){
            tmp = s[i] - 'a' + 10;
        }
        else if('A'<=s[i] && s[i]<='F'){
            tmp = s[i] - 'A' + 10;
        }
        else{
            throw invalid_argument("Invalid arguments.");
        }

        bNum.coef[j] |= tmp<<(k*4);
        k++;
        if(k>= b / 4){
            k=0;
            j++;
        }
    }
    return in;
}

ostream& operator << (ostream& st, const BN& num)
{
    int size = BASE_SIZE;
    for (int j = num.len - 1; j >= 0; j--)
    {
        st.width(size / 4);//вычисляем сколько может влезть в коэфициент (4 бита)
        st.fill('0');//заполняем нолями пустые места
        st << hex << (int)num.coef[j];
    }
    return st;
}
void test(){
    srand( time(NULL) );
    int M = 1000;
    int T = 1000;

    BN A;
    BN B;
    BN C;
    BN D;
    do
    {

        int n = rand()%M + 1;
        int m = rand()%M + 1;
        BN E (n, 1);
        BN G (m, 1);
        A = E;
        B = G;
        C = A / B;
        D = A % B;
        cout<<"m: "<<m<<" ";
        cout<<"n: "<<n<<" ";
        cout<<"T: "<<T<<endl;

    }
    while (A == C * B + D && A - D == C*B && D<B && --T);
    cout<<T<<endl;
    // if(T!=0){
    //     // cout<<"A: "<<A<<endl;
    //     cout<<"B: "<<B<<endl;
    //     // cout<<"C: "<<C<<endl;
    //     cout<<"D: "<<D<<endl;
    // }



}
int main() {
   //BN slave;
   //slave.cin_10();
   //slave.cout_10();
   test();
    return 0;

}
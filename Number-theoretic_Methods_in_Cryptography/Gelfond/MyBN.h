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
    bool operator < (const BN&) const;
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
    BN pow_int(int);
    BN root(int);
    BN gcd(BN);
    int log(int);
    BN pow_BN(BN);
    BN random_bound(BN, BN);

    bool Miller_Rabin_test(int);

    BN fastPow(int, BN);

    friend BN operator*(BASE num, BN bNum) {  return bNum*num; }

    friend ostream& operator << (ostream &, const BN &);
    friend istream& operator >> (istream &, BN &);
};
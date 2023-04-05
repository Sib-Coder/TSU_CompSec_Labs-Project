#include <iostream>
#include <cmath>
using namespace std;
class complex{
    double re, im;

public:
    complex(double Re = 0, double Im = 0);

    double getRe() {// посмотреть re
        return re;
    };
    void setRe(double);// поменять re

    double getIm()//посмотреть im
    {
        return im;
    };
    void setIm(double);//поменять im

    bool operator == (complex);
    bool operator != (complex);

    double mod() {
        return sqrt(re * re + im * im);//модуль
    };

    complex operator + (const complex &);
    complex operator - (const complex &);
    complex operator * (const complex &);
    complex operator / (const complex &);

    friend ostream &operator<<(ostream &st, const complex &x)// ввод
    {
        if (x.im > 0)
            st << x.re << " + " << x.im << " * i";
        else if (x.im < 0)
            st << x.re << " - " << -1 * x.im << " * i";
        else
            st << x.re;
        return st;
    };

    friend istream &operator>>(istream &st, complex &x) {// вывод
        st >> x.re;
        st >> x.im;
        return st;
    };

};

complex::complex(double Re, double Im)
{
    re = Re;
    im = Im;
}

void complex :: setRe (double Re)
{
    re = Re;
}
void complex :: setIm(double Im)
{
    im = Im;
}

bool complex ::operator == (complex x) //сравнение
{
 if (re == x.re && im== x.im)
     return true;
    return false;
}
bool complex ::operator != (complex x) // отрицательное сравнение
{
    if (re != x.re || im != x.im )
        return true;
    return false;
}
complex complex::operator + (const complex &x) //сложение
{
    complex res;
    res.re = re + x.re;
    res.im = im + x.im;
    return res;
}
complex complex:: operator - (const complex &x)//вычитание
{
    complex res;
    res.re = re - x.re;
    res.im = im - x.im;
    return res;
}

complex complex::operator * (const complex &x)// умножение
{
    complex res;
    res.re = re * x.re - im * x.im;
    res.im = re * x.im - re * x.re;
    return res;
}
complex complex::operator / (const complex &x)// деление
{
    complex res;
    res.re = (re * x.re + im * x.im)/(x.re * x.re + x.im * x.im);
    res.im = (im * x.re - re * x.im)/(x.re * x.re + x.im * x.im);
    return res;
}

int main() {
    complex fi, sec(-7,6);
    cout << "Enter first \n";
    cin >> fi;
    cout << "First:"<< fi << "\nSecond:" << sec;
    if (fi == sec)
        cout << "\nThey are equal";
    if (fi != sec)
        cout << "\nThey are not equal";
    fi.setRe(10);
    sec.setIm(10);
    cout << "\nFirst's re change:" << fi.getRe()<< "\nSecond's im change:"<< sec.getIm();
    cout << "\nFirst module:"<< fi.mod()<< "\nSecond module:"<< sec.mod();
    cout << "\nFirst + second:" << fi + sec;
    cout << "\nFirst - second:" << fi - sec;
    cout << "\nFirst * second:" << fi * sec;
    cout << "\nFirst / second:" << fi / sec;
}

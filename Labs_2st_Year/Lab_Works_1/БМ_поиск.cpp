#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

class String {
    char *str;
    int len;
public:
    String(int l = 0) {
        str = new char[l + 1];
        len = 0;
        strcpy(str, "\0");
    };

    String(const char *a) {
        str = new char[strlen(a) + 1];
        strcpy(str, a);
        len = strlen(a);
    };

    String(String &a) {
        str = new char[a.len + 1];
        len = a.len;
        strcpy(str, a.str);
    };

    ~String() {
        if (str) delete[]str;
        str = NULL;
    }

    int Len();

    String &operator=(const String &);

    char &operator[](int);

    bool operator==(String &);

    bool operator!=(String &);

    String operator+(const String &);

    String &operator+=(const String &);

    friend istream &operator>>(istream &, String &);

    friend ostream &operator<<(ostream &, String &);

    int BMH_search(String &);

    String operator () (int,int);
};

int String::Len() {
    return len;
}

String &String::operator=(const String &a) {
    if (this != &a) {
        delete[] str;
        str = new char[a.len + 1];
        strcpy(str, a.str);
        len = a.len;
    }
    return *this;
}

char &String::operator[](int a) {
    if (a < 0 || a >= len) exit(1);
    return str[a];
}

bool String::operator==(String &a) {
    if (strcmp(str, a.str)) return false;
    return true;
}

bool String::operator!=(String &a) {
    if (strcmp(str, a.str)) return true;
    return false;
}

String String::operator+(const String &a) {
    String z(len + a.len + 1);
    z.len = len + a.len;
    strcpy(z.str, str);
    strcat(z.str, a.str);
    return z;
}

String &String::operator+=(const String &a) {
    char *t = new char[len + 1];
    strcpy(t, str);
    delete[] str;
    len = len + a.len;
    str = new char[len + 1];
    strcpy(str, t);
    strcat(str, a.str);
    delete[] t;
    return *this;
}

istream &operator>>(istream &in, String &a) {
    in >> a.str;
    a.len = strlen(a.str);
    return in;
}

ostream &operator<<(ostream &out, String &a) {
    cout << a.str;
    return out;
}

int String::BMH_search(String &a) {//БМ поиск
    int m = a.len;
    int n=len;//длина текста
    int t[256];
    fill_n(t, 256, m);// len obraz
    for (int i = 0; i < m - 1; i++) { //tablicha char
        t[(int)a.str[i]] = m-1-i;
    }
    int i = m-1,j = m-1;
    while ( i < n && j>=0) {
        int k = i;
        j = m-1;
        while (j>=0) {
            if(str[k]!=a.str[j]) {
                i += t[str[i]];
                j = m - 1;
                break;
            }
            j--;
            k--;
        }
    }
    if(j>=0) return -1;
    else return i+1-m;
}
String String::operator () (int a,int b) {//выделяет подстроку из исходной строки с i-ого по j-ый символы
    if(a<=b && b<=len) {
        String s(b-a);
        strncpy(s.str,str+a,b-a);
        return s;
    }
    exit(1);
}


int main() {
    String a, b("footballer");
    String c("ssch");
    a = b + c;
    cout<<a<<endl;
    a+=c;
    b = "ssch";
    if(c==b) cout<<"equal\n";//c=aacb & b=aacb
    b = a;
    if(c!=b) cout<<"not equal\n";//c=aacb & a=abchaaacbjaacbaacb


    a = "footballer";
    b = "ball";
    cout<<"char_start_string2="<<a.BMH_search(b)<<endl<<"string1="<<a<<"\nstring2="<<b<<endl;
    c = a(2,6);
    cout<<"string(i,j-1)="<<c<<endl;
    cout<<"\n";
    String h;
    cin>>h;
    cout<<h<<"\t"<<h.Len();

    return 0;
}
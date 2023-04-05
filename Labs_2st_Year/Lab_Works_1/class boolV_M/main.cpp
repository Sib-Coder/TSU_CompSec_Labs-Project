#include <iostream>
#include <cstring>
#include <stdexcept>
#include <fstream>

using namespace std;

// Класс булев вектор
class BoolV {
    unsigned int *v;
    int nbit, m; // nbit – количество бит вектора, m – количество элементов массива v
public:
    BoolV(int nn = 1); // формируется булев вектор из nn бит; все биты со значениями 0
    BoolV(const char *); // формируется булев вектор по строке из нулей и единиц
    BoolV(const BoolV &);//конструктор копирования

    ~BoolV();

    void Set1(int); // устанавливает указанный бит в 1
    void Set0(int); // устанавливает указанный бит в 0
    int operator[](int);//возвращает бит из вектора
    BoolV operator=(const BoolV &);
    BoolV operator|(const BoolV &);//побитовая или
    BoolV operator&(const BoolV &);//побитовая И
    BoolV operator~();//инверсия
    bool operator==(const BoolV &); // равенство векторов
    friend ostream &operator<<(ostream &, const BoolV &);
    friend istream &operator>>(istream &, BoolV &);
    int weight();//вес
};

// Класс булева матрица
class BoolM {
    BoolV *bm;
    int m, n; // m – количество строк, n – количество столбцов
public:
    BoolM(int k = 1, int l = 1); // формируется нулевая булева матрица размера kl
    BoolM(const BoolM &);
    BoolV &operator[](int);
    BoolM operator=(const BoolM &);
    friend ostream &operator<<(ostream &, BoolM &);
    int BuildMatrix();//построение матрицы

};

BoolV::BoolV(int nn) {// формируется булев вектор из nn бит; все биты со значениями 0
    nbit = nn;
    m = ((nbit - 1) / 32) + 1;
    v = new unsigned int[m];
    for (int i = 0; i < m; i++) v[i] = 0;
}

BoolV::BoolV(const char *c) {// формируется булев вектор по строке из нулей и единиц
    nbit = strlen(c);
    m = ((nbit - 1) / 32) + 1;
    v = new unsigned int[m];
    for (int i = 0; i < m; i++) v[i] = 0;
    for (int i = 0; i < nbit; i++) if (c[i] != '0') v[i / 32] = v[i / 32] | (1 << (i % 32));
}

BoolV::BoolV(const BoolV &V) {//конструктор копирования
    nbit = V.nbit;
    m = V.m;
    v = new unsigned int[m];
    for (int i = 0; i < m; i++) v[i] = V.v[i];
}

BoolV::~BoolV() {//удаляется массив
    delete[]v;
}

void BoolV::Set1(int k) {//
    if ((k < nbit) && (k >= 0)) {
        v[k / 32] = v[k / 32] |
                    (1 << (k % 32));//вычисляем в каком элементе стоит эл, в каком бите К , сдвигают единицу на место К
    } else { cout << "Out of bounds index"; }
}

void BoolV::Set0(int k) {//заменяем к бит на 0
    if ((k < nbit) && (k >= 0)) {
        v[k / 32] = v[k / 32] & (~(1 << (k % 32)));
    } else { cout << "Out of bounds index"; }
}

bool BoolV::operator==(const BoolV &newBoolV) {//сравнение
    if (nbit != newBoolV.nbit || m != newBoolV.m) {
        return false;
    }

    for (int i = 0; i < m; i++) {
        if (v[i] != newBoolV.v[i]) {
            return false;
        }
    }

    return true;
}

int BoolV::operator[](int k) {//возвращает бит из вектора
    if ((k < nbit) && (k >= 0)) {
        if ((v[k / 32] & (1 << (k % 32))) == 0) return 0;
        else return 1;
    } else {
        cout << "Out of bounds index";//за пределами
        return -1;
    }
}

BoolV BoolV::operator=(const BoolV &V) {//один булев вектор приравниваем другому
    if (this != &V) {
        m = V.m;
        nbit = V.nbit;
        delete[]v;
        v = new unsigned int[m];
        for (int i = 0; i < m; i++) v[i] = V.v[i];
    }
    return *this;
}

BoolV BoolV::operator|(const BoolV &vec) {//побитовая или
    BoolV copy = *this;
    if (nbit != vec.nbit)//сравниваем колличество бит
    {
        cout << "No";
        return 0;
    }
    for (int i = 0; i < m; i++)//пробегаем
    {
        copy.v[i] |= vec.v[i];
    }
    return copy;
}

BoolV BoolV::operator&(const BoolV &newBoolV) {//побитовая и
    BoolV vec;
    if(nbit>newBoolV.nbit){
        vec=*this;
        for(int i=0;i<newBoolV.m;i++){
            vec.v[i]=vec.v[i]&newBoolV.v[i];
        }
        for(int i=newBoolV.m;i<m;i++){//конец 0
            vec.v[i]=0;
        }
    }
    else{
        vec=newBoolV;
        for(int i=0;i<m;i++){
            vec.v[i]=vec.v[i]&v[i];
        }
        for(int i=m;i<newBoolV.m;i++){//конец ноликами
            vec.v[i]=0;
        }
    }
    return vec;
}

BoolV BoolV::operator~() {
    BoolV vec(*this);
    for(int i=0;i<m-1;i++){
        vec.v[i]=~vec.v[i];//инвертируем все элементы
    }
    vec.v[m-1]=~(vec.v[m-1]<<(nbit%32));//избавляемся от лишних 1
    vec.v[m-1] = vec.v[m-1]>>(nbit%32);//возвращаем на место
    return vec;
}

istream &operator>>(istream &in, BoolV &vec) {//ввод
    char *buff = new char[1000];
    in.getline(buff, 1000);
    vec = BoolV(buff);
    delete[] buff;
    return in;
}


ostream &operator<<(ostream &out, const BoolV &vec) {//вывод
    for (int i = 0; i < vec.nbit; i++) {
        if ((vec.v[i / 32] & (1 << (i % 32))) == 0) {
            out << 0;
        } else {
            out << 1;
        }
    }
    return out;
}

BoolM::BoolM(int k, int l) {//создаёт будеву матрицу из бул векторов
    m = k;
    bm = new BoolV[m];
    n = l;
    BoolV v(n);
    for (int i = 0; i < m; i++) {
        bm[i] = v;
    }
}

BoolM::BoolM(const BoolM &M) {//конструктор копирования (размерности и строки)
    n = M.n;
    bm = new BoolV[m = M.m];
    for (int i = 0; i < m; i++) {
        bm[i] = M.bm[i];
    }
}

BoolV &BoolM::operator[](int k) {//возвращает строку
    return this->bm[k];
}

BoolM BoolM::operator=(const BoolM &M) {//приравнивание
    if (this != &M) {
        n = M.n;//колличество столбцов
        delete[]bm;
        bm = new BoolV[m = M.m];
        for (int i = 0; i < m; i++) {//пробегаем по строкам и записываем новые строки
            bm[i] = M.bm[i];
        }
    }
    return *this;
}

ostream &operator<<(ostream &out, BoolM &M) {//выводит строки
    for (int i = 0; i < M.m; i++) out << M.bm[i] << '\n';
    return out;
}

int BoolV::weight() {//считаем вес вектора ( колличество 1 )
    int weight = 0;
    for (int i = 0; i < nbit; i++) {
        if ((v[i / 32] & (1 << (i % 32))) != 0) {
            weight++;
        }
    }
    return weight;
}

void topsort(BoolM &M, int m, int *a) {
    BoolV v0(m); // Какие вершины использовали rоторые уже рассмотрели
    BoolV v1(m); // Вершины в которые нет пути
    BoolV v2(m); // Ответ на данном шаге цикла while
    BoolV NullV(m);//вектор с 0 везде
    int k = 0;
    for (int i = 0; i < m; i++) {//jтветы заполняем нулями
        a[i] = 0;
    }
    while (v0.weight() != m) {//
        v1 = NullV;//обноляем на каждом шаге
        for (int i = 0; i < m; i++) {
            v1 = v1 | M[i];//находим вершины в которые у нас есть пути

        }
        v1 = ~v1;// вершины в которые у нас нет пути
        v2 = v1 & (~v0);//нет пути но мы их не использовались
        if (v2 == NullV) {//условие для неприминимости топологической сортировки
            throw invalid_argument("Error Matrix");
        }
        for (int i = 0; i < m; i++) { // пробегаем по всему v2

            if (v2[i] == 1) {
                a[k] = i + 1;//добавляем вершину в массив ответов
                M[i] = NullV;//удаляем исходящие пути
                k++;//увеличиваем указатель для массива ответов
            }
        }

        v0 = v0 | v2;//добавляем рассмотренные вершины


    }
}

int BoolM::BuildMatrix() {//построение матрицы из файла
    ifstream fin("graf.txt");
    if (fin.is_open()) {
        int a, b;
        int m;
        fin >> m;//колличество вершин
        BoolM BM(m, m);//строим пустую матрицу
        do {
            fin >> a;// вершина начала пути
            fin >> b;//вершина конца пути
            BM[a - 1].Set1(b - 1);// установка единицы в ячейку матрицы
        } while (!fin.eof());// пока можем считать с файла
        fin.close();
        *this = BM;
        return m;//возвращаем колличество вершин
    }
    return 0;
}

void matrix() {//матрица+ответ сортировки
    BoolM a;
    int m;
    m = a.BuildMatrix();
    int *b = new int[m];//массив ответов
    cout << a;//выводим матрицу
    topsort(a, m, b);//производим топологическую сортировку
    printf("Otvet: ");
    for (int i = 0; i < m - 1; i++) {//выводим массив ответов
        cout << b[i] << ", ";
    }
    cout << b[m - 1] << endl;
}

int main() {
    BoolV dann(10 );
    cout<<"BoolV: "<<endl<<dann<<endl;
    BoolM dan(2,3);
    cout<<"BoolM_sring_k:"<<endl<<dan[1]<< endl;
    cout<<"matritsa: "<< endl;
    matrix();
}
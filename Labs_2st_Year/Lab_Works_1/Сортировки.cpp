#include <iostream>
#include <chrono>

using namespace std;

class Array {
    int *a, n;
public:
    /// d – диапазон псевдослучайных чисел для неупорядоченного массива (при t = 1)
    Array(int len = 1, int t = 1, int d = 10) {
        a = new int[len];
        n = len;/// len – число элементов в массиве
        if (t == 1) { /// t = 1 – неупорядоченный массив
            for (int i = 0; i < n; i++) {
                a[i] = rand() % d;
            }
        } else if (t == 2) { /// t = 2 – массив, упорядоченный по неубыванию
            a[0] = rand() % d;
            for (int i = 1; i < n; i++) {
                a[i] = a[i - 1] + rand() % d;
            }
        } else if (t == 3) {/// t = 3 – массив, упорядоченный по невозрастанию
            a[n - 1] = rand() % d;
            for (int i = n - 2; i >= 0; i--) {
                a[i] = a[i + 1] + rand() % d;
            }
        } else {
            exit(1);
        }
    };

    Array(int *b, int len) { /// конструктор 2: по массиву
        a = new int[len];
        n = len;
        for (int i = 0; i < n; i++) {
            a[i] = b[i];
        }
    };

    Array(Array &b) {///конструктор копирования
        a = new int[b.n];
        n = b.n;
        for (int i = 0; i < n; i++) {
            a[i] = b.a[i];
        }
    };

    ~Array() {
        if (a) delete[]a;
        a = NULL;
    }///деструктор

    Array &operator=(const Array &);///оператор присваивания
    int &operator[](int);///оператор для получения i-ого элемента

    bool Test(); /// проверка на упорядоченность по неубыванию
    bool operator==(Array); /// равенство элементов массивов (но не порядка)

    void Shell_sort();

    void Heapsort();

    void heapify(int, int);

    void Hoar_sort();

    void Bit_sort(int, int, int, bool);

    int major_bit();// для Bit_sort
    friend istream &operator>>(istream &, Array &);

    friend ostream &operator<<(ostream &, Array &);
};

Array &Array::operator=(const Array &newArr) {///оператор присваивания
    if (this == &newArr)
        return *this;
    delete[] a;
    n = newArr.n;
    a = new int[n];
    for (int i = 0; i < n; i++) {
        a[i] = newArr.a[i];
    }
    return *this;
};

int &Array::operator[](int b) {///оператор для получения i-ого элемента
    if (b < 0 || b >= n) return a[0];
    return a[b];
}

bool Array::Test() { /// проверка на упорядоченность по неубыванию
    for (int i = 1; i < n; i++) {
        if (a[i] < a[i - 1]) return false;
    }
    return true;
}

bool Array::operator==(Array b) {/// равенство элементов массивов (но не порядка)
    if (n != b.n) return false;
    int len = n;
    for (int i = 0; i < n; i++) {
        bool ch = false;
        for (int j = 0; j < len; j++) {
            if (a[i] == b.a[j]) {
                ch = true;
                b[j] = b[len - 1];
                len--;
                break;
            }
        }
        if (ch == false) return false;
    }
    return true;
}

istream &operator>>(istream &in, Array &obj) {///оператор ввода
    int len;
    cout << "len: ";
    in >> len;
    cout << "\n massiv: ";
    int *arr;
    arr = new int[len];
    for (int i = 0; i < len; i++) {
        in >> arr[i];
    }
    obj = Array(arr, len);
    delete[] arr;
    return in;
}

ostream &operator<<(ostream &out, Array &a) {///оператор вывода
   out << "out_massiv: ";
    for (int i = 0; i < a.n; i++) {
        out << a[i] << " ";
    }
    out << "\n";
    return out;
}

void Array::Shell_sort() {///сортировка Шела
    for (int gap = n / 2; gap > 0; gap /= 2) {///разбиваем на шаги
        for (int b = 0; b < gap; b++) {///0 до шаг ( 1 элемент нашего подмассива)
            for (int i = b + gap; i < n; i += gap) {///следующий элемент
                int x = a[i];
                int k;
                for (k = i - gap; k >= 0 && a[k] > x; k -= gap) {///смотрим на предеидушие элементы и сравниваем с нашим
                    a[k + gap] = a[k];
                }
                a[k + gap] = x;
            }
        }
    }
}

int change(int *arr, int l, int r) {///функция сортировки для удобства
    if (l >= r) {
        return 0;
    }
    int i = l;
    int j = r;
    int x = arr[(l + r) / 2];
    while (i <= j) {
        while (arr[i] < x) {
            i++;
        }
        while (arr[j] > x) {
            j--;
        }
        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }

    change(arr, l, j);///вызов рекурсии
    change(arr, i, r);///вызов рекурсии
    return 0;
}

void Array::Hoar_sort() {///сортировка Хоара
    change(a, 0, n - 1);
}

void Array::heapify(int n, int i) {///функция просеивания
    int j = 2 * i + 1;
    int x = a[i];
    bool f = true;
    while (j < n && f) {
        if (j + 1 < n && a[j + 1] > a[j]) j++;
        if (a[j] > x) {
            a[i] = a[j];
            i = j;
            j = 2 * i + 1;
        } else f = false;
    }
    a[i] = x;
}

void Array::Heapsort() {///пираимидальная сортировка
    for (int i = n / 2 - 1; i >= 0; i--)
        this->heapify(n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(a[0], a[i]);
        this->heapify(i, 0);
    }
}

void Array::Bit_sort(int l = 0, int r = 0, int k = 0, bool flag = true) {///побитовая сортировка
    if (flag) {
        flag = false;
        l = 0;
        r = n - 1;
        k = this->major_bit();
    }
    if (!(l >= r || k < 0)) {
        int i = l, j = r;
        int mask = 1 << k;
        while (i <= j) {
            while (i <= j && !(a[i] & mask)) i++;
            while (i <= j && a[j] & mask) j--;
            if (i < j) swap(a[i++], a[j--]);
        }
        this->Bit_sort(l, j, k - 1, flag);
        this->Bit_sort(i, r, k - 1, flag);
    }
}

int Array::major_bit() {///поиск главного бита
    int max = a[0];
    for (int i = 0; i < n; i++) {
        if (a[i] > max) max = a[i];
    }
    int k = 0;
    while (max) {
        max >>= 1;
        k++;
    }
    return k - 1;
}

void test() {

    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;
    Array t(100, 3);
    Array t1(100, 3);
    Array t2(100, 3);
    Array t3(100, 3);

    double seconds = 0;
    auto time1 = high_resolution_clock::now();
    t.Shell_sort();
    auto time2 = high_resolution_clock::now();
    duration<double, std::milli> ms_double = time2 - time1;
    cout << ms_double.count() << " ms" << endl;
    time1 = high_resolution_clock::now();
    t1.Bit_sort();
    time2 = high_resolution_clock::now();
    ms_double = time2 - time1;
    cout << ms_double.count() << " ms" << endl;
    time1 = high_resolution_clock::now();
    t2.Heapsort();
    time2 = high_resolution_clock::now();
    ms_double = time2 - time1;
    cout << ms_double.count() << " ms" << endl;
    time1 = high_resolution_clock::now();
    t3.Hoar_sort();
    time2 = high_resolution_clock::now();
    ms_double = time2 - time1;
    std::cout << ms_double.count() << " ms" << endl;
}

int main() {
    Array t;
    cin >> t;
    t.Shell_sort();
    cout << t;
    test();

    return 0;
}

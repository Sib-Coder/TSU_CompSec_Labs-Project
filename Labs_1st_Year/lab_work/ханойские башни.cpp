#include<stdio.h>
void hanoi(int n, int i, int k)
///n-колличесвотво дисков
///i-начальный стержень
///k-конечный стержень
{
    if (n == 1) {
        printf("переместите диск 1 со стержня %d в %d.\n", i, k);}
    else{
        int tmp=6-i-k;
        //вычисление временного столба исходя из их суммы 1+2+3=6
        hanoi(n-1, i, tmp);
        printf("переместите диск %d со стержня %d в %d\n",n,  i, k);
        hanoi(n-1,tmp , k);}
}
int main ()
{
    int kol, start, finish;
    printf("колличество дисков:");
        scanf("%d", &kol);
    printf("начальный стержень:");
        scanf("%d", &start);
    printf("конечный стержень:");
        scanf("%d", &finish);
    hanoi(kol,start,finish);
    return 0;
}

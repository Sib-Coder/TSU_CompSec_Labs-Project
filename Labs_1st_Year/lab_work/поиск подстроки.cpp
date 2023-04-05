#include <stdio.h>
int poisk ( char *s, char *c,char n)
{
    int j,i; //счётчик циклов
    int lenC,lenS; // длины строк
    for (lenC=0; c[lenC];lenC++);//поиск размера строки С
    for(lenS=0; s[lenS]; lenS++);//поиск размера строки S
    for( i=0;i<=lenS-lenC; i++)// устловия адекватности работы
    {
        for(j=0;s[i+j] == c[j];j++)//цикл на посимвольное совпадение
            if(j-lenC==1 && i==lenS-lenC && !(n-1)) return i;
            if(j==lenC)
                if(n-1) n--;
                else return i;
    }
    return -1;//возврат в виду отсутствия строки
}
int main()
{
    char *s="Daniil";//строка
    char  *c="Dan";//подстрока
    printf("Строка:%s\n", s);
    printf("Подстрока:%s\n", c);
    int i, n=0;
    for (i=1; n!= -1;i++)
    {
        n= poisk(s,c,i);
        if(n>=0)
            printf("Подстрока найдена и начинается с символа  %d строки\n", n);
    }
}


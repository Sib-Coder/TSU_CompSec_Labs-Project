#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "library.h"

#define TEMP 20
#define STEP 0.2
#define COUNT 10000

char *playfairDecipher(char *key, char *in, char *out, int len);
int main(int argc, char * argv[]);
float playfairCrack(char *text, int len, char* maxKey);

double scoreTextQgram(char *text, int len);

int main(int argc, char *argv[])
{
	printf("Before you start, create a file named 'cipher text.txt' \n\t put the encrypted text in it and then to start press any button.\n");
	puts("");
	printf("\t\t\tWARINING!!!\n");
	puts("");
	printf("The program doesn't stop itself so \n\t as soon as you think you need to finish click CTRL+C !!!\n");
	puts("");
	system("pause");

	FILE* f_in = fopen("cipher text.txt", "r");
	if (f_in == NULL)
	{
		fprintf(stderr, "Failed to open file cipher text.txt\n");
		perror("");
		return 1;
	}

	char* cipher = NULL;
	int len = 0;
	while (!feof(f_in))
	{
		char c;
		fscanf(f_in, "%c", &c);
		if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		{
			if (c >= 97 && c <= 122)
			{
				c = c - 97 + 65;
			}
			cipher = (char*)realloc(cipher, (len + 1) * sizeof(char));
			cipher[len] = c;
			len++;
		}
	}
	len--;
	fclose(f_in);

	if (len % 2)
	{
		printf("The size of the ciphertext is odd, please check whether the ciphertext is correct\n");
		free(cipher);
		return 1;
	}

	char *out = (char*)malloc(sizeof(char)*(len + 1));
	srand((unsigned)time(NULL)); // каждый раз будет задаваться случайный ключ

	printf("Running playfaircrack, it migth take more than 1 minute\n");

	char key[] = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
	int i = 0;
	double score, maxscore = -99e99;
	// программа работает пока специально не прекратить работу

	while(true){
		i++;
		score = playfairCrack(cipher, len, key);
		if (score > maxscore) {
			maxscore = score;
			printf("best score so far: %f, on iteration %d\n", score, i);
			printf("    Key: '%s'\n", key);
			playfairDecipher(key, cipher, out, len);
			printf("    plaintext: '%s'\n", out);
		}
	}

	free(out);
	return 0;
}

void exchange2letters(char *key) {
	int i = rand() % 25;
	int j = rand() % 25;
	char temp = key[i];
	key[i] = key[j];
	key[j] = temp;
}

void swap2rows(char *key) {
	int i = rand() % 5;
	int j = rand() % 5;
	char temp;
	int k;
	for (k = 0; k < 5; k++) {
		temp = key[i * 5 + k];
		key[i * 5 + k] = key[j * 5 + k];
		key[j * 5 + k] = temp;
	}
}

void swap2cols(char *key) {
	int i = rand() % 5;
	int j = rand() % 5;
	char temp;
	int k;
	for (k = 0; k < 5; k++) {
		temp = key[k * 5 + i];
		key[k * 5 + i] = key[k * 5 + j];
		key[k * 5 + j] = temp;
	}
}

void modifyKey(char *newKey, char *oldKey) {//функция модификации ключа
	int k, j, i = rand() % 50;
	switch (i) {
	case 0: strcpy(newKey, oldKey); swap2rows(newKey); break;
	case 1: strcpy(newKey, oldKey); swap2cols(newKey); break;
	case 2: for (k = 0; k < 25; k++) newKey[k] = oldKey[24 - k]; newKey[25] = '\0'; break; // разворачиваем всю матрицу
	case 3: for (k = 0; k < 5; k++) for (j = 0; j < 5; j++) newKey[k * 5 + j] = oldKey[(4 - k) * 5 + j]; // меняем все ряды сверху-вних
		newKey[25] = '\0';
		break;
	case 4: for (k = 0; k < 5; k++) for (j = 0; j < 5; j++) newKey[j * 5 + k] = oldKey[(4 - j) * 5 + k]; // меняем все колонки слева-направо
		newKey[25] = '\0';
		break;
	default:strcpy(newKey, oldKey);
		exchange2letters(newKey);
	}
}

float playfairCrack(char *text, int len, char* bestKey) {
	int count; //прогоны внутри цикла - чем больше цифра тем больше точность расчета результата
	float T; //общее количество прогонов
	char *deciphered = (char*)malloc(sizeof(char) * (len + 1)); //строка с расшифрованным текстом
	char testKey[26];
	char maxKey[26];
	double prob, dF, maxscore, score;
	double bestscore;
	strcpy(maxKey, bestKey);
	playfairDecipher(maxKey, text, deciphered, len); //расшифровываем текст с помощью функции расшифровки
	maxscore = scoreTextQgram(deciphered, len); //высчитываем результат анализа ключа
	bestscore = maxscore; //приравниваем лучший ключ к максимальному на данный момент
	for (T = TEMP; T >= 0; T -= STEP) {
		for (count = 0; count < COUNT; count++) {
			modifyKey(testKey, maxKey);    //случайно меняем ключ, подробнее в функции
			playfairDecipher(testKey, text, deciphered, len); //расшифровываем с помощью текущего модифицированного ключа
			score = scoreTextQgram(deciphered, len); //анализируем текст по четырехбуквенным сочетаниям
			dF = score - maxscore;
			if (dF >= 0) {
				//если в результате модифицированный ключ лучше оригинального, то производим замену максимального результата
				maxscore = score;
				strcpy(maxKey, testKey);
			}
			else if (T > 0) {
				//также, пока не последний прогон мы смотрим качественно ключ, чтобы у нас не произошел сбой в его вычислении
				prob = exp(dF / T);
				if (prob > 1.0*rand() / RAND_MAX) {
					maxscore = score;
					strcpy(maxKey, testKey);
				}
			}
			// отслеживаем лучший ключ в каждом прогоне
			if (maxscore > bestscore) {
				bestscore = maxscore;
				strcpy(bestKey, maxKey);
			}
		}
	}
	free(deciphered);
	printf("OldKey: %s\nNewKey:%s\n\n", bestKey,maxKey);
	return bestscore;
}

char *playfairDecipher(char *key, char *text, char *result, int len) { //расшифровка текста
	int i;
	char a, b; /* the digram we are looking at */
	int a_ind, b_ind;
	int a_row, b_row;
	int a_col, b_col;

	for (i = 0; i < len; i += 2) {
		a = text[i];
		b = text[i + 1];
		/*if (index(key,a) == NULL || index(key,b) == NULL) break;*/
		a_ind = (int)(strchr(key, a) - key);
		b_ind = (int)(strchr(key, b) - key);
		a_row = a_ind / 5;
		b_row = b_ind / 5;
		a_col = a_ind % 5;
		b_col = b_ind % 5;
		if (a_row == b_row) {
			if (a_col == 0) {
				result[i] = key[a_ind + 4];
				result[i + 1] = key[b_ind - 1];
			}
			else if (b_col == 0) {
				result[i] = key[a_ind - 1];
				result[i + 1] = key[b_ind + 4];
			}
			else {
				result[i] = key[a_ind - 1];
				result[i + 1] = key[b_ind - 1];
			}
		}
		else if (a_col == b_col) {
			if (a_row == 0) {
				result[i] = key[a_ind + 20];
				result[i + 1] = key[b_ind - 5];
			}
			else if (b_row == 0) {
				result[i] = key[a_ind - 5];
				result[i + 1] = key[b_ind + 20];
			}
			else {
				result[i] = key[a_ind - 5];
				result[i + 1] = key[b_ind - 5];
			}
		}
		else {
			result[i] = key[5 * a_row + b_col];
			result[i + 1] = key[5 * b_row + a_col];
		}
	}
	result[i] = '\0';
	return result;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFSIZE 64
// global буффер для чтения чисел из файлов
char buffer[BUFSIZE] = {0};

char* read_number(FILE* fp, char* buffer);

int main(void) {
    FILE* f1 = fopen("./f1", "r");
    FILE* f2;
    FILE* f3;
    char ch = '\0';
    size_t block_len = 1;
    size_t number_count = 0;
    while (!feof(f1) && read_number(f1, buffer)[0] != '\0') {
        number_count += 1;
    }
    fclose(f1);
    while (number_count >= block_len) {
        f1 = fopen("./f1", "r");
        f2 = fopen("./f2", "w");
        f3 = fopen("./f3", "w");
        int num = 0;
        size_t block_len_counter = 0;
        memset(buffer, 0, BUFSIZE);
        while (!feof(f1) && read_number(f1, buffer)[0] != '\0') {
            num = atoi(buffer);
            memset(buffer, 0, BUFSIZE);
            FILE* outfp = NULL;
            if ((block_len_counter++ / block_len) % 2 == 0)
                outfp = f2;
            else
                outfp = f3;
            fprintf(outfp, "%d ", num);
        }
        fclose(f1);
        fclose(f2);
        fclose(f3);
        f1 = fopen("./f1", "w");
        f2 = fopen("./f2", "r");
        f3 = fopen("./f3", "r");
        // -1 будет служить меткой, что следует прочитать следующее число из соответствующего файла
        int num_f2 = -1;
        int num_f3 = -1;
        size_t block_len_counter_f2 = 0;
        size_t block_len_counter_f3 = 0;
        memset(buffer, 0, BUFSIZE);
        //&& (num_f3 != 67 || num_f2 != -1)
        while ((!feof(f2) || !feof(f3)) ) {
            if (num_f2 == -1 && num_f3 == -1 && block_len_counter_f2 == block_len && block_len_counter_f3 == block_len) {
                block_len_counter_f2 = 0;
                block_len_counter_f3 = 0;
            }
            if (num_f2 == -1 && block_len_counter_f2 < block_len) {
                if (read_number(f2, buffer)[0] != '\0')
                    num_f2 = atoi(buffer);
                block_len_counter_f2++;
                memset(buffer, 0, BUFSIZE);
            }
            if (num_f3 == -1 && block_len_counter_f3 < block_len) {
                if (read_number(f3, buffer)[0] != '\0')
                    num_f3 = atoi(buffer);
                block_len_counter_f3++;
                memset(buffer, 0, BUFSIZE);
            }
            if ((num_f2 > num_f3 || num_f2 == -1) && num_f3 != -1) {
                fprintf(f1, "%d ", num_f3);
                num_f3 = -1;
            } else if (num_f2 != -1) {
                fprintf(f1, "%d ", num_f2);
                num_f2 = -1;
            }
        }
        fclose(f1);
        fclose(f2);
        fclose(f3);
        block_len *= 2;
    }
    return EXIT_SUCCESS;
}

char* read_number(FILE* fp, char *buffer) {
    char ch = '\0';
    size_t i = 0;
    while ((ch = getc(fp)) && !feof(fp) && ch != ' ' && ch != '\n') {
        buffer[i++] = ch;
    }
    return buffer;
}

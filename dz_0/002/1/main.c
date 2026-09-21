#include <stdio.h>


void clean_buff();
int input_check(int*, int*);

int main() {
    int a, b;
    printf("Введите HEX числа [num1 num2]: ");
    int iseof = input_check(&a, &b);
    int start = a/16, end = b/16;
    if (iseof == EOF) return 0;
    printf("\"..\" используется для непечатаемых символов\n");
    printf("\n    ");
    for (int i = 0; i < 16; i++) {
        printf("%-3x", i);
    }
    printf("\n");
    for (int i = start; i <= end; i++) {
        printf("%xx  ", i);
        for (int j = 0; j < 16; j++) {
            int chr = i * 16 + j;
            if (chr < a || chr > b) {
                printf("   ");
                continue;
            }
            switch(chr) {
                case 0:
                    printf("%-3s", "\\0");
                    break;
                case 7:
                    printf("%-3s", "\\a");
                    break;
                case 8:
                    printf("%-3s", "\\b");
                    break;
                case 9:
                    printf("%-3s", "\\t");
                    break;
                case 10:
                    printf("%-3s", "\\n");
                    break;
                case 11:
                    printf("%-3s", "\\v");
                    break;
                case 12:
                    printf("%-3s", "\\f");
                    break;
                case 13:
                    printf("%-3s", "\\r");
                    break;
                case 27:
                    printf("%-3s", "\\e");
                    break;
                default:
                    if (chr > 31 && chr < 127) {
                        printf("%-3c", chr);
                    } else {
                        printf("%-3s", "..");
                    }
            }
        }
        printf("\n");
    }

    return 0;
}

void clean_buff() {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
}

int input_check(int *a, int *b) {
    while (1) {
        char c;
        int f = scanf("%x %x%c", a, b, &c);
        if (f == EOF) {
            printf("EOF! Выход...\n");
            return EOF;
        } else if (f != 3) {
            printf("Ошибка ввода! Попробуйте ещё раз: ");
            clean_buff();
        } else if (c != '\n') {
            printf("Лишние символы! Попробуйте ещё раз: ");
            clean_buff();
        } else if (*a < 0 || *b < 0 || *a > 127 || *b > 127) {
            printf("Нужны числа от 0 до 7F! Попробуйте ещё разn: ");
        } else if (*a > *b) {
            printf("Первое число меньше второго! Попробуйте ещё раз: ");
        } else break;
    }

    return 0;
}

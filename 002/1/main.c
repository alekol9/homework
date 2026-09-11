#include <stdio.h>


void clean_buff();
int input_check(int*, int*);

int main() {
    int a, b;
    printf("Введите HEX числа [num1 num2]: ");
    int iseof = input_check(&a, &b);
    if (iseof == EOF) return 0;
    printf("\"..\" используется для непечатаемых символов\n");
    printf("HEX CHAR\n");
    for (int i = a; i <= b; i++) {
        switch(i) {
            case 0:
                printf("%-3x \\0\n", i);
                break;
            case 7:
                printf("%-3x \\a\n", i);
                break;
            case 8:
                printf("%-3x \\b\n", i);
                break;
            case 9:
                printf("%-3x \\t\n", i);
                break;
            case 10:
                printf("%-3x \\n\n", i);
                break;
            case 11:
                printf("%-3x \\v\n", i);
                break;
            case 12:
                printf("%-3x \\f\n", i);
                break;
            case 13:
                printf("%-3x \\r\n", i);
                break;
            case 27:
                printf("%-3x \\e\n", i);
                break;
            default:
                if (i > 31 && i < 127) {
                    printf("%-3x %c\n", i, i);
                } else {
                    printf("%-3x ..\n", i);
                }
        }
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

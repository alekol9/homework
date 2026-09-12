#include <stdio.h>
#include "prog.h"


int main() {
    int correct = 123, attempts = 3, code, flag = 0;

    for (int i = 1; i <= attempts; i++) {
        printf("Введите код: ");
        scanf("%d", &code);
        if (check(code, correct) == 1) {
            flag = 1;
            break;
        } else {
            if ((attempts- i) != 0) printf("Неверный код. Попробуйте снова (попыток осталось %d). ", attempts-i);
            fprintf(stderr, "Попытка %d: Введён неверный код\n", i);
        }
    }

    if (flag == 1) {
        printf("GRANTED\n");
        fprintf(stderr, "Успешный вход\n\n");
        return 0;
    } else {
        printf("DENIED\n");
        fprintf(stderr, "Вход не совершён\n\n");
        return 1;
    }
}

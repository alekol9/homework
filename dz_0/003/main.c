#include <stdio.h>
#include "prog.h"


int main() {
    const char *correct = "123";
    char code[5];
    int attempts = 3, flag = 0;

    for (int i = 1; i <= attempts; i++) {
        printf("Введите код: ");
        scanf("%4s", code);
        if (check(code, correct) == 1) {
            flag = 1;
            break;
        } else {
            if ((attempts- i) != 0) printf("Неверный код. Попробуйте снова (попыток осталось %d). ", attempts-i);
            LWRN("Введён неверный код\n", i);
            clean_buff();
        }
    }

    if (flag == 1) {
        printf("GRANTED\n");
        LINF("Успешный вход\n\n");
        return 0;
    } else {
        printf("DENIED\n");
        LERR("Вход не совершён\n\n");
        return 1;
    }
}

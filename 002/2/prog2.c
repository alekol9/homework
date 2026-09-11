#include <stdio.h>
#include <time.h>

int isleap(int);
int daymonth(int, int);

int main() {
    int d, m, y;
    if (scanf("%d.%d.%d", &d, &m, &y) != 3) {
        printf("Неверный формат\n");
        return 1;
    }

    if (d < 1 || d > 31 || m < 1 || m > 31) {
        printf("Некорректная дата\n");
        return 1;
    }
    d++;
    if (d > daymonth(m, y)) {
        d = 1;
        m++;
    }
    if (m > 12) {
        m = 1;
        y++;
    }
    printf("%02d.%02d.%02d\n", d, m, y);

    return 0;
}

int daymonth(int m, int y) {
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (m == 2 && isleap(y)) return 29;
    return days[m - 1];
}

int isleap(int y) {
    if (y % 4 != 0) return 0;
    if (y % 100 != 0) return 1;
    if (y % 400 == 0) return 1;
    return 0;
}

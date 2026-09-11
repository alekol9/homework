#include <stdio.h>
#include <time.h>


int main() {
    time_t curr_time;
    time(&curr_time);
    struct tm *curr_tm = localtime(&curr_time);
    printf("%02d.%02d.%04d\n", curr_tm->tm_mday, curr_tm->tm_mon+1, curr_tm->tm_year+1900);

    return 0;
}

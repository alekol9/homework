#include "prog.h"
#include <stdio.h>
#include <string.h>


int check(const char *code, const char *correct) {
    return strcmp(code, correct) == 0;
}

void clean_buff() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
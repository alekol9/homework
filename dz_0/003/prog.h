#pragma once

#include <stdio.h>

#define LINF(fmt, ...) fprintf(stderr, "[INF] | [%s:%s:%d] %s", __FILE__, __FUNCTION__, __LINE__, fmt)
#define LWRN(fmt, ...) fprintf(stderr, "[WRN] | [%s:%s:%d] %s", __FILE__, __FUNCTION__, __LINE__, fmt)
#define LERR(fmt, ...) fprintf(stderr, "[ERR] | [%s:%s:%d] %s", __FILE__, __FUNCTION__, __LINE__, fmt)

int check(const char*, const char*);
void clean_buff(void);
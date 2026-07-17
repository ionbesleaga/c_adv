#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include "variadic_func.h"

#define ANSI_RESET_ALL
#define ANSI_COLOR_WHITE "\x1b[37m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_RED "\x1b[31m"

typedef struct
{
    const char *label;
    const char *color;
} log_style;

static const log_style STYLES[3] = {
    [LOG_INFO] = {"INFO", ANSI_COLOR_WHITE},
    [LOG_WARN] = {"WARN", ANSI_COLOR_YELLOW},
    [LOG_ERR] = {"ERR", ANSI_COLOR_RED}};

static void print_time(log_level level)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    log_style style = STYLES[level];

    printf("%s[%d-%02d-%02d %02d:%02d:%02d]: %s\t=> ", style.color, tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, style.label);
}

void log_msg(log_level level, const char *msg, ...)
{
    va_list vl;
    va_start(vl, msg);

    print_time(level);
    vprintf(msg, vl);
    printf(ANSI_RESET_ALL "\n");
    va_end(vl);

    ANSI_RESET_ALL;
}

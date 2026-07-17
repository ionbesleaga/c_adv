#include <stdio.h>

int str_len(const char *val)
{
    int ctn = 0;
    while (val[ctn++] != '\0')
        ;

    return ctn - 1;
}

// 1st param - delegate function
static void myprint(int (*func)(const char *), char *text)
{
    printf("%d", func(text));
}

void print_strlen(char *text)
{
    myprint(str_len, text);
}

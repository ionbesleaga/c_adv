#include <stdio.h>
#include <stdlib.h>

static char *read_line(FILE *f)
{
    size_t cap = 10, len = 0;
    char *buf = malloc(cap);
    int ch;

    if (buf == NULL)
        return NULL;

    // read until new line or end of file
    while ((ch = fgetc(f)) != '\n' && ch != EOF)
    {
        // resize if needed
        if (len + 1 >= cap)
        {
            char *tmp = realloc(buf, cap *= 2);
            if (tmp == NULL)
            {
                free(buf);
                return NULL;
            }
            buf = tmp;
        }

        buf[len++] = (char)ch;
    }

    // shrink buffer to only needed chars
    if (len != cap)
    {
        char *tmp = realloc(buf, len + 1);
        if (tmp == NULL)
        {
            free(buf);
            return NULL;
        }
        buf = tmp;
    }

    if (ch == EOF && len == 0)
    {
        free(buf);
        return NULL;
    }

    buf[len] = '\0';
    return buf;
}

int read_file()
{
    FILE *f = fopen("tt.txt", "r");
    if (f == NULL)
    {
        perror("Failed to open file");
        return 0;
    }

    char *line;
    while ((line = read_line(f)) != NULL)
    {
        printf("%s\n", line);
        free(line);
    }

    fclose(f);

    return 1;
}

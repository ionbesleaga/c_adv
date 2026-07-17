#include <stdio.h>
#include <stdlib.h>

void fill_arr(int h, int w, int arr[h][w])
{
    int ctn = 1;
    for (size_t i = 0; i < h; i++)
    {
        for (size_t j = 0; j < w; j++)
        {
            arr[i][j] = ctn++;
        }
    }
}

void print_arr(int h, int w, int arr[h][w])
{
    for (size_t i = 0; i < h; i++)
    {
        for (size_t j = 0; j < w; j++)
        {
            printf("%d\t", arr[i][j]);
        }
        printf("\n\n");
    }
}

int get_input_number()
{
    char inpt[10];
    int num = (int)strtol(fgets(inpt, sizeof inpt, stdin), NULL, 10);

    return num;
}

int create_print_arr()
{
    printf("Set height: ");
    int h = get_input_number();
    printf("Set width: ");
    int w = get_input_number();

    int arr[h][w];
    fill_arr(h, w, arr);
    print_arr(h, w, arr);

    return 0;
}

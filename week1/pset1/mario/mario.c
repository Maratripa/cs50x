#include <cs50.h>
#include <stdio.h>

void build_pyramid(int h, int j);

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    build_pyramid(height, height);
}

void build_pyramid(int h, int j)
{
    if (h == 1)
    {
        for (int i = 1; i < j; i++)
        {
            printf(" ");
        }
        printf("#  #\n");
    }
    else
    {
        build_pyramid(h - 1, j);
        for (int i = 0; i < (j - h); i++)
        {
            printf(" ");
        }
        for (int i = 0; i < h; i++)
        {
            printf("#");
        }
        printf("  ");
        for (int i = 0; i < h; i++)
        {
            printf("#");
        }
        printf("\n");
    }
}
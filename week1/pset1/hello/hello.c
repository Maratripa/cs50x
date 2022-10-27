#include <stdio.h>
#include <cs50.h>

int main(void)
{
    char *s = get_string("What is your name? \n");

    printf("hello, %s\n", s);
}
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int pop;
    do
    {
        pop = get_int("Starting population: ");
    }
    while (pop < 9);

    int end;
    do
    {
        end = get_int("Ending population: ");
    }
    while (end < pop);

    int years = 0;
    for (int i = 0; pop < end; i++)
    {
        int pass = pop / 4;
        int born = pop / 3;
        pop = pop + born - pass;
        years++;
    }
    printf("Years: %i\n", years);
}
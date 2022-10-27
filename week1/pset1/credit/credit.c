#include <stdio.h>
#include <cs50.h>

bool validation(long num);

int main(void)
{
    long card = get_long("Number: ");

    if (validation(card))
    {
        int lng;
        for (lng = 1; card > 100; lng++)
        {
            card = (card - (card % 10)) / 10;
        }

        if ((card == 51 || card == 52 || card == 53 || card == 54 || card == 55) && lng > 14)
        {
            printf("MASTERCARD\n");
        }
        else if ((card == 34 || card == 37) && lng > 13)
        {
            printf("AMEX\n");
        }
        else if ((card - (card % 10)) / 10 == 4 && lng > 11)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

bool validation(long num)
{
    int sum1 = 0;
    int sum2 = 0;

    int j;
    long i;

    for (i = num, j = 1; i > 0; i = (i - (i % 10)) / 10, j++)
    {
        if (j % 2 == 0)
        {
            int tmp = ((i % 10) * 2);
            if (tmp >= 10)
            {
                sum1 = sum1 + (tmp % 10) + (((tmp - (tmp % 10)) / 10) % 10);
            }
            else
            {
                sum1 = sum1 + tmp;
            }
        }
        else
        {
            sum2 = sum2 + (i % 10);
        }
    }

    return (sum1 + sum2) % 10 == 0;
}
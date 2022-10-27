#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

int main(void)
{
    string sentence = get_string("Text: ");

    int letters = 0;

    int words = 1;

    int sentences = 0;

    for (int i = 0; sentence[i] != '\0'; i++)
    {
        if (isalpha(sentence[i]))
        {
            letters++;
        }

        if (sentence[i] == ' ')
        {
            words++;
        }

        if (sentence[i] == '.' || sentence[i] == '!' || sentence[i] == '?')
        {
            sentences++;
        }
    }

    double grade = (0.0588 * (100 * (float)letters / words)) - (0.296 * (100 * (float)sentences / words)) - 15.8;

    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (1 <= grade && grade < 16)
    {
        printf("Grade %i\n", (int)round(grade));
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
}
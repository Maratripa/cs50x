#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if (argc == 1)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (argc > 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else
    {
        for (int i = 0; i < 26; i++)
        {
            for (int j = 0; j < 26; j++)
            {
                if (tolower(argv[1][i]) == tolower(argv[1][j]) && i != j)
                {
                    printf("Key must not contain duplicate characters.\n");
                    return 1;
                }
            }

            if (!isalpha(argv[1][i]))
            {
                printf("Key must contain only characters.\n");
                return 1;
            }
        }
    }

    string key = argv[1];
    for (int j = 0; j < 27; j++)
    {
        if (isupper(key[j]))
        {
            key[j] = tolower(key[j]);
        }
    }

    string plaintext = get_string("plaintext: ");

    string ciphertext = plaintext;

    for (int i = 0; plaintext[i] != '\0'; i++)
    {

        if (isalpha(plaintext[i]))
        {
            bool upper = isupper(plaintext[i]);
            if (upper)
            {
                ciphertext[i] = toupper(key[(int)plaintext[i] - 65]);
            }
            else
            {
                ciphertext[i] = key[(int)plaintext[i] - 97];
            }
        }
    }

    printf("ciphertext: %s\n", ciphertext);
    return 0;
}
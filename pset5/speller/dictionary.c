// Implements a dictionary's functionality

#include <stdbool.h>
#include <strings.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26 * 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *w)
{
    int index = hash(w);

    for (node *n = table[index]; n != NULL; n = n->next)
    {
        if (strcasecmp(n -> word, w) == 0)
        {
            return true;
        }
    }
    // printf("%i\n", hash("foo"));
    return false;
}

// Hashes word to a number
unsigned int hash(const char *w)
{
    int num = 0;

    if (strlen(w) > 1)
    {
        if (isalpha(w[0]) != 0)
        {
            if (isupper(w[0]) != 0)
            {
                num = (w[0] - 'A') * 26;
            }
            else
            {
                num = (w[0] - 'a') * 26;
            }
        }
        if (isalpha(w[1]) != 0)
        {
            if (isupper(w[1]) != 0)
            {
                num = num + (w[1] - 'A');
            }
            else
            {
                num = num + (w[1] - 'a');
            }
        }
    }
    else
    {
        if (isupper(w[0]) != 0)
        {
            num = (w[0] - 'A') * 26;
        }
        else
        {
            num = (w[0] - 'a') * 26;
        }
    }
    return num;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        fclose(file);
        return false;
    }

    int index;
    node *n;
    char w[LENGTH + 1];
    while (fscanf(file, "%s", w) != EOF)
    {
        // Create node and get hash index
        n = malloc(sizeof(node));
        if (n == NULL)
        {
            free(n);
            return false;
        }
        index = hash(w);

        // Populate node
        strcpy(n->word, w);
        n->next = table[index];

        // Add new node to table
        table[index] = n;
    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    unsigned int count = 0;

    for (int i = 0; i < N; i++)
    {
        for (node *n = table[i]; n != NULL; n = n->next)
        {
            count++;
        }
    }

    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int j = 0; j < N; j++)
    {
        for (node *m = table[j]; table[j] != NULL; table[j] = m)
        {
            m = m->next;
            free(table[j]);
        }
    }
    return true;
}
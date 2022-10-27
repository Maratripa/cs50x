#include <stdio.h>
#include <cs50.h>

#define MAX 5

bool locked[MAX][MAX];

typedef struct
{
    int winner;
    int loser;
}
pair;

pair pairs[10];

int pair_count = 10;
int candidate_count = 5;

void lock_pairs(void);
bool check_cycle(int row, int inicial);
void print_locked(void);

int main(void)
{
    pairs[0].winner = 0;
    pairs[0].loser = 2;
    pairs[1].winner = 0;
    pairs[1].loser = 3;
    pairs[2].winner = 1;
    pairs[2].loser = 0;
    pairs[3].winner = 4;
    pairs[3].loser = 0;
    pairs[4].winner = 1;
    pairs[4].loser = 4;
    pairs[5].winner = 1;
    pairs[5].loser = 3;
    pairs[6].winner = 1;
    pairs[6].loser = 2;
    pairs[7].winner = 3;
    pairs[7].loser = 2;
    pairs[8].winner = 4;
    pairs[8].loser = 3;
    pairs[9].winner = 2;
    pairs[9].loser = 4;
    lock_pairs();
}

bool check_cycle(int row, int inicial)
{
    for (int j = 0; j < candidate_count; j++)
    {
        if (locked[row][j])
        {
            if (j == inicial)
            {
                printf("false\n");
                return false;
            }
            else
            {
                return check_cycle(j, inicial);
            }
        }
    }
    printf("true\n");
    return true;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        printf("pair %i winner: %i, loser: %i.\n", i, pairs[i].winner, pairs[i].loser);
        locked[pairs[i].winner][pairs[i].loser] = true;
        if (!check_cycle(pairs[i].loser, pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser] = false;
        }

        print_locked();
    }
    return;
}

void print_locked(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[i][j])
            {
                printf("1 ");
            }
            else
            {
                printf("0 ");
            }
        }
        printf("\n");
    }
}
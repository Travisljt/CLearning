#include <assert.h>
#include <stdio.h>

#define RANGE 10000000

int getHailstoneLength(long init);
int dp[NUMBER] = {1};

int main()
{
    int max = 0;
    int max_init;
    for (int i = 1; i < NUMBER; i++)
    {
        int len = getHailstoneLength(i);
        if (max < len)
        {
            max = len;
            max_init = i;
        }
    }
    printf("Sequence Len: %d\nInitial Number: %d.\n", max, max_init);
}

int getHailstoneLength(long init)
{
    // check whether the length info already store in dp array.
    if (init < NUMBER + 1 && dp[init - 1] != 0)
        return dp[init - 1];

    int curr_len = 0;
    if (init != 1)
    {
        if (init % 2 == 0)
        {
            curr_len = 1 + getHailstoneLength(init / 2);
        }
        else
        {
            curr_len = 1 + getHailstoneLength(init * 3 + 1);
        }
    }

    // store every length info into dp array.
    if (init < NUMBER)
        dp[init - 1] = curr_len;

    return curr_len;
}

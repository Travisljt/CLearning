#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>

bool struses(const char *s1, const char *s2);

int main(void)
{

    /* What words can you make using only the
       Top line of a traditional qwerty keyboard ?*/
    assert(struses("perpetuity", "qwertyuiop"));
    assert(struses("PERPETUITY", "QWERTYUIOP"));
    assert(struses("typewriter", "qwertyuiop"));
    assert(struses("", "qwertyuiop"));

    assert(!struses("printers", "qwertyuiop"));
    assert(!struses("typist", "qwertyuiop"));
    assert(!struses("typist", "qwertyuiop"));

    assert(struses("alfalfas", "asdfghjkl"));
    assert(struses("galahads", "asdfghjkl"));

    assert(!struses("goldilocks", "asdfghjkl"));
    assert(!struses("darkness", "asdfghjkl"));

    assert(!struses("sdm,nc,ncd|SDFKSKO$$W", ""));

    return 0;
}

bool struses(const char *s1, const char *s2)
{
    /*if((int)strlen(s1)==0||((int)strlen(s1)==(int)strlen(s2)))
    {
        return true;
    }*/
    int cnt = 0;

    for (int i = 0; i < (int)strlen(s1); i++)
    {
        for (int j = 0; j < (int)strlen(s2); j++)
        {
            if ((s1[i] - s2[j]) == 0)
            {
                cnt++;
            }
        }
    }
    if (cnt == (int)strlen(s1))
    {

        return true;
    }

    return false;
}
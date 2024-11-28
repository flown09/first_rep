#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void asdf(int count_flags[8])
{
    count_flags[0]++;
}
int main(int argc, char * argv[])
{
    int count_flags[8] = {0};
    count_flags[1]++;
    asdf(count_flags);
    for (int i = 0; i < 8; i++)
    {
        printf("%d\n", count_flags[i]);
    }
}


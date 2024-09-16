#include <stdio.h>

void menu_1(char filename[256]);

int main(void)
{
    int mode;
    char garbage[256];
    char filename[256];
    while (1)
    {
        if (scanf("%d", &mode) != 1)
        {
            printf("n/a\n");
            scanf("%255s", garbage);
        }
        if (mode == -1)
            break;
        else if (mode == 1)
        {
            menu_1(filename);
        }
    }

    return 0;
}

void menu_1(char filename[256])
{
    fscanf(stdin, "%255s", filename);
    FILE* fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("n/a\n");
    }
    else
    {
        fscanf(fp, "%255s", filename);
        printf("%s", filename);
        putchar('\n');
    }
}
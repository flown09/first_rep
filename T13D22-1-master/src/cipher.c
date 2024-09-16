#include <stdio.h>

void menu_1(char filename[256]);
void menu_2(char filename[256], char str[256]);

int main(void)
{
    int mode;
    char garbage[256];
    char filename[256];
    char str[256];
    while (1)
    {
        if (scanf("%d", &mode) != 1)
        {
            printf("n/a1\n");
            scanf("%255s", garbage);
        }
        if (mode == -1)
            break;
        else if (mode == 1)
        {
            menu_1(filename);
        }
        else if (mode == 2 && filename != NULL)
        {
            menu_2(filename, str);
        }
    }

    return 0;
}

void menu_1(char filename[256])
{
    char str1[256];
    fscanf(stdin, "%255s", filename);
    FILE* fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("n/a2\n");
    }
    else
    {
        fscanf(fp, "%255s", str1);
        printf("%s", str1);
        putchar('\n');
    }
}

void menu_2(char filename[256], char str[256])
{
    FILE* fr = fopen(filename, "r");
    if (fr == NULL)
    {
        printf("n/a3\n");
        fclose(fr);
    }
    else
    {
        puts(filename);
        fscanf(stdin, "%255s", str);
        FILE* fp = fopen(filename, "a");
        if (fp == NULL)
        {
            printf("n/a4\n");
        }
        else
        {
            fputs(str, fp);
        }
    }
}
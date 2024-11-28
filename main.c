#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "flag-s.h"

void* flags(int count_flags[8], char* data, int *length);
void isFlag(int count_flags[8], char flag[256]);
char* readFile(char filename[256], char* data, int *length, int *capacity);
void printFile(char* data, int length);
void* append(char* data, int *length, int *capacity, char value);
int isFile(char filename[256]);

int main(int argc, char * argv[])
{
    if (strcmp(argv[1], "cat") == 0)
    {
        int count_flags[8] = {0};
        for (int i = 2; i < argc; i++)
        {
            if (strncmp(argv[i], "-", 1) == 0)
            {
                isFlag(count_flags, argv[i]);
            }
            else if (isFile(argv[i]) == 0)
            {
                char *data;
                int capacity = 10;
                int length = 0;
                data = readFile(argv[i], data, &length, &capacity);
                data = flags(count_flags, data, &length);
                printFile(data, length);
            }
            else
            {
               printf("cat: %s: No such file or directory", argv[i]);
            }
        }
        /*for (int i = 0; i < 8; i++)
            printf("%d ", count_flags[i]);*/
    }
    
    return 0;
}

void* flags(int count_flags[8], char* data, int *length)
{
    if (count_flags[4] > 0)
    {
        data = flag_s(data, length);
    }
    return data;
}

void isFlag(int count_flags[8], char flag[256])
{
    if (strcmp(flag, "-b") == 0 || strcmp(flag, "--number-nonblank") == 0)
        count_flags[0] += 1;
    else if (strcmp(flag, "-e") == 0)
        count_flags[1] += 1;
    else if (strcmp(flag, "-E") == 0)
        count_flags[2] += 1;
    else if (strcmp(flag, "-n") == 0 || strcmp(flag, "--number") == 0)
        count_flags[3] += 1;
    else if (strcmp(flag, "-s") == 0 || strcmp(flag, "--squeeze-blank") == 0)
        count_flags[4] += 1;
    else if (strcmp(flag, "-t") == 0)
        count_flags[5] += 1;
    else if (strcmp(flag, "-T") == 0)
        count_flags[6] += 1;
    else if (strcmp(flag, "-v") == 0)
        count_flags[7] += 1;
}

char* readFile(char filename[256], char* data, int *length, int *capacity)
{
    FILE *fp = fopen(filename, "r");
    char ch;
    data = malloc(sizeof(char) * *capacity);
    while ((ch = fgetc(fp)) != EOF)
        data = append(data, length, capacity, ch);
    return data;
    fclose(fp);
}

void* append(char* data, int *length, int *capacity, char value)
{
    if (*length >= *capacity)
    {
        (*capacity) *= 2;
        char* ar = realloc(data, sizeof(char) * *capacity);
        if (ar == NULL)
            return data;
        data = ar;
    }
    data[*length] = value;
    (*length)++;

    return data;
}

int isFile(char filename[256])
{
    FILE *fp;
    if ((fp = fopen(filename, "r")) == NULL)
    {
        return 1;
    }
    fclose(fp);
    return 0;
}

void printFile(char* data, int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("%c", data[i]);
    }
}
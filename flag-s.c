#include "flag-s.h"

void* flag_s(char* data, int *length)
{
    for (int i = 0; i < *length - 2; )
    {
        if (data[i] == '\n' && data[i + 1] == '\n' && data[i + 2] == '\n')
        {
            for (int j = i + 2; j < *length - 1; j++)
            {
                data[j] = data[j + 1];
            }
            (*length)--;
        }
        else
        {
            i++;
        }
    }
    return data;
} 

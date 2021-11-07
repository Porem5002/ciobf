#include "include/string_op.h"

bool string_starts_with(char* str, char* starts_with)
{
    int i = 0;

    while(starts_with[i] != '\0')
    {
        if(str[i] != starts_with[i]) return false;

        i++;
    }

    return true;
}

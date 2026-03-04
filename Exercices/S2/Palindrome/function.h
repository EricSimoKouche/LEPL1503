#include <string.h>

#ifndef _FUNCTION_H_
#define _FUNCTION_H_

int pal(char *str) {
    if (!str) return -1;

    int len = strlen(str);
    if (len == 0) return 1;

    int low = 0, high = len - 1;

    while (low <= high) 
    {
        if (str[low] == ' ')
        {
            low++;
            continue;
        }
        if (str[high] == ' ')
        {
            high--;
            continue;
        }
        
        if (str[low] != str[high]) return 0;
        low++;
        high--;
    }

    return 1;
}
#endif // _FUNCTION_H_
#include <stdio.h>
#include <stdlib.h>

char* my_strcat(char* dest, const char* src) 
{
    size_t dest_len = 0;
    while(dest[dest_len]) dest_len++;

    size_t i;
    for (i = 0; src[i]; i++) {
        dest[dest_len + i] = src[i];
    }
    dest[dest_len+i] = '\0';
    return dest;
}

int main(int argc, char** argv) 
{
    char* str = my_strcat(argv[1], argv[2]);
    printf("the concatenated string is %s", str);
    return 0;
}
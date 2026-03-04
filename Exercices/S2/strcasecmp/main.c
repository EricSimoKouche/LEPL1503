#include <stdlib.h>
#include <stdio.h>

int strcasecmp (const char* s1, const char* s2) 
{
    while (*s1 && *s2) {
        
        char c1 = (unsigned char)*s1;
        char c2 = (unsigned char)*s2;

        if (c1 >= 'A' && c1 <= 'Z') c1 += 32;
        if (c2 >= 'A' && c2 <= 'Z') c2 += 32;

        if (c1 < c2) return -1;
        if (c1 > c2) return 1;

        s1++;
        s2++;
    }

    if (*s1) return 1;
    if (*s2) return -1;

    return 0;
}

int main(int argc, char** argv) 
{
    printf("%d", strcasecmp(argv[1], argv[2]));

}
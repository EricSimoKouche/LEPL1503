#include <stdlib.h>
#include <stdio.h>


void* calloc2(size_t nmemb, size_t size) 
{
    unsigned long SIZE_MAX = 4294967295;
    if (nmemb == 0 || size == 0) {
        return malloc(1);
    }
    if (size > SIZE_MAX / nmemb)
    {
        return NULL;
    }
    
    void* ptr = malloc(nmemb * size);
    if (!ptr) return NULL;
    char* current = (char*) ptr;
    size_t i = 0;
    while (i < nmemb * size) 
    {
        *(current + i) = 0;
        i++;
    }
    return ptr;
}


int main(int argc, char** argv) 
{
    char* s = (char*) calloc2(2, 2);
    if (!s) printf("Error");
    int i = 0;
    while (i < 5) 
    {
        printf("sth%c\n", *(s+i));
        i++;
    }
    printf("%lu", sizeof(size_t));
    return 0;
}
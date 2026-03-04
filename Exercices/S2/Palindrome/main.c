#include <stdio.h>
#include <stdlib.h>
#include "function.h"

int main (int argc, char** argv) {
    if (argc == 1) {
        printf("None argument passed");
        exit(EXIT_FAILURE);
    } else {
        printf("%s %s a palindrome", argv[1], pal(argv[1]) == 1 ? "is" : "is not");
    }
    return 0;
}
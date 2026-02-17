#include <stdio.h>
#include <stdlib.h>
#include "./function.h"
#include "./function.c"

int main (int argc, const char *argv[]) {

    if (argc > 1 && argc <= 2) {
        int val = atoi(argv[1]);
        printf("the factorial of %d is %d", val, factorial(val));
    } else {
        printf("You did not passed any parameter or passed too much parameter");
    }
    return 0;
}
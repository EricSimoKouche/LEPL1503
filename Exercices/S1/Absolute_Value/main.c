#include <stdio.h>
#include <stdlib.h>
#include "./function.h"

int main(int argc, const char *argv[]) {

    if (argc > 1 && argc <=2) {
        int val = atoi(*(argv+1));
        printf("%d", absval(val));
    } else {
        printf("Nothig was passed");
    }
    return 0;
}
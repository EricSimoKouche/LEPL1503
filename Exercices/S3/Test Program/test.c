#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int eq (int a, int b) {
    return !(a == b);
}

int ge (int a, int b) {
    return !(a >= b);
}

int gt(int a, int b) {
    return !(a > b);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <a> <op> <b>\n", argv[0]);
        return 1;
    }

    int a = atoi(argv[1]);
    int b = atoi(argv[3]);
    char *op = argv[2];
    
    if (strcmp("-eq", op) == 0) {
        return eq(a, b);
    } else if (strcmp("-ge", op) == 0) {
        return ge(a, b);
    } else if (strcmp("-gt", op) == 0) {
        return gt(a, b);
    } else if (strcmp("-ne", op) == 0) {
        return !eq(a, b);
    } else if (strcmp("-le", op) == 0) {
        return !gt(a, b);
    } else if (strcmp("-lt", op) == 0) {
        return !ge(a, b);
    } else {
        fprintf(stderr, "Unknown operation %s\n", argv[2]);
        return 1; 
    }
}
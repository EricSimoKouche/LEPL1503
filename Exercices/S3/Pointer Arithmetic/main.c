#include <stdio.h>
#include <stdlib.h>

int first (void* ptr) {
    int* a_ptr = (int *) (ptr + 12);
    return *a_ptr;
}

int second(void* ptr) {
    char* b_ptr = (char *) (ptr + 6);
    return *b_ptr;
}

int third(void* ptr) {
    int* c = (int*) (ptr + 45);
    return *c_ptr;
}

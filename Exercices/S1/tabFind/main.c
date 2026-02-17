#include <stdio.h>
#include "./function.h"
#include "./function.c"


int main(){ 

    int elem = 4;
    int tab[] = {1,3,4};
    int len = 3;
    printf("the index of the element %d is %d", elem, tab_find(tab, len, elem));

    return 0;
}
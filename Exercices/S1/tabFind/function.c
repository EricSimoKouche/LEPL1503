#include "./function.h"

int tab_find(int tab[], int len, int elem) {

    for (int i = 0; i < len; i++) {
        if (tab[i] == elem) return i;
    }

    return -1;
}
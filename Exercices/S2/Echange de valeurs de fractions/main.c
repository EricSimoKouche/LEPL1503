#include <stdio.h>
#include <stdlib.h>

struct frac_t {
    int num;
    int denum;
};

void swap(struct frac_t *a, struct frac_t *b)
{
    // we assume that the structures always contains a value.

    int temp = a->num;
    a->num = b->num;
    b->num = temp;

    temp = a->denum;
    a->denum = b->denum;
    b->denum = temp;
}

int main (int argc, char** argv) 
{
    struct frac_t* a = malloc(sizeof(struct frac_t));
    struct frac_t* b = malloc(sizeof(struct frac_t));

    a->num = 2; a->denum = 3;
    b->num = 4; b->denum = 6;
    swap(a, b);
    printf("fraction a : %d/%d\n", a->num, a->denum);
    printf("fraction b : %d/%d", b->num, b->denum);
    return 0;
}

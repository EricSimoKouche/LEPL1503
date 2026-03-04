#include <stdio.h>
#include <stdlib.h>

void swap(int *i, int *j) 
{
	int temp = *i;
	*i = *j;
	*j = temp;
}

int main(int argc, char** argv) 
{
	int i = 2;
	int j = 3;
	swap(&i, &j);
	printf("i = %d and j = %d", i, j);
	return 0;
}

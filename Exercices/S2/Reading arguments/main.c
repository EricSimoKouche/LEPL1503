#include <stdio.h>
#include <stdlib.h>

int main (int argc, char** argv) {
    
    for(int i = 1; i < argc; i += 2) {
        if (i+2 < argc) {
            printf("%s ", *(argv + i));
        } else {
            printf("%s\n", *(argv + i));
        }
    }
    return 0;
}
	

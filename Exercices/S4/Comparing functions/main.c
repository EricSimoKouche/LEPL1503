#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int cmp_func(uint8_t (*f1)(uint8_t), uint8_t(*f2)(uint8_t)) {

	uint8_t val = 0;
	do {
		uint8_t f1_val = f1(val);
		uint8_t f2_val = f2(val);

		if (f1_val != f2_val) 
			return 0;
		val ++;

	} while (val != 0); // The loop breaks when 255 overflows back to 0

	return 1;
}

int main() {
	printf("Comparing functions\n");
	return 0;
}

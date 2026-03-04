#include <stdio.h>
#include <stdlib.h>

#ifndef _FUNCTION_H_
#define _FUNCTION_H_

/* print_digit
    @nunmber : an integer

    result: print to stdout "The magic number is NUMBER.\n"

*/
void print_digit(int number)
{
    printf("The magic number is %d.\n", number);
}

void print_foo() 
{
    printf("foo\n");
}

/*  format_str, example :
    format_str(buf, 42, "Olivier", 'B') will write into buf
    the string "Mister Olivier B. has 42 eggs" (no line feed)
    the given buffer is guaranteed to be big enough
*/
void format_str(char *buffer, unsigned int d, char *name, char initial)
{
    sprintf(buffer, "Mister %s %c. has %d eggs", name, initial, d);
    printf("%s", buffer);
}

#endif // _FUNCTION_H_
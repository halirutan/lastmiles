
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{

    uint32_t a, b, c, d;

    a = 1;
    b = 2147483645;
    c = a + b;

    printf ("the sum of %u and %u may be %u\n", a, b, c );


    c = a + b + 1;
    printf ("the sum of %u and %u and another 1 may be %u\n", a, b, c );

    c = a + b + 2;
    printf ("the sum of %u and %u and another 2 may be %u\n", a, b, c );

    d = 305419896;
    printf ("the value of d in decimal is %u\n", d );


    printf ("the value of d in hexadecimal is %x\n", d );


    return ( EXIT_SUCCESS );

}


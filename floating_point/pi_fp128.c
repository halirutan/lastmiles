
/*********************************************************************
 * The Open Group Base Specifications Issue 6
 * IEEE Std 1003.1, 2004 Edition
 *
 *    An XSI-conforming application should ensure that the feature
 *    test macro _XOPEN_SOURCE is defined with the value 600 before
 *    inclusion of any header. This is needed to enable the
 *    functionality described in The _POSIX_C_SOURCE Feature Test
 *    Macro and in addition to enable the XSI extension.
 *
 *********************************************************************/

#define _XOPEN_SOURCE 600
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

    /* last digit was round up from a 3 to a 4 */
    long double pi = 3.1415926535897932384626433832795028841971694L;

    printf("the sizeof(pi) is %i bytes\n", sizeof(long double) );

    printf("\npi is this  3.14159265358979323846264338");
    printf("3279502884197169.....\n\n");

    printf("pi could be %42.38Le\n", pi);


/*
    long double tenth = 0.1L;

    long double sum = 0.0L;

    sum = sum + tenth;
    printf("sum = %42.38Le\n", sum);

    sum = sum + tenth;
    printf("sum = %42.38Le\n", sum);

    sum = sum + tenth;
    printf("sum = %42.38Le\n", sum);

    sum = sum + tenth;
    printf("sum = %42.38Le\n", sum);

    sum = sum + tenth;
    printf("sum = %42.38Le\n", sum);

    sum = sum + tenth;
    printf("sum = %42.38Le\n", sum);

    sum = sum + tenth;
    printf("sum = %42.38Le\n", sum);

    sum = sum + tenth;
    printf("sum = %42.38Le\n", sum);

    sum = sum + tenth;
    printf("sum = %42.38Le\n", sum);

    sum = sum + tenth;
    printf("sum = %42.38Le\n", sum);

    sum = sum - 1.0L;

    printf("final sum is %42.38Le\n", sum);

*/
    return ( EXIT_SUCCESS );

}



#define _XOPEN_SOURCE 600

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{

    double foo = -0.0;
    double bar = 0.0;

    if ( foo == bar )
        printf("sure\n");
    else
        printf("nope\n");

    if ( foo != bar )
        printf("not equal says hello\n");

    if ( !( foo == bar ) )
        printf("not and then equal says hola\n");

    /* ruffianeo: I would shamelessly do the:
     *       printf(foo != bar ? "ne" : "eq") */
    printf("\n\nruffianeo is shameless\n\n");
    printf("%s\n", ( foo != bar ? "ne" : "eq" ) );


    return ( EXIT_SUCCESS );

}


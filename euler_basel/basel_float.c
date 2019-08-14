
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

int main(int argc, char *argv[])
{
    uint32_t n;
    float sum, pi = 3.1415926535897932384626L;
    float basel = pi * pi / 6.0L;
    float error_prev, error_now;

    sum = 0.0;

    /* some sort of fake error numbers that are different */
    error_prev = 1.0L;
    error_now = 1.1L;

    for ( n = 1; n < 16385; n++ ) {

        printf (" %05u :  n^2 = %4u        ", n, n * n);

        sum = sum + ( 1.0 / ( n * n ) );

        printf ("%-12.10g", sum);

        error_prev = error_now;
        error_now = basel - sum;
        printf ("        err = %-12.10g\n", basel - sum);

        if ( fabsf( error_prev - error_now ) < 0.0000001 ) {
            fprintf( stderr, "WARN : catestrophic loss of precision\n");
            return ( EXIT_FAILURE );
        }

    }

    return ( EXIT_SUCCESS );
}



#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

int main(int argc, char *argv[])
{
    uint64_t n;
    double sum;
    double pi = 3.141592653589793238462643383279502884197169399375L;
    double basel = pi * pi / 6.0L;
    double error_prev, error_now;

    sum = 0.0L;

    /* some sort of fake error numbers that are different */
    error_prev = 1.0L;
    error_now = 1.1L;

    for ( n = 1; n < 16777216; n++ ) {
        sum = sum + ( 1.0L / ( n * n ) );
        error_prev = error_now;
        error_now = basel - sum;
        if ( fabs( error_prev - error_now ) < 1.0e-14L ) {
            fprintf( stderr, "WARN : catestrophic loss of precision\n");
            printf (" %08lu :  n^2 = %8lu        ", n, n * n);
            printf ("%-18.16g", sum);
            printf ("        err = %-12.10e\n", basel - sum);
            return ( EXIT_FAILURE );
        }
    }

    return ( EXIT_SUCCESS );
}


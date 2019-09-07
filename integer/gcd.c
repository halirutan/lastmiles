
#include <stdio.h>
#include <stdlib.h>

int gcd_i(int *a_in, int *b_in)
{
    int loop = 0;
    int rem_m, a, b;

    a = *a_in;
    b = *b_in;

    while ( b != 0 ) {
        rem_m = a % b;
        a = b;
        b = rem_m;
        loop = loop + 1;
    }

    return a;
}

int main(int argc, char *argv[])
{
    int j, k;

    if ( argc < 3 ){
        fprintf ( stderr, "\nFAIL : Please provide integers\n");
        return ( EXIT_FAILURE );
    }

    j = (int)strtol(argv[1], (char **)NULL, 10);
    k = (int)strtol(argv[2], (char **)NULL, 10);

    printf ("gcd( %i, %i ) = ", j, k);
    int g = gcd_i(&j, &k);
    printf ("%i\n", g);

    return (EXIT_SUCCESS);
}


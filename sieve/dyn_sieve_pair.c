
#include <stdio.h>
#include <stdlib.h>

/* insane upper limit */
#define UPPER_LIMIT 536870913

int main(int argc, char *argv[])
{
    int limit, j, k, pcnt;

    /* use a reasonable name for the prime sieve */
    int *sieve; /* use a reasonable name for the prime sieve */

    double estimate;

    if ( argc < 2 ){
        fprintf(stderr,"FAIL : please provide an upper limit\n");
        return(EXIT_FAILURE);
    }

    limit = atoi(argv[1]);
    if ( limit > UPPER_LIMIT ){
        fprintf(stderr,"WARN : upper limit is %i\n", UPPER_LIMIT );
        limit = UPPER_LIMIT ;
    }

    if ( limit < 0 ){
        fprintf(stderr,"WARN : positive numbers please!\n");
        limit = -1 * limit;
    }

    if ( limit < 100 ){
        fprintf(stderr,"WARN : at least 100 please!\n");
        limit = 100;
    }

    sieve = malloc((size_t)(limit * sizeof(int)));
    if ( sieve == NULL ){
        fprintf(stderr,"FAIL : could not malloc memory!\n");
        return ( EXIT_FAILURE );
    }

    for ( k=2; k<limit; k++ ) {
        *(sieve + k) = k;
    }

    for ( k=2; k<limit; k++ )
        if ( *(sieve + k) > 0 )
            for ( j=k+k; j<limit; j=j+k ) *(sieve + j) = 0;
 
    pcnt = 0;
    for ( k=4; k<limit; k++ )
        if ( ( *(sieve + k - 2) > 0 ) && ( *(sieve + k) > 0 ) ) {
            printf(" ( %4i, %4i)\n", *(sieve + k - 2), *(sieve + k));
            pcnt += 1;
        }
    printf("\n    Number of prime pairs is %i\n", pcnt);

    free(sieve);
    return(EXIT_SUCCESS);

}


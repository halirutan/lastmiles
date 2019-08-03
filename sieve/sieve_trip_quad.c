
#include <stdio.h>
#include <stdlib.h>

/* insane upper limit */
#define UPPER_LIMIT 536870913

int main(int argc, char *argv[])
{
    int limit, j, k;

    /* count the prime triplets and quadruplets */
    int pcnt, qcnt;

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
    for ( k=2; k<(limit-6); k++ ) {
        /* check for triplets */
        if ( *(sieve + k + 6) > 0 ){
            if ( ( *(sieve + k) > 0 ) && ( *(sieve + k + 2) > 0 ) ) {
                printf(" ( %4i, %4i, %4i)\n", k, k+2, k+6);
                pcnt += 1;
            }
            if ( ( *(sieve + k) > 0 ) && ( *(sieve + k + 4) > 0 ) ) {
                printf(" ( %4i, %4i, %4i)\n", k, k+4, k+6);
                pcnt += 1;
            }
        }
    }

    qcnt = 0;
    for ( k=2; k<(limit-8); k++ ) {
        /* check for quadruplets */
        if ( *(sieve + k + 8) > 0 ){
            if (    ( *(sieve + k) > 0 )
                 && ( *(sieve + k + 2) > 0 )
                 && ( *(sieve + k + 6) > 0 ) ) {
                printf(" ( %4i, %4i, %4i, %4i)\n", k, k+2, k+6, k+8);
                qcnt += 1;
            }
        }
    }

    printf("\n    Number of prime    triplets is %i\n", pcnt);
    printf("\n    Number of prime quadruplets is %i\n", qcnt);

    free(sieve);
    return(EXIT_SUCCESS);

}


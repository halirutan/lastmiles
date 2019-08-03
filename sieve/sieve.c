
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
    int limit, j, k, pcnt, p[10000];
    double estimate;

    if ( argc < 2 ){
        fprintf(stderr,"FAIL : please provide an upper limit\n");
        return(EXIT_FAILURE);
    }

    limit = atoi(argv[1]);
    if ( limit > 10000 ){
        fprintf(stderr,"WARN : upper limit is 10000\n");
        limit = 10000;
    }

    if ( limit < 0 ){
        fprintf(stderr,"WARN : positive numbers please!\n");
        limit = -1 * limit;
    }

    if ( limit < 100 ){
        fprintf(stderr,"WARN : at least 100 please!\n");
        limit = 100;
    }

    for ( k=2; k<limit; k++ ) {
        p[k]=k;
    }

    for ( k=2; k<limit; k++ )
        if ( p[k] > 0 )
            for ( j=k+k; j<limit; j=j+k ) p[j] = 0;
 
    pcnt = 0;
    for ( k=2; k<limit; k++ )
        if ( p[k] > 0 ) {
            printf("    %02i    %i\n", k, p[k]);
            pcnt += 1;
        }
    printf("\n    Number of primes is %i\n", pcnt);

    estimate = ((double)limit) / log((double)limit);

    printf("\n    Estimate n/log(n) = %g\n", estimate);

    return(EXIT_SUCCESS);

}


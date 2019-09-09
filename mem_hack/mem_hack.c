
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>

int main(int argc, char *argv[])
{

    int j, k;
    size_t num_of = 16;
    uint64_t *foo, *bar;

    for ( k=0; k<4; k++ ) {

        if ( k%2 == 0 ) {
            foo = malloc ( num_of * sizeof(uint64_t) );
            if ( foo == NULL ) {
                /* really? possible ENOMEM? */
                if ( errno == ENOMEM ) {
                    fprintf(stderr,"FAIL : calloc returns ENOMEM at %s:%d\n",
                            __FILE__, __LINE__ );
                } else {
                    fprintf(stderr,"FAIL : calloc fails at %s:%d\n",
                            __FILE__, __LINE__ );
                }
                perror("FAIL ");
                return ( EXIT_FAILURE );
            }
        
            bar = calloc ( num_of, sizeof(uint64_t) );
            if ( bar == NULL ) {
                /* really? possible ENOMEM? */
                if ( errno == ENOMEM ) {
                    fprintf(stderr,"FAIL : calloc returns ENOMEM at %s:%d\n",
                            __FILE__, __LINE__ );
                } else {
                    fprintf(stderr,"FAIL : calloc fails at %s:%d\n",
                            __FILE__, __LINE__ );
                }
                perror("FAIL ");
                return ( EXIT_FAILURE );
            }
        } else {
            bar = calloc ( num_of, sizeof(uint64_t) );
            if ( bar == NULL ) {
                /* really? possible ENOMEM? */
                if ( errno == ENOMEM ) {
                    fprintf(stderr,"FAIL : calloc returns ENOMEM at %s:%d\n",
                            __FILE__, __LINE__ );
                } else {
                    fprintf(stderr,"FAIL : calloc fails at %s:%d\n",
                            __FILE__, __LINE__ );
                }
                perror("FAIL ");
                return ( EXIT_FAILURE );
            }

            foo = malloc ( num_of * sizeof(uint64_t) );
            if ( foo == NULL ) {
                /* really? possible ENOMEM? */
                if ( errno == ENOMEM ) {
                    fprintf(stderr,"FAIL : calloc returns ENOMEM at %s:%d\n",
                            __FILE__, __LINE__ );
                } else {
                    fprintf(stderr,"FAIL : calloc fails at %s:%d\n",
                            __FILE__, __LINE__ );
                }
                perror("FAIL ");
                return ( EXIT_FAILURE );
            }
        }
    
        for ( j= 0 ; j<num_of ; j++ ) {
            if ( *(foo+j) != 0 ) fprintf ( stderr, "DBUG : %i pass foo[%04i] = %llu at 0x%p\n", k, j, *(foo+j), foo+j );
            if ( *(bar+j) != 0 ) fprintf ( stderr, "DBUG : %i pass bar at %i\n", k, j );
        }
    
        for ( j= 0 ; j<num_of ; j++ ) {
            *(foo+j) = j + 1;
            *(bar+j) = *(foo+j) + 1000000;
        }
    
        free(foo);
        free(bar);
    
        foo = NULL;
        bar = NULL;

    }

    return ( EXIT_SUCCESS );

}


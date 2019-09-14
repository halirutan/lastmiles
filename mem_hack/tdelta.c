
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>

uint64_t timediff( struct timespec start, struct timespec end )
{
    /* return the delta time as a 64-bit positive number of
     * nanoseconds.  Regardless of the time direction between
     * start and end we always get a positive result. */

    struct timespec temp;
    uint64_t s, n;

    if ( ( end.tv_nsec - start.tv_nsec ) < 0 ) {
        /* make a full second adjustment to tv_sec */
        temp.tv_sec = end.tv_sec - start.tv_sec - 1;
        /* we have to add a full second to temp.tv_nsec */
        temp.tv_nsec = 1000000000 + end.tv_nsec - start.tv_nsec;
    } else {
        temp.tv_sec = end.tv_sec - start.tv_sec;
        temp.tv_nsec = end.tv_nsec - start.tv_nsec;
    }
    s = (uint64_t) temp.tv_sec;
    n = (uint64_t) temp.tv_nsec;
    return ( s * (uint64_t)1000000000 + n );
}

int main ( int argc, char **argv)
{

    uint64_t t_delta;
    struct timespec  t_start, t_end;

    clock_gettime( CLOCK_MONOTONIC, &t_start );
    sleep(7);
    clock_gettime( CLOCK_MONOTONIC, &t_end );

    t_delta = timediff( t_start, t_end );
    printf ("  %16lld nsec\n", t_delta );

    return EXIT_SUCCESS;

}


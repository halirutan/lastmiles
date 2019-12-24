
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
#include <stdint.h>
#include <time.h>
#include <unistd.h>

uint64_t timediff( struct timespec st, struct timespec en );

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


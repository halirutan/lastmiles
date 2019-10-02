
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
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <math.h>
#include <errno.h>
 
size_t fptohex( char **ret, const void *addr, const size_t n );

int main( int argc, char **argv)
{
    double foo = 1.125;
    size_t bar;
    char *rbuf = calloc((size_t)32,sizeof(uint8_t));

    bar = fptohex( &rbuf, (void *)&foo, sizeof(double) );
    printf ("dbug : bar = %lu\n", bar);
    printf ("     : rbuf = \"%s\"\n", rbuf );
    printf ("     :      = \"3FF2000000000000\" is correct.\n");

    foo = 1.1;
    memset( rbuf, 0x00, (size_t)1 );
    bar = fptohex( &rbuf, (void *)&foo, sizeof(double) );
    printf ("dbug : bar = %lu\n", bar);
    printf ("     : rbuf = \"%s\"\n", rbuf );
    printf ("     :      = \"3FF199999999999A\" is correct.\n");

    foo = M_PI;
    memset( rbuf, 0x00, (size_t)1 );
    bar = fptohex( &rbuf, (void *)&foo, sizeof(double) );
    printf ("dbug : bar = %lu\n", bar);
    printf ("     : rbuf = \"%s\"\n", rbuf );
    printf ("     :      = \"400921FB54442D18\" is correct.\n");

    free(rbuf);
    return ( EXIT_SUCCESS );
}


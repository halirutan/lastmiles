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

#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int main( int argc, char *argv[] ) {

    int max = -1;
    int mallop = 0;
    int j, mb;
    int bytes_formatted;
    char* buffer;
    struct timespec tn;
    char time_buffer[32] = "";

    if ( clock_gettime( CLOCK_REALTIME, &tn ) > -1 ) {
        bytes_formatted = sprintf ( time_buffer,
                                    "%10lu.%-9lu",
                                    tn.tv_sec, tn.tv_nsec );

        if ( bytes_formatted > 0 ) {
            printf ( "START %s\n", time_buffer );
        } else {
            printf ( "    0.000000000\n" );
        }
    }

    if ( argc == 2 ) {
        max = atoi(argv[1]);
        if ( max == 0 )
            printf ( " NOTE : will try to allocate all available memory.\n" );
        else
            printf ( " NOTE : will try to allocate %5i MB of memory.\n", max );

    } else {

        printf ( "Will try to allocate all available memory.\n" );
        printf ( "This MAY be the last thing your system does.\n" );

    }

    if ( ( max > 0 ) && ( max < 8 ) ) { 
        printf ( "WARNING : You must at least use 8 MB of memory!\n" );
        printf ( "        : quitting .. no harm done.\n" );
    } else {
        mb = 8;
        while (((buffer=malloc((size_t)mb*(size_t)1048576)) != NULL ) 
                             && 
               (( mb<max ) || ( max==0 )) )
        {
            /* flip bits of all memory in the buffer */
            memset( buffer, 0x00, (size_t) mb*1024*1024 );
            memset( buffer, 0xaa, (size_t) mb*1024*1024 );
            memset( buffer, 0x55, (size_t) mb*1024*1024 );
            memset( buffer, 0xff, (size_t) mb*1024*1024 );

            mb+=8;

            if ( ( mb % 16 ) == 0 ) {
                printf( "      : Allocated %6i MB", mb);

                /* Get the REALTIME_CLOCK time */
                if ( clock_gettime( CLOCK_REALTIME, &tn ) > -1 ) {
                    bytes_formatted = sprintf ( time_buffer,
                                                "%10lu.%-9lu",
                                                tn.tv_sec, tn.tv_nsec );

                    if ( bytes_formatted > 0 )
                        printf ( "    %s\n", time_buffer );
                    else
                        printf ( "    0.000000000\n" );
                }
            }

            free ( buffer );
            buffer = NULL;

        }

        if ( ( buffer == NULL ) && ( ( mb < max ) || ( max == 0 ) )  ) { 
            printf ( " NOTE : malloc returned NULL.\n" );
            printf ( "      : Most likely there is no more free memory.\n" );
        }

        printf( "FINAL : Allocated %d MB\n", mb);

    }

    if ( clock_gettime( CLOCK_REALTIME, &tn ) > -1 ) {
        bytes_formatted = sprintf ( time_buffer,
                                    "%10lu.%-9lu",
                                    tn.tv_sec, tn.tv_nsec );

        if ( bytes_formatted > 0 ) {
            printf ( "END   %s\n", time_buffer );
        } else {
            printf ( "    0.000000000\n" );
        }
    }
    return ( EXIT_SUCCESS );

}


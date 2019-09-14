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

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

int main( int argc, char *argv[] ) {

    size_t max = 0;
    int mallop = 0;
    int j;
    size_t num_bytes, mem_alloc_size, mem_delta_size;
    int bytes_formatted;
    char* buffer;
    struct timespec tn;
    char time_buffer[32] = "";
    uint64_t t0_s, t0_ns, t1_s, t1_ns, t_tmp_s, t_tmp_ns, t_delta;

    if ( clock_gettime( CLOCK_REALTIME, &tn ) > -1 ) {
        bytes_formatted = sprintf ( time_buffer,
                                    "%10lu.%-9lu",
                                    tn.tv_sec, tn.tv_nsec );

        if ( bytes_formatted > 0 ) {
            printf ( "START %s\n", time_buffer );
        } else {
            fprintf(stderr,"FAIL : you seem to not have clock_gettime().\n");
            return ( EXIT_FAILURE );
        }
    }
    t0_s = (uint64_t)tn.tv_sec;
    t0_ns = (uint64_t)tn.tv_nsec;

    if ( argc == 4 ) {
        max = (size_t)strtol(argv[1], (char **)NULL, 10);
        mem_alloc_size = (size_t)strtol(argv[2], (char **)NULL, 10);
        mem_delta_size = (size_t)strtol(argv[3], (char **)NULL, 10);

        /* ensure we are getting 32 data points */
        if ( ( max / mem_delta_size ) < 32 ) {
            fprintf(stderr, "FAIL : lets allocation some reasonable amount!\n");
            return ( EXIT_FAILURE );
        }

        printf ( " NOTE : will try to allocate %lu bytes of memory.\n", max );
        printf ( "      : we will use an init allocation of %lu bytes.\n", mem_alloc_size );
        printf ( "      : with a delta memory allocation of %lu bytes.\n", mem_delta_size );

    } else {

        fprintf (stderr, "FAIL : enter memsize total and allocation\n" );
        fprintf (stderr, "     : init size and allocation delta.\n" );
        return ( EXIT_FAILURE );

    }

    if ( ( max > 0 ) && ( max < 8 ) ) { 
        printf ( "WARNING : You must at least use 8 MB of memory!\n" );
        printf ( "        : quitting .. no harm done.\n" );
    } else {
        num_bytes = mem_alloc_size;
        while (((buffer=malloc(num_bytes)) != NULL ) 
                             && 
               (( num_bytes<max ) || ( max==0 )) )
        {
            /* flip bits of all memory in the buffer */
            memset( buffer, 0x00, num_bytes );
            memset( buffer, 0xaa, num_bytes );
            memset( buffer, 0x55, num_bytes );
            memset( buffer, 0xff, num_bytes );

            num_bytes+=mem_delta_size;

            if ( ( num_bytes % ( 8 * 1048576 ) ) == 0 ) {

                printf( "      : Allocated %6i MB", (num_bytes/1048576) );

                /* Get the REALTIME_CLOCK time */
                clock_gettime( CLOCK_REALTIME, &tn );
                bytes_formatted = sprintf ( time_buffer,
                                                "%10lu.%-9lu",
                                                tn.tv_sec, tn.tv_nsec );

                if ( bytes_formatted > 0 ) {
                    printf ( "    %s", time_buffer );
                    t1_s = (uint64_t)tn.tv_sec;
                    t1_ns = (uint64_t)tn.tv_nsec;

                    if ( ( t1_ns - t0_ns ) < 0 ) {
                        /* make a full second adjustment */
                        t_tmp_s = t1_s - t0_s - 1;
                        /* add a full second to t_tmp */
                        t_tmp_ns = 1000000000 + t1_ns - t0_ns;
                    } else {
                        t_tmp_s = t1_s - t0_s;
                        t_tmp_ns = t1_ns - t0_ns;
                    }

                    printf ("    %lu\n", 
                                 ( t_tmp_s * (uint64_t)1000000000
                                                         + t_tmp_ns ) );


                }

                t0_s = t1_s;
                t0_ns = t1_ns;

            }

            free ( buffer );
            buffer = NULL;

        }

        if ( ( buffer == NULL ) && ( ( num_bytes < max ) || ( max == 0 ) )  ) { 
            printf ( " NOTE : malloc returned NULL.\n" );
            printf ( "      : Most likely there is no more free memory.\n" );
        }

        printf( "FINAL : Allocated %lu bytes\n", num_bytes);

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


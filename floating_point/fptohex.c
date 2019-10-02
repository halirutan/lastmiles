
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
#include <signal.h>
#include <errno.h>
 
void sigsegv_handler( int sig, siginfo_t *si, void *vuctx ) {
    execl( "/some/path/sigsegv", NULL );
}

size_t fptohex( char *ret, const void *addr, const size_t n )
{
    /* Assume that addr is a pointer to a set of bytes in
     * memory and that we have n bytes that we can access.
     *
     * There is no protection here for over runs into
     * memory that is uninitialized or otherwise dangerous.
     * Well actually we could trap a SIGSEGV just for fun.
     *
     * Return the uppercase hexadecimal representation of the
     * data in ret.  
     *
     * We expect ret to be pre-allocated for us but if it is
     * NULL then we can handle the task here. A nice idea is
     * to trap a SIGSEGV on the event we wander into memory 
     * where we should not be.
     */

    uint8_t byte, mask;
    int j;
    size_t retval = 0;

    /* trap the possible SIGSEGV */
    struct sigaction sa_sigsegv;
    memset ( &sa_sigsegv, 0, sizeof( sa_sigsegv ) );
    sa_sigsegv.sa_sigaction = sigsegv_handler;
    sa_sigsegv.sa_flags = SA_SIGINFO;
    sigfillset ( &sa_sigsegv.sa_mask );
    sigaction( SIGSEGV, &sa_sigsegv, NULL);

    if ( ret == NULL ){
        /* allocate twice n for the hex digits plus a nul
         * terminator on the char buffer and align on a
         * 16 byte number */


        size_t bytes_to_clear = 2 * n + 1;

        /* align on a multiple of 16 */
        if ( bytes_to_clear%32 != 0 ) {
            bytes_to_clear = bytes_to_clear + 16 - bytes_to_clear%16;
        }

        ret = calloc( bytes_to_clear, sizeof(unsigned char));
        if ( ret == NULL ) {
            /* really? possible ENOMEM? */
            if ( errno == ENOMEM ) {
                fprintf(stderr,"FAIL : calloc returns ENOMEM at %s:%d\n",
                        __FILE__, __LINE__ );
            } else {
                fprintf(stderr,"FAIL : calloc fails at %s:%d\n",
                        __FILE__, __LINE__ );
            }
            perror("FAIL ");
            /* signal a failure and kill the whole process */
            exit( EXIT_FAILURE );
        }
    }

    int foo = 1;  /* dummy test integer */
    if ( *(char *)&foo == 1) {
        /* little endian */
        for ( j=(n-1); j>(-1); j-- ) {
            byte = f[j];
            if ( byte ) {
                mask = 0x80;
                while (mask){
                    printf ( "%d", (byte&mask ? 1 : 0) );
                    mask >>= 1;
                }
            } else {
                printf("00000000");
            }
            retval+=1;
        }
    } else {
        /* big endian */
        for ( j=0; j<n; j++ ) {
            if (j%8) {
                printf(" ");
            } else {
                /* new line on every eight bytes */
                printf("\n ");
            }
            byte = f[j];
            if ( byte ) {
                mask = 0x80;
                while (mask){
                    printf ( "%d", (byte&mask ? 1 : 0) );
                    mask >>= 1;
                }
            } else {
                printf("00000000");
            }
            retval+=1;
        }
    }
    printf("\n" );
    return retval;
}



#define _XOPEN_SOURCE 600

#include <stdio.h>
#include <stdint.h>
 
size_t bin_printf ( uint8_t* f, size_t n )
{
    /* Assume that f is a pointer to a set of bytes in
     * memory and that we have n bytes that we can access.
     * There is no protection here for over runs into
     * memory that is uninitialized or otherwise dangerous.
     * Return the number of bytes printed.
     */

    uint8_t byte, mask;
    int j, retval = 0;
    int foo = 1;  /* dummy test integer */
    if ( *(char *)&foo == 1) {
        /* little endian */
        for ( j=(n-1); j>(-1); j-- ) {
            if ((j+1)%8) {
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


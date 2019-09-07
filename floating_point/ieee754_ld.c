/*************************************************
 * The Open Group Base Specifications Issue 6
 * IEEE Std 1003.1, 2004 Edition
 *************************************************/
#define _XOPEN_SOURCE 600

#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main ( int argc, char *argv[] ) {

    int j;
    long double pi = 3.14159265358979323846264338327950288419716939937510L;
    /* note hex representation of pi is 
     *   0x4000 0x921f 0xb544 0x42d1 0x8469 0x898c 0xc517 0x01b8 */

    for ( j=0; j<sizeof(long double); j++ )
        printf("%02x ", ((unsigned char *)&pi)[j] );

    printf("\n" );

    return (EXIT_SUCCESS);
}


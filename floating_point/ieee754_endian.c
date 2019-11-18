
/*************************************************
 * The Open Group Base Specifications Issue 6
 * IEEE Std 1003.1, 2004 Edition
 *************************************************/
#define _XOPEN_SOURCE 600

#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>

void ptr_printf ( uint8_t* v );

int main ( int argc, char* argv[] ) {

    int j, bit_size, little_endian;
    struct utsname uname_data;
    double* pi = calloc((size_t)1,sizeof(double));

    pi[0] = 3.14159265358979323846264 ;
    /* IEEE754-2008 binary64 hex representation of pi is
     *    40 09 21 fb 54 44 2d 18   */

    setlocale( LC_MESSAGES, "C" );
    if ( uname( &uname_data ) < 0 ) {
        fprintf ( stderr,
                 "WARNING : Could not attain system uname data.\n" );
        perror ( "uname" );
    } else {
        printf ( "-------------------------------" );
        printf ( "------------------------------\n" );
        printf ( "        system name = %s\n", uname_data.sysname );
        printf ( "          node name = %s\n", uname_data.nodename );
        printf ( "            release = %s\n", uname_data.release );
        printf ( "            version = %s\n", uname_data.version );
        printf ( "            machine = %s\n", uname_data.machine );
        printf ( "-------------------------------" );
        printf ( "------------------------------" );
    }
    printf ("\n");

    /* The C standard really doesn't clearly say how a
     * pointer will be printed. C11 ISO/IEC 9899:2011
     * the idea is described in section 7.21.6.1 para8.
     * Maybe you get a leading 0x and maybe you don't and
     * really we are printing a void* type pointer.
     * Just use C99 <inttypes.h> and uintptr_t instead. */

    /* just to be clear let's print the data addresses */
    printf("Just to be clear here is the pointer pi info:\n");
    printf("pi ptr = 0x%0" PRIXPTR " ", (uintptr_t)pi);
    printf("at addr 0x%0" PRIXPTR "\n\n", (uintptr_t)&pi);

    bit_size = sizeof(pi) * 8;
    printf("This is a %i bit system.\n", bit_size );

    /* A big endian system would store an ordinary 32-bit int
     * in memory in left to right order similar to a decimal
     * number written by a human. The most significant bit MSB
     * will be in the lowest address and thus the int value for
     * the number one will be 0x00000001h so just check to see
     * if the initial byte of an integer is zero or one and then
     * we know we are on a big endian or little endian machine. */
    j = 1;  /* dummy test integer */
    little_endian = (*(uint8_t*)&j == 1) ? 1 : 0;

    if (!little_endian) {
        printf("This is a big endian memory machine.\n");
        printf("Data will look normal to humans.\n");
    }

    printf("---- pi is a %i-bit pointer ----\n", bit_size);
    printf("0x%" PRIXPTR " : ", (uintptr_t)&pi);
    for ( j=0; j<sizeof(pi); j++){
        printf("%02x ", ((uint8_t*)&pi)[j] );
    }
    printf("\n" );

    printf("---- IEEE 754 binary64 data ----\n");
    printf("0x%" PRIXPTR " : ", (uintptr_t)pi);
    for ( j=0; j<sizeof(double); j++ ){
        printf("%02x ", (uint8_t)((uint8_t*)pi)[j] );
    }
    printf("\n" );

/*
    bin_printf( &pi, sizeof(pi) );
 */

    if (little_endian) {
        printf("\nThis is a little endian memory machine.\n");
        printf("Data in memory may be reversed.\n");
        printf("Here is the data in natural human order.\n");
        printf("0x%" PRIXPTR " : ", (uintptr_t)pi);
        for ( j=(sizeof(double)-1); j>(-1); j-- ){
            printf("%02x ", (uint8_t)((uint8_t*)pi)[j] );
        }
        printf("\n\n" );
    }

    printf("The IEEE 754-2008 binary64 estimate value for pi is\n");
    if (bit_size==64) printf("        "); /* indent four addr bytes */
    printf("           : 40 09 21 fb 54 44 2d 18\n");
    printf("\n** Any IEEE754-2008 compliant system should match **\n");

    printf("\n" );
    ptr_printf((uint8_t*)pi);
    free(pi);
    return (EXIT_SUCCESS);
}

void ptr_printf ( uint8_t* v )
{
    /* consistent width upper case hex address from
     * an n-bit value in v such that we return a 
     * string like 0xFEEDBEEFBADCAFFE
                     ffffffff7ffff2d0         */
    int eflag = 1; /* in mem 0x00000001 big endian */
    eflag = (*(uint8_t*)&eflag == 1) ? 1 : 0;
    fprintf ( stderr, "DEBUG : eflag = %i\n", eflag );
}


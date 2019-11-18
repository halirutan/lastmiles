
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
#include <locale.h>
#include <sys/utsname.h>

int main ( int argc, char *argv[] ) {

    /* note hex representation of pi is 
     *   0x4000 0x921f 0xb544 0x42d1 0x8469 0x898c 0xc517 0x01b8
     * IEEE754-2008 binary64 hex representation of pi is
     *    40 09 21 fb 54 44 2d 18   */
    int j;

    long double pi = 3.14159265358979323846264338327950288419716939937510L;

    struct utsname uname_data;

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

    uint8_t x86_fp80[16] = { 0x35, 0xc2, 0x68, 0x21, 0xa2, 0xda, 0x0f, 0xc9,
                             0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

    printf("x86_fp80[16]\n");
    printf("    0x35, 0xc2, 0x68, 0x21, 0xa2, 0xda, 0x0f, 0xc9,\n");
    printf("    0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00\n");
    printf("out ");
    for ( j=0; j<16; j++ ) {
        printf("0x%02x ", ((uint8_t *)&x86_fp80)[j] );
    }
    printf("\n");
    printf("    x86_fp80 may be %38.34Le\n", *(long double*)&x86_fp80);
    printf("    x86_fp80  or be %18.14g\n", *(double*)&x86_fp80);
    printf("-------------------------------------------------\n");


    uint8_t pi_fp64le[16] = { 0x18, 0x2d, 0x44, 0x54, 0xfb, 0x21, 0x09, 0x40,
                              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    printf("pi_fp64le[16]\n");
    printf("    0x18, 0x2d, 0x44, 0x54, 0xfb, 0x21, 0x09, 0x40,\n");
    printf("    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00\n");
    printf("out ");
    for ( j=0; j<16; j++ ) {
        printf("0x%02x ", ((uint8_t *)&pi_fp64le)[j] );
    }
    printf("\n");
    printf("   pi_fp64le may be %38.34Le\n", *(long double*)&pi_fp64le);
    printf("   pi_fp64le  or be %18.14g\n", *(double*)&pi_fp64le);
    printf("-------------------------------------------------\n");


    uint8_t pi_fp64be[16] = { 0x40, 0x09, 0x21, 0xfb, 0x54, 0x44, 0x2d, 0x18,
                              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    printf("pi_fp64be[16]\n");
    printf("    0x40, 0x09, 0x21, 0xfb, 0x54, 0x44, 0x2d, 0x18,\n");
    printf("    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00\n");
    printf("out ");
    for ( j=0; j<16; j++ ) {
        printf("0x%02x ", ((uint8_t *)&pi_fp64be)[j] );
    }
    printf("\n");
    printf("   pi_fp64be may be %38.34Le\n", *(long double*)&pi_fp64be);
    printf("   pi_fp64be  or be %18.14g\n", *(double*)&pi_fp64be);
    printf("-------------------------------------------------\n");


    uint8_t pi_fp128le[16] = { 0xb8, 0x01, 0x17, 0xc5, 0x8c, 0x89, 0x69, 0x84,
                               0xd1, 0x42, 0x44, 0xb5, 0x1f, 0x92, 0x00, 0x40 };
    printf("pi_fp128le[16]\n");
    printf("    0xb8, 0x01, 0x17, 0xc5, 0x8c, 0x89, 0x69, 0x84,\n");
    printf("    0xd1, 0x42, 0x44, 0xb5, 0x1f, 0x92, 0x00, 0x40\n");
    printf("out ");
    for ( j=0; j<16; j++ ) {
        printf("0x%02x ", ((uint8_t *)&pi_fp128le)[j] );
    }
    printf("\n");
    printf("  pi_fp128le may be %38.34Le\n", *(long double*)&pi_fp128le);
    printf("  pi_fp128le  or be %18.14g\n", *(double*)&pi_fp128le); 
    printf("-------------------------------------------------\n");

    uint8_t pi_fp128be[16] = { 0x40, 0x00, 0x92, 0x1f, 0xb5, 0x44, 0x42, 0xd1,
                               0x84, 0x69, 0x89, 0x8c, 0xc5, 0x17, 0x01, 0xb8 };
    printf("pi_fp128be[16]\n");
    printf("    0x40, 0x00, 0x92, 0x1f, 0xb5, 0x44, 0x42, 0xd1,\n");
    printf("    0x84, 0x69, 0x89, 0x8c, 0xc5, 0x17, 0x01, 0xb8\n");
    printf("out ");
    for ( j=0; j<16; j++ ) {
        printf("0x%02x ", ((uint8_t *)&pi_fp128be)[j] );
    }
    printf("\n");       
    printf("  pi_fp128be may be %38.34Le\n", *(long double*)&pi_fp128be);
    printf("  pi_fp128be  or be %18.14g\n", *(double*)&pi_fp128be);
    printf("-------------------------------------------------\n");

    for ( j=0; j<sizeof(long double); j++ )
        printf("%02x ", ((unsigned char *)&pi)[j] );

    printf("\n" );

    printf("pi may be %38.34Le\n", pi);

    return (EXIT_SUCCESS);
}


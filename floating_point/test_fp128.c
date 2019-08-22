
#include <errno.h>
#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <unistd.h>

#define BUFFERSIZE 32

int main(int argc, char *argv[]) 
{

    struct utsname uname_data;
    size_t bufsize = BUFFERSIZE;
    long double baseline, ld1, ld2, offset1, offset2, delta;

    char *buf;
    buf = malloc( bufsize );
    if ( buf == NULL ) {
        perror ( "doh! ");
        fprintf (stderr,"FAIL : malloc failed for buf\n");
        return(EXIT_FAILURE);
    }

    if ( argc > 1 ) {
        printf ("\nINFO : You suggest a locale of %s\n", argv[1]);
        buf = setlocale ( LC_ALL, argv[1] );
    } else {
        buf = setlocale ( LC_ALL, "POSIX" );
    }

    if ( buf == NULL ) {
        fprintf (stderr,"FAIL : setlocale fail\n");
        return(EXIT_FAILURE);
    }

    if ( uname(&uname_data) < 0 ) {
        fprintf (stderr,
                 "WARN : Could not attain system uname data.\n" );
        perror ("uname");
    } else {
        printf("INFO : ------------------------------\n");
        printf("INFO :   system name = %s\n", uname_data.sysname );
        printf("INFO :     node name = %s\n", uname_data.nodename );
        printf("INFO :       release = %s\n", uname_data.release );
        printf("INFO :       version = %s\n", uname_data.version );
        printf("INFO :       machine = %s\n", uname_data.machine );
        printf("INFO : ------------------------------");
    }
    printf ("\n");

    /* firstly what is a long double anyways ? */
    printf("INFO : size of long double is %d\n", sizeof(long double));

    /* long double must use powl for the tiny little
     * offset addition computation */
    offset1 = powl( 2.0L, -1073.0L);
    printf("\n\nDATA :  offset1 = %.38Le\n", offset1);
    offset2 = powl( 2.0L, -1074.0L);
    printf("DATA :  offset2 = %.38Le\n", offset2);

    /* we add to this monstrous large thing */
    baseline = powl( 2.0L, 1023.0L);
    printf("DATA : baseline = %.38Le\n", baseline);

    /* this is the original which shows a loss of
      * precision due to the addition of a small
      * offset which is well out of the domain range.
      *
     ld1 = (long double)pow(2.0, 1023) + pow(2.0, -1073);
     ld2 = (long double)pow(2.0, 1023) + pow(2.0, -1074);
     */

    ld1 = baseline + offset1;
    ld2 = baseline + offset2;

    printf("\n\nDATA :      ld1 = %.38Le\n", ld1);
    printf("DATA :      ld2 = %.38Le\n", ld2);

    delta = fabsl(ld1 - ld2);
    printf("INFO :    delta = %.38Le\n", delta);

    if ( delta == 0.0L ) 
        printf("barf barf barf.\n");

    return ( EXIT_SUCCESS );

}


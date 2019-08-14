
#include <errno.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFERSIZE 32


int valid_date( int d, int m, int y );


int main(int argc, char *argv[])
{
    size_t bufsize = BUFFERSIZE;
    int errno;
    int j, k;
    int day, month, year;

    char *buf;
    buf = malloc( bufsize );
    if ( buf == NULL ) {
        perror ( "doh! ");
        fprintf (stderr,"FAIL : malloc failed for buf\n");
        return(EXIT_FAILURE);
    }

    buf = setlocale ( LC_ALL, "POSIX" );
    if ( buf == NULL ) {
        fprintf (stderr,"FAIL : setlocale ( LC_ALL, \"POSIX\" ) fails\n");
        return(EXIT_FAILURE);
    }
    printf ( "setlocale ( LC_ALL, \"POSIX\" ) returns %s\n", buf );


    /* silly code that prints out the cli arguments */
    if ( argc > 2 ) {
        printf ( "\n    there are %i things on the cli\n", argc );
        for ( j=0; j<argc; j++ ){
            printf ( "    arg[ %2i ] is \'%s\'\n", j, argv[j] );
        }
    }

    for ( year = 2019; year < 2021; year++ ) {
        for ( month = 1; month < 13; month++ ) {
            for ( day = 1; day < 32; day++ ) {
                /* vanarius_10 says :
                 * ( month%1 ? ( month < 7 ? 31 , 30 ) , ( month >= 7 ? 30 , 31 ) ) */

                /* does this date exist ? */

                if ( day < 29 ) {
                    printf ( "    y = %4i    m = %2i    d = %2i\n", year, month, day);
                } else {

                    if ( valid_date( day, month, year ) == 1 ) {

                        printf ( "    y = %4i    m = %2i    d = %2i\n", year, month, day);

                    } else {

                        fprintf (stderr,"WARN : invalid date y = %4i    m = %2i    d = %2i\n", year, month, day);

                    }

                }

            } /* day */

        } /* month */

    } /* year */

    free(buf);
    buf = NULL;
    return ( EXIT_SUCCESS );

}


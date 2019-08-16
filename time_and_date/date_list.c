
#include <errno.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFERSIZE 32

/* function to determine if a date is valid */
int valid_date( int d, int m, int y );

/* function to print out the date in whatever locale we want */
int print_date( int day, int month, int year );

int main(int argc, char *argv[])
{
    size_t bufsize = BUFFERSIZE;
    int errno = 0;  /* start with no error condition */
    int j, k;
    int day, month, year;

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

    for ( year = 2019; year < 2031; year++ ) {
        for ( month = 1; month < 13; month++ ) {
            for ( day = 1; day < 32; day++ ) {

                /* vanarius_10 in chat suggests this magic :
                 *
                 * ( month%1 ?
                 *    ( month < 7 ? 31 , 30 ) ,
                 *       ( month >= 7 ? 30 , 31 ) ) */

                /* does this date exist ? */
                if ( day < 29 ) {

                    /* printf ( "    y = %4i    m = %2i    d = %2i\n",
                                                      year, month, day);
                                                      */
                    print_date( day, month, year );

                } else {

                    if ( valid_date( day, month, year ) == 1 ) {

                        print_date( day, month, year );

                    } else {

                        fprintf (stderr, "WARN : invalid date ");
                        fprintf (stderr, "y = %4i  m = %2i  d = %2i\n",
                                                      year, month, day);

                    }

                }
            } /* day */
        } /* month */
    } /* year */

    free(buf);
    buf = NULL;
    return ( EXIT_SUCCESS );

}


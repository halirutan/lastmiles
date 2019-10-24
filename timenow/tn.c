
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

#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

/***********************************************************************
 *      tn : trivial UNIX time output function for time now
 *
 *  Output : current UNIX time expressed in seven bit ASCII chars 0 - 9
 *           with options for fractional time after a decimal point.
 *           Default output is UNIX time expressed as nine decimal 
 *           digits followed by a carraige return char.
 *
 *  Locale : At this time only the C or POSIX locale is supported and 
 *           thus the decimal point is char 0x2eh or octal 056
 *
 * Options : the user may request fractional time output as well as
 *           output without a carraige return char 0x0dh nor 0x0ah.
 *
 *           -b  signifies that a bare string output is requested 
 *               without a carraige return
 *
 *           -f  fractional time is requested in which case there
 *               shall be nine decimal digits for UNIX time to the
 *               left of a decimal point as well as nine decimal
 *               digits to the right of the decimal point. There is
 *               no promise that time is accurate nor that time may
 *               may be expressed within nine digits of precision.
 *
 *            NOTE : All other options are silently ignored.
 *
 * $ ./tn -f
 * 1416795058.948174500
 *
 *        It would be annoying to output the fractional time part byte
 *        by byte with an if clause to detect space chars and replace
 *        the output with 0x30h zero chars.  Annoying but perhaps no 
 *        other way. 
 *
 * Also, merely as a note here, senseless repetition of options may be
 * misunderstood. Since we only check for two char sequences within a
 * given argv[] string thus : 
 *
 * $ ./tn -ffbfbbb
 * 1416795324.741733932
 *
 * Dennis Clarke  dclarke@blastwave.org
 *
 ***********************************************************************/

int main( int argc, char *argv[] ) {

    char time_buffer[32];
    char buffer[21];
    char bare_opt[8] = "-b";
    char frac_opt[8] = "-f";
    char barefrac_opt[8] = "-bf";
    char fracbare_opt[8] = "-fb";

    struct timespec tn;

    int ec;
    int bare = 0;
    int frac = 0;
    size_t j;

    ec = clock_gettime( CLOCK_REALTIME, &tn );
    if ( ec == 0 ) {
        sprintf ( time_buffer, "%10lu", tn.tv_sec );
        fprintf ( stdout, "%s", time_buffer );
        if ( argc < 2 ) {
            fprintf ( stdout, "\n" );
        } else {
            for ( j = 1; j < (size_t)argc; j++ ) {
                /* ugly but works */
                if ( strncmp( bare_opt, argv[j], (size_t) 2 ) == 0 ) {
                    /* bare output without a CR requested */
                    bare = 1;
                }

                if ( strncmp( frac_opt, argv[j], (size_t) 2 ) == 0 ) {
                    /* fractional output requested */
                    frac = 1;
                }

                if ( strncmp( barefrac_opt, argv[j], (size_t) 3 ) == 0 ) {
                    /* bare output with fractional time requested */
                    bare = 1;
                    frac = 1;
                }

                if ( strncmp( fracbare_opt, argv[j], (size_t) 3 ) == 0 ) {
                    /* bare output with fractional time requested */
                    bare = 1;
                    frac = 1;
                }
            }

            if ( frac == 1 ) {
                snprintf( time_buffer, (size_t)11, ".%-9lu", tn.tv_nsec );
                for ( j=0; j<strlen(time_buffer); j++ ) {
                    if (isspace(time_buffer[j])){
                        time_buffer[j] = 0x0;
                        j = 32; /* some out of bounds val */
                    }
                }
                strncat( time_buffer, "000000000", (size_t)9 );
                /* output no more than 20 chars from the result such
                 * that we get a time like 1447199009.123456789 or
                 * possibly 1447199009.000000000 with trailing zeros.
                 * Be aware we already printed the integer portion.
                 */
                strncpy ( buffer, time_buffer, (size_t)10 );
                /* be aware we need the terminating null */
                buffer[10] = '\0';
                fprintf ( stdout, "%s", buffer );
            }

            if ( bare == 0 ) {
                fprintf ( stdout, "\n" );
            }

        }
    } else {
        if ( ec == EINVAL ) {
            fprintf ( stderr, "%s : EINVAL = not a known clock\n", argv[0] );
        }

        if ( ec == ENOSYS ) {
            fprintf ( stderr, "%s : ENOSYS = clock_gettime not supported\n", argv[0] );
        }

        return ( EXIT_FAILURE );
    }

    return ( EXIT_SUCCESS );

}


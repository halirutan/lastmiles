
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
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <errno.h>
#include <math.h>

/* some sample polynomial */
double f_poly0( double x )
{
    double ret = ( 3.0 * x * x - 5.0 * x + 2.0 );
    return ret;
}

/* derivitive of the sample polynomial */
double fp_poly0( double x )
{
    double ret = ( 6.0 * x - 5.0 );
    return ret;
}

int main(int argc, char **argv)
{

    /* Newton Raphson trivial approach wherein we make a guess
     * and then bounce around with secant linear jumps to the
     * next possible guess until maybe we get a polynomial
     * result near enough to zero.
     *
     *    essentially we have a guess called x_0 and it can
     *    be anywhere in the domain of the function. We use
     *    the first derivitive to make the next guess : 
     *
     *         x_1 = x_0 -  f(x_0)/f'(x_0) 
     *
     *   Then check is we are anywhere near a zero root with 
     *   the guess.
     *
     * With the test polynomial we can locate roots 2/3 and
     * +1 even with a guess very near the derivative zero
     * slope point of 5/6 which we can estimate at 0.8333333
     * and any variation left or right of that point will 
     * then locate a root.
     */

    /* just some close to zero test */
    const double epsilon = 0.000001;
    double x0, x1;
    uint32_t loop_cnt = 0;
    errno = 0;

    if ( argc>1 ) {
        /* what happens next may be useless to detect bad data */
        x0 = strtod(argv[1], (char**) NULL);
        if ( errno == ERANGE ) {
            fprintf(stderr,"FAIL : please provide a valid double.\n");
            fprintf(stderr,"     : Error ERANGE\n");
            perror("DBUG");
            return(EXIT_FAILURE);
        }
        if ( errno == EINVAL ) {
            fprintf(stderr,"FAIL : please provide a valid double.\n");
            fprintf(stderr,"     : Error EINVAL\n");
            perror("DBUG");
            return(EXIT_FAILURE);
        }
    } else {
        fprintf(stderr,"FAIL : please provide a guess double.\n");
        return(EXIT_FAILURE);
    }

    printf("guess x0 = %g\n", x0 );

    while ( ( loop_cnt < 32 ) && ( fabs(f_poly0(x0)) > epsilon ) ) {
        x1 = x0 -  f_poly0(x0)/fp_poly0(x0);
        loop_cnt+=1;
        printf("x%i = %g\n", loop_cnt, x1);
        x0 = x1;
    }

    return(EXIT_SUCCESS);
}


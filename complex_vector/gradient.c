
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

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <math.h>

#include "v.h"

/* compute the surface gradient vector at the intercept point
 * provided as described in our notes on page 2.
 */
int gradient( vec_type *res,
              vec_type *sign,
              vec_type *loc,
              vec_type *axi,
              vec_type *intercept )
{

    cplex_type c_tmp[12];

    /* what data did we receive ?

    fprintf(stderr, "grad :  sign = %g, %g, %g\n", sign->x.r, sign->y.r, sign->z.r);
    fprintf(stderr, "grad :   loc = %g, %g, %g\n", loc->x.r, loc->y.r, loc->z.r);
    fprintf(stderr, "grad :   axi = %g, %g, %g\n", axi->x.r, axi->y.r, axi->z.r);
    fprintf(stderr, "grad : icept = %g, %g, %g\n", intercept->x.r, intercept->y.r, intercept->z.r);
    */

    /* deal with just the x axis component first */
    c_tmp[0].r = intercept->x.r;
    c_tmp[0].i = intercept->x.i;
    /* we need to square the semi-major axi */
    c_tmp[1].r = axi->x.r;
    c_tmp[1].i = axi->x.i;
    cplex_sq( c_tmp+2, c_tmp+1 );
    /* do the trivial division */
    cplex_div( c_tmp+3, c_tmp, c_tmp+2 );
    /* mult by 2 here */
    c_tmp[3].r *= 2.0;
    c_tmp[3].i *= 2.0;

    /* now the y axis component */
    c_tmp[4].r = intercept->y.r;
    c_tmp[4].i = intercept->y.i;
    c_tmp[5].r = axi->y.r;
    c_tmp[5].i = axi->y.i;
    cplex_sq( c_tmp+6, c_tmp+5 );
    /* division */
    cplex_div( c_tmp+7, c_tmp+4, c_tmp+6 );
    /* mult by 2 */
    c_tmp[7].r *= 2.0;
    c_tmp[7].i *= 2.0;

    /* z axis component */
    c_tmp[8].r = intercept->z.r;
    c_tmp[8].i = intercept->z.i;
    c_tmp[9].r = axi->z.r;
    c_tmp[9].i = axi->z.i;
    cplex_sq( c_tmp+10, c_tmp+9 );
    /* division */
    cplex_div( c_tmp+11, c_tmp+8, c_tmp+10 );
    /* mult by 2 */
    c_tmp[11].r *= 2.0;
    c_tmp[11].i *= 2.0;

    /* copy into a result vector */

    cplex_vec_set( res, c_tmp[3].r, c_tmp[3].i,
                        c_tmp[7].r, c_tmp[7].i,
                        c_tmp[11].r, c_tmp[11].i);

    /* 01 Jan 2020 we should not do the normalization here 
     * cplex_vec_normalize( res, tmp+2 );
     */

    return ( EXIT_SUCCESS );

}


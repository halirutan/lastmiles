
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

    vec_type tmp[3];
    cplex_type c_tmp[3];

    /* what data did we receive ? */

    fprintf(stderr, "grad :  sign = %g, %g, %g\n", sign->x.r, sign->y.r, sign->z.r);
    fprintf(stderr, "grad :   loc = %g, %g, %g\n", loc->x.r, loc->y.r, loc->z.r);
    fprintf(stderr, "grad :   axi = %g, %g, %g\n", axi->x.r, axi->y.r, axi->z.r);
    fprintf(stderr, "grad : icept = %g, %g, %g\n", intercept->x.r, intercept->y.r, intercept->z.r);

    /*
    printf ("\n\nINFO : in gradient intercept = \n");
    cplex_vec_print( intercept );
    printf ("\n");
    */

    cplex_vec_scale( tmp, loc, -2.0 );

    /*
    printf ("\n\nINFO : in gradient tmp = -2loc = \n");
    cplex_vec_print( tmp );
    printf ("\n");
    */

    cplex_vec_add( tmp+1, intercept, tmp );
    
    /*
    printf ("\n\nINFO : in gradient tmp[1] = \n");
    cplex_vec_print( tmp+1 );
    printf ("\n\n");
    */

    c_tmp[0].r = tmp[1].x.r * sign->x.r;
    c_tmp[0].i = tmp[1].x.i;
    c_tmp[1].r = tmp[1].y.r * sign->y.r;
    c_tmp[1].i = tmp[1].y.i;
    c_tmp[2].r = tmp[1].z.r * sign->z.r;
    c_tmp[2].i = tmp[1].z.i;


    /*
    printf ("INFO :in gradient res = \n< ( %-16.10e, %-16.10e ),\n",
                                               c_tmp[0].r, c_tmp[0].i);

    printf ("  ( %-16.10e, %-16.10e ),\n", c_tmp[1].r, c_tmp[1].i);

    printf ("  ( %-16.10e, %-16.10e ) >\n\n", c_tmp[2].r, c_tmp[2].i);
    */


    cplex_vec_set( tmp+2, c_tmp[0].r, c_tmp[0].i,
                          c_tmp[1].r, c_tmp[1].i,
                          c_tmp[2].r, c_tmp[2].i);

    cplex_vec_normalize( res, tmp+2 );

    fprintf(stderr, "grad :   res = %g, %g, %g\n\n", res->x.r, res->y.r, res->z.r);

    return ( EXIT_SUCCESS );

}


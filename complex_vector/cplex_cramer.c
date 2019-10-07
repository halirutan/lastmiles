
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

#include <stdlib.h>
#include "v.h"

int cplex_cramer( vec_type *res,
                  vec_type *r1,
                  vec_type *r2,
                  vec_type *r3,
                  vec_type *d )
{

    /* Assume we have a failure condition and change this
     * to a zero later if all goes well */
    int det_status, result_status = -1;
    double denom_det_mag;
    vec_type tmp_r1, tmp_r2, tmp_r3;

    /* we will need a determinate of our left hand matrix in
     * the denominator of further calculations. */
    cplex_type denom_det, x_numerator, y_numerator, z_numerator;

    det_status = cplex_det( &denom_det, r1, r2, r3 );
    denom_det_mag = cplex_mag(&denom_det);

    /* we need to determine if we have a non-zero denominator */
    if ( denom_det_mag > 0.0 ) {
        result_status = 0;
        /* attempt to compute res.x from d vector replacement
         * in the first column */
        tmp_r1.x.r = d->x.r;  tmp_r1.x.i = d->x.i;
        tmp_r1.y.r = r1->y.r; tmp_r1.y.i = r1->y.i;
        tmp_r1.z.r = r1->z.r; tmp_r1.y.i = r1->z.i;

        tmp_r2.x.r = d->y.r;  tmp_r2.x.i = d->y.i;
        tmp_r2.y.r = r2->y.r; tmp_r2.y.i = r2->y.i;
        tmp_r2.z.r = r2->z.r; tmp_r2.y.i = r2->z.i;

        tmp_r3.x.r = d->z.r;  tmp_r3.x.i = d->z.i;
        tmp_r3.y.r = r3->y.r; tmp_r3.y.i = r3->y.i;
        tmp_r3.z.r = r3->z.r; tmp_r3.y.i = r3->z.i;

        det_status = cplex_det(&x_numerator, &tmp_r1, &tmp_r2, &tmp_r3);



    } else {
        return result_status;
    }


    /* cplex_type cross[12], tmp[5]; */

    /* please see https://en.wikipedia.org/wiki/Cramer%27s_rule
     */

    /*
    cplex_mult( &cross[0], &r1->x, &r2->y );
    cplex_mult( &cross[1], &cross[0], &r3->z );
    cplex_add( &tmp[0], &cross[1], &cross[3] );
    cplex_add( &tmp[1], &tmp[0], &cross[5] );
    cplex_sub( &tmp[2], &tmp[1], &cross[7] );
    res->r = tmp[4].r;
    res->i = tmp[4].i;
    */

}


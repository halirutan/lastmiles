
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
#include <math.h>
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
        /* compute res.x from d vector replacement
         * in the first column */
        tmp_r1.x.r = d->x.r;  tmp_r1.x.i = d->x.i;
        tmp_r1.y.r = r1->y.r; tmp_r1.y.i = r1->y.i;
        tmp_r1.z.r = r1->z.r; tmp_r1.z.i = r1->z.i;

        tmp_r2.x.r = d->y.r;  tmp_r2.x.i = d->y.i;
        tmp_r2.y.r = r2->y.r; tmp_r2.y.i = r2->y.i;
        tmp_r2.z.r = r2->z.r; tmp_r2.z.i = r2->z.i;

        tmp_r3.x.r = d->z.r;  tmp_r3.x.i = d->z.i;
        tmp_r3.y.r = r3->y.r; tmp_r3.y.i = r3->y.i;
        tmp_r3.z.r = r3->z.r; tmp_r3.z.i = r3->z.i;

        det_status = cplex_det(&x_numerator, &tmp_r1, &tmp_r2, &tmp_r3);

        /* compute res.y from d vector replacement
         * in the second column */
        tmp_r1.x.r = r1->x.r; tmp_r1.x.i = r1->x.i;
        tmp_r1.y.r = d->x.r;  tmp_r1.y.i = d->x.i;
        tmp_r1.z.r = r1->z.r; tmp_r1.z.i = r1->z.i;

        tmp_r2.x.r = r2->x.r; tmp_r2.x.i = r2->x.i;
        tmp_r2.y.r = d->y.r;  tmp_r2.y.i = d->y.i;
        tmp_r2.z.r = r2->z.r; tmp_r2.z.i = r2->z.i;

        tmp_r3.x.r = r3->x.r; tmp_r3.x.i = r3->x.i;
        tmp_r3.y.r = d->z.r;  tmp_r3.y.i = d->z.i;
        tmp_r3.z.r = r3->z.r; tmp_r3.z.i = r3->z.i;

        det_status = cplex_det(&y_numerator, &tmp_r1, &tmp_r2, &tmp_r3);

        /* compute res.z from d vector replacement
         * in the third column */
        tmp_r1.x.r = r1->x.r; tmp_r1.x.i = r1->x.i;
        tmp_r1.y.r = r1->y.r; tmp_r1.y.i = r1->y.i;
        tmp_r1.z.r = d->x.r;  tmp_r1.z.i = d->x.i;

        tmp_r2.x.r = r2->x.r; tmp_r2.x.i = r2->x.i;
        tmp_r2.y.r = r2->y.r; tmp_r2.y.i = r2->y.i;
        tmp_r2.z.r = d->y.r;  tmp_r2.z.i = d->y.i;

        tmp_r3.x.r = r3->x.r; tmp_r3.x.i = r3->x.i;
        tmp_r3.y.r = r3->y.r; tmp_r3.y.i = r3->y.i;
        tmp_r3.z.r = d->z.r;  tmp_r3.z.i = d->z.i;

        det_status = cplex_det(&z_numerator, &tmp_r1, &tmp_r2, &tmp_r3);

        cplex_div ( &res->x, &x_numerator, &denom_det );
        cplex_div ( &res->y, &y_numerator, &denom_det );
        cplex_div ( &res->z, &z_numerator, &denom_det );

        /* check for data smaller than RT_EPSILON */
        if ( fabs(res->x.r) < RT_EPSILON ) res->x.r = 0.0;
        if ( fabs(res->x.i) < RT_EPSILON ) res->x.i = 0.0;
        if ( fabs(res->y.r) < RT_EPSILON ) res->y.r = 0.0;
        if ( fabs(res->y.i) < RT_EPSILON ) res->y.i = 0.0;
        if ( fabs(res->z.r) < RT_EPSILON ) res->z.r = 0.0;
        if ( fabs(res->z.i) < RT_EPSILON ) res->z.i = 0.0;

    }

    return result_status;

}



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

int cplex_det( cplex_type *res,
               vec_type *r1,
               vec_type *r2,
               vec_type *r3 )
{

    cplex_type cross[12], tmp[5];

    /* the determinant of a 3x3 matrix with rows r1, r2, r3 :
     *
     *        ||    r1.x    r1.y    r1.z  ||
     *        ||    r2.x    r2.y    r2.z  ||
     *        ||    r3.x    r3.y    r3.z  ||
     *
     *   ==>    r1.x * r2.y * r3.z 
     *        + r1.y * r2.z * r3.x
     *        + r1.z * r2.x * r3.y
     *        - r3.x * r2.y * r1.z
     *        - r3.y * r2.z * r1.x
     *        - r3.z * r2.x * r1.y
     *
     * So it may be expediant to use intermediate internal
     * product values. i.e. :
     *
     *      cross[0] = cplex_mult( &r1->x, &r2->y )
     *
     */

    cplex_mult( &cross[0], &r1->x, &r2->y );
    cplex_mult( &cross[1], &cross[0], &r3->z );

    cplex_mult( &cross[2], &r1->y, &r2->z );
    cplex_mult( &cross[3], &cross[2], &r3->x );
    
    cplex_mult( &cross[4], &r1->z, &r2->x );
    cplex_mult( &cross[5], &cross[4], &r3->y );

    cplex_mult( &cross[6], &r3->x, &r2->y );
    cplex_mult( &cross[7], &cross[6], &r1->z );

    cplex_mult( &cross[8], &r3->y, &r2->z );
    cplex_mult( &cross[9], &cross[8], &r1->x );

    cplex_mult( &cross[10], &r3->z, &r2->x );
    cplex_mult( &cross[11], &cross[10], &r1->y );

    cplex_add( &tmp[0], &cross[1], &cross[3] );
    cplex_add( &tmp[1], &tmp[0], &cross[5] );
    cplex_sub( &tmp[2], &tmp[1], &cross[7] );
    cplex_sub( &tmp[3], &tmp[2], &cross[9] );
    cplex_sub( &tmp[4], &tmp[3], &cross[11] );

    res->r = tmp[4].r;
    res->i = tmp[4].i;

    return ( EXIT_SUCCESS );

}


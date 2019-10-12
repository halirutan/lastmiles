
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

/* theddmage and we all agree that a vertor "normal" is a
 * vector with the same direction but a unit length. */
int cplex_vec_normalize( vec_type *res, vec_type *op1 )
{

    double magnitude = cplex_vec_mag( op1 );
    if ( magnitude < RT_EPSILON ) {
        return ( -1 );
    }

    res->x.r = op1->x.r / magnitude; res->x.i = op1->x.i / magnitude;
    res->y.r = op1->y.r / magnitude; res->y.i = op1->y.i / magnitude;
    res->z.r = op1->z.r / magnitude; res->z.i = op1->z.i / magnitude;

    return ( 0 );

}

